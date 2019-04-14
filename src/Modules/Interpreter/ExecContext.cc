
/***********************************************************************
 *  This code is part of CMPL
 *
 *  Copyright (C) 2007, 2008, 2009, 2010, 2011
 *  Mike Steglich - Technical University of Applied Sciences
 *  Wildau, Germany and Thomas Schleiff - Halle(Saale),
 *  Germany
 *
 *  Coliop3 and CMPL are projects of the Technical University of
 *  Applied Sciences Wildau and the Institute for Operations Research
 *  and Business Management at the Martin Luther University
 *  Halle-Wittenberg.
 *  Please visit the project homepage <www.coliop.org>
 *
 *  CMPL is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  CMPL is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/


#include <sstream>

#include "ExecContext.hh"
#include "Interpreter.hh"
#include "ValueStore.hh"
#include "Interval.hh"
#include "TupleUtil.hh"
#include "SetUtil.hh"
#include "ValFunction.hh"
#include "ValType.hh"
#include "ValContainer.hh"
#include "ValSpecial.hh"
#include "OperationBase.hh"
#include "../../Control/MainControl.hh"
#include "../../CommonData/IntCode.hh"



namespace cmpl
{

	/*********** ExecContext **********/

	/**
	 * constructor
	 * @param mod			interpreter module
	 * @param prv			parent execution context / NULL: this is the root execution context
     * @param fct           execution context is a function context
     * @param fctArg		only for function context: pointer to function argument
	 */
    ExecContext::ExecContext(Interpreter *mod, ExecContext *prv, bool fct, StackValue *fctArg)
	{
		_modp = mod;
		_parent = prv;
		_level = (prv ? prv->_level + 1 : 0);
        _fctContext = fct;
        _needLock = (prv ? prv->_needLock : false);

        _localSymbols = NULL;
        _localSymbolCap = 0;
        _localSymbolCreateTo = 0;

		_stackTop = 0;
		_stackCap = ARR_NEWCAP(0);
		_stack = NULL;
		ARR_REALLOC(_stack, StackValue, _stackTop, _stackCap);

        _fctArg = (fct ? fctArg : (prv ? prv->_fctArg : NULL));
        _fctThis = (fct && prv ? prv->_callThis : (prv ? prv->_fctThis : NULL));
        _callThis = NULL;

        _cbContextTop = 0;
        _cbContextCreateTop = 0;
        _cbContext = NULL;
        if (_fctArg) {
            _cbContextCap = ARR_NEWCAP(0);
            ARR_REALLOC(_cbContext, CodeBlockContext *, _cbContextTop, _cbContextCap);
        }
        else {
            _cbContextCap = 0;
        }

        _assRhs = NULL;
        _assDataType = NULL;

        _cancel = false;
	}

	/**
	 * destructor
	 */
	ExecContext::~ExecContext()
	{
        if (_localSymbols) {
            // only for error handling: uninitialize symbols
            for (unsigned i = _localSymbolCreateTo; i < _localSymbolCap; i++)
                _localSymbols[i].unset();

            delete[] _localSymbols;
        }

        if (_stack) {
            // only for error handling: empty stack
            stackPopTo(_stack);

            delete _stack;
        }

        if (_cbContext) {
            // only for error handling: delete codeblock contexts
            for (unsigned i = _cbContextCreateTop; i < _cbContextTop; i++) {
                if (_cbContext[i])
                    delete _cbContext[i];
            }

            delete _cbContext;
        }

        _opRes.dispose();
	}


    /**
     * creates new execution context object for iteration execution within own thread
     * @param lsdt          count of initialized local symbols in <code>prv</code>
     * @return              new execution context
     */
    ExecContext *ExecContext::newAsIterCopy(unsigned lsdt)
    {
        ExecContext *res = new ExecContext(_modp, this, false);
        res->_needLock = true;

        // local symbol values
        if (_localSymbolCap) {
            res->_localSymbolCap = _localSymbolCap;
            res->_localSymbols = new SymbolValue[_localSymbolCap];

            if (lsdt) {
                res->_localSymbolCreateTo = lsdt;

                // copy local symbols values without increment reference counter, because the symbols up to <code>lsdt</code> are never uninitialized within the the new execution context
                memcpy(res->_localSymbols, _localSymbols, sizeof(SymbolValue) * lsdt);
            }
        }

        // codeblock contexts
        if (_cbContextCap) {
            res->_cbContextCap = _cbContextCap;
            res->_cbContextTop = res->_cbContextCreateTop = _cbContextTop;

            ARR_REALLOC(res->_cbContext, CodeBlockContext *, 0, res->_cbContextCap);
            memcpy(res->_cbContext, _cbContext, sizeof(CodeBlockContext *) * res->_cbContextTop);
        }

        return res;
    }

    /**
     * reinitialize execution context object for reuse in another thread for iteration execution
     */
    void ExecContext::reinitIterCopy()
    {
        _cancel = false;

        if (_stackTop)
            internalError("invalid computation stack state in execution context for iteration");

        if (_cbContextTop != _cbContextCreateTop)
            internalError("invalid codeblock context stack state in execution context for iteration");

        if (_localSymbolCap > _localSymbolCreateTo && !_localSymbols[_localSymbolCreateTo].isUninitialized())
            internalError("invalid local symbol array state in execution context for iteration");
    }

    /**
     * release execution context object created for iteration execution within own thread
     */
    void ExecContext::disposeIterCopy()
    {
        //TODO?
    }


    /**
     * get start of the array with intermediary code
     */
    IntCode::IcElem *ExecContext::codeBase() const
    {
        return _modp->_code;
    }


	/**
	 * main function, runs the main loop for execution of the intermediary code
     * @param startPos      start position within the intermediary code
     * @param userFct       execution of a user defined function
     * @param res           pointer for storing result (NULL if not used)
     */
    void ExecContext::run(unsigned startPos, bool userFct, CmplVal *res)
	{
        PROTO_MOD_OUTL(_modp, "start main loop in execution context (level " << _level << ") at code pos " << startPos);

        IntCode::IcElem *curCommand = _modp->_code + startPos;
		IntCode::IcElem *cMax = _modp->_code + _modp->_codeCnt;
		IntCode::IcElem *ncd;

        // check for execution of single codeblock header or single codeblock body
        bool cbHeader = false, cbBody = false;
        unsigned cbLvl = 0;
        unsigned long stackTopStart = _stackTop;
        unsigned cbTopStart = _cbContextTop;
        bool cbCancel = false, endCtx = false;

        if (curCommand->tp == IntCode::icTypeCommand && (curCommand->v.c.major == INTCODE_CODEBLOCK || curCommand->v.c.major == INTCODE_CB_HEADER)) {
            if (curCommand->v.c.major == INTCODE_CODEBLOCK && curCommand->v.c.minor == ICS_CB_PART_BODY)
                cbBody = true;
            else if (curCommand->v.c.major == INTCODE_CB_HEADER && curCommand->v.c.minor == ICS_CBHEADER_START)
                cbHeader = true;
        }

        // check for execution of user defined function or of whole code
        if (userFct || startPos == 0) {
            PROTO_MOD_OUT_IC(_modp, (unsigned)(curCommand - _modp->_code), curCommand);
            if (curCommand->tp != IntCode::icTypeCommand || curCommand->v.c.major != INTCODE_FUNCTION || curCommand->v.c.minor != ICS_FUNC_START || curCommand->v.c.cnt != 0)
                internalError((startPos ? "invalid function start within intermediary code" : "invalid start of intermediary code"));

            _localSymbolCap = curCommand->v.c.par;
			_localSymbols = new SymbolValue[_localSymbolCap];

			//TODO: init fuer lokale Symbole; sonst?
			// (lokale Symbole können hier mangels Info nicht weiter initialisiert werden, erst beim ersten Fetch darauf (darin steht dann auch die eindeutige Symbolnummer))

            curCommand++;
		}

		// execution main loop
        while (curCommand < cMax) {
            _curCommand = curCommand;
#if PROTO
			if (_modp->isProtocol()) {
                curCommand->protoOut(_modp, (unsigned)(curCommand - codeBase()));
                for (unsigned i = 1; i <= curCommand->v.c.cnt; i++)
                    curCommand[i].protoOut(_modp, (unsigned)(curCommand + i - codeBase()));
			}
#endif

            if (_cancel && !cbCancel) {
                LockGuard<recursive_mutex> lck(_needLock, _cancelMtx);

                if ((cbHeader || cbBody) && cbTopStart > _cancelCbLvl) {
                    stackPopTo(_stack + _stackTop, true);
                    if (cbHeader)
                        res->set(TP_BIN, false);
                    else
                        res->set(TP_BLANK);

                    if (_cbContextTop > cbTopStart)
                        popCBContext(curCommand->se, _cbContextTop - cbTopStart);

                    if (_cancelCont && cbTopStart == _cancelCbLvl + 1)
                        _cancel = false;

                    PROTO_MOD_OUTL(_modp, "leave execution context (level " << _level << ") for single codeblock header or body after cancel signal at code pos " << (unsigned)(curCommand - _modp->_code) << endl << "  -> result: " << res);
                    return;
                }
                else {
                    cbCancel = true;
                }
            }

            if (curCommand->tp != IntCode::icTypeCommand)
				internalError("invalid element in intermediary code");

            switch (curCommand->v.c.major) {
				case INTCODE_NOP:
                    ncd = curCommand + (curCommand->v.c.cnt + 1);
					break;

				case INTCODE_LIT_VAL:
                    ncd = execCodeLitVal(curCommand);
					break;

				case INTCODE_FETCH:
                    ncd = execCodeFetch(curCommand);
					break;

				case INTCODE_FETCH_SPECIAL:
                    ncd = execCodeFetchSpecial(curCommand);
					break;

				case INTCODE_ASSIGN:
                    ncd = execCodeAssign(curCommand);
					break;

				case INTCODE_OPERATION:
                    ncd = execCodeOperation(curCommand);
					break;

				case INTCODE_CONSTRUCT:
                    ncd = execCodeConstruct(curCommand);
					break;

				case INTCODE_LINENAMEPREF:
                        ncd = curCommand + (curCommand->v.c.cnt + 1);
					//TODO
					break;

				case INTCODE_FUNCTION:
                    ncd = execCodeFunction(curCommand);
					if (!ncd) {
                        if (res) {
                            StackValue *sv = stackCur();
                            res->copyFrom(sv->val(), true, false);
                            pop();
                        }
                        PROTO_MOD_OUTL(_modp, "leave execution context (level " << _level << ") at code pos " << (unsigned)(curCommand - _modp->_code));
                        return;
					}
					break;

				case INTCODE_CODEBLOCK:
                    ncd = execCodeCodeblock(curCommand, cbBody, cbLvl, cbCancel, endCtx);
                    if (endCtx) {
                        if (_stackTop > stackTopStart) {
                            StackValue *sv = stackCur();
                            res->copyFrom(sv->val(), true, false);
                            pop();
                        }
                        else {
                            res->unset();
                        }
                        PROTO_MOD_OUTL(_modp, "leave execution context (level " << _level << ") for single codeblock body at code pos " << (unsigned)(curCommand - _modp->_code) << endl << "  -> body result: " << res);
                        return;
                    }
                    break;

                case INTCODE_CB_HEADER:
                    ncd = execCodeCBHeader(curCommand, cbHeader);
                    if (cbHeader && !cbLvl && curCommand->v.c.minor == ICS_CBHEADER_END) {
                        StackValue *sv = stackCur();
                        res->copyFrom(sv->val(), true, false);
                        pop();
                        PROTO_MOD_OUTL(_modp, "leave execution context (level " << _level << ") for single codeblock header at code pos " << (unsigned)(curCommand - _modp->_code) << endl << "  -> header result: " << res);
                        return;
                    }
                    break;

				case INTCODE_CB_CONTROL:
                    ncd = execCodeCBControl(curCommand, (cbHeader || cbBody), cbLvl, cbTopStart);
                    if (!ncd) {
                        stackPopTo(_stack + _stackTop, true);
                        if (cbHeader)
                            res->set(TP_BIN, false);
                        else
                            res->moveFrom(_opRes);

                        PROTO_MOD_OUTL(_modp, "leave execution context (level " << _level << ") for single codeblock header or body after control command at code pos " << (unsigned)(curCommand - _modp->_code) << endl << "  -> result: " << res);
                        return;
                    }
					break;

				default:
					internalError("invalid command in intermediary code");
			}

            curCommand = ncd;
		}

		_modp->ctrl()->errHandler().internalError(_modp->ctrl()->printBuffer("unexpected end of intermediary code, at code pos %u", _modp->_codeCnt));
	}


	/**
	 * executes intermediary code command for literal value
	 * @param cd		intermediary code command
	 * @return			next intermediary code position / NULL if you have to leave this execution context after the command
	 */
	IntCode::IcElem* ExecContext::execCodeLitVal(IntCode::IcElem *cd)
	{
		switch (cd->v.c.minor) {
			case ICS_LIT_INT:
				pushInt((cd->v.c.cnt ? cd[1].v.i : cd->v.c.par), cd->se);
				break;

			case ICS_LIT_STR:
				pushString((cd->v.c.cnt ? cd[1].v.i : cd->v.c.par), cd->se);
				break;

			case ICS_LIT_REAL:
				pushReal(cd[1].v.r, cd->se);
				break;

			case ICS_LIT_BLANK:
				pushBlank(cd->se);
				break;
		}

		return cd + (cd->v.c.cnt + 1);
	}

	/**
	 * executes intermediary code command for fetch a value
	 * @param cd		intermediary code command
	 * @return			next intermediary code position / NULL if you have to leave this execution context after the command
	 */
	IntCode::IcElem* ExecContext::execCodeFetch(IntCode::IcElem *cd)
	{
		unsigned int fetchId = cd[1].v.n.n2;

		SymbolValue *symval;
        CmplValAuto valCont(TP_EMPTY);
        bool needLockSym, needLockVS;

		if (cd->v.c.par & ICPAR_FETCH_SUBSYM) {
            CmplVal *base = stackCur()->simpleValue();
            fetchId = 0;

            if (!base || base->t != TP_CONTAINER) {
                valueError("left operand of subsymbol operator is not a container value", stackCur());
                symval = NULL;
            }
            else {
                ValContainer *cont = base->valContainer();
                {
                    needLockSym = _needLock;
                    LockGuard<mutex> lckC(_needLock, cont->accMtx());
                    symval = cont->getInsertSymbol(this, cd);
                }

                // distinct whether previous fetch was ICPAR_FETCH_NMSPACE (then addval of left operand is TP_STR)
                CmplVal& pav = stackCur()->_addVal;
                if (pav.t == TP_STR) {
                    if (cd->v.c.par & ICPAR_FETCH_NMSPACE) {
                        // concat symbol names for full namespace name
                        const char *nms = modp()->ctrl()->printBuffer("%s.%s", modp()->data()->globStrings()->at(pav.v.i), modp()->symbolInfo(symval->defId())->name());
                        valCont.set(TP_STR, (intType)(modp()->data()->globStrings()->storeInd(nms)));
                    }
                    else {
                        valCont.copyFrom(pav, true, false);
                    }
                }
                else if (!(cd->v.c.par & ICPAR_FETCH_LVALUE)) {
                    // use container value as addval of result
                    valCont.copyFrom(base, true, false);
                }
            }

            pop();
		}
        else if (cd->v.c.minor == ICS_FETCH_GLOBAL) {
            symval = _modp->_globSymbols + fetchId;
            needLockSym = _needLock;
        }
        else {
            symval = _localSymbols + fetchId;
            if (!symval->defId())
                symval->init((*_modp->_symbolInfo)[cd[1].v.n.n1], false, false);

            needLockSym = (_needLock && fetchId < _localSymbolCreateTo && !symval->readOnly());
		}

		StackValue *sv = pushPre(cd->se);
        if (cd->v.c.minor == ICS_FETCH_DEF_CB) {
            // code block symbol definition, use special value
            sv->_val.set(TP_DEF_CB_SYM, (intType) fetchId);
        }
        else if (cd->v.c.par & ICPAR_FETCH_LVALUE) {
			// lvalue, fetch as symbol value
            sv->_val.setP(TP_SYMBOL_VAL, symval);
		}
        else if (!symval) {
            // error, already reported
            sv->_val.set(TP_INT, 0);
        }
        else if (cd->v.c.par & ICPAR_FETCH_INCDEC) {
            intType i;
            {
                LockGuard<mutex> lckS(needLockSym, symval->accMtx());

                if (symval->readOnly() || !(symval->hasValueStore())) {
                    CmplVal v;
                    v.setP(TP_SYMBOL_VAL, symval);
                    valueError((symval->readOnly() ? "constant symbol used for increment/decrement" : "uninitialized symbol used for increment/decrement"), v, cd->se);
                    i = 0;
                }
                else {
                    needLockVS = (_needLock && (fetchId < _localSymbolCreateTo || symval->valueStore()->values()->refCnt() > 1));
                    LockGuard<mutex> lckV(needLockVS, symval->valueStore()->accMtx());

                    i = symval->valueStore()->fetchInc(this, (bool)(cd[2].v.n.n1), (cd[2].v.n.n2 ? 1 : -1), cd->se);
                }
            }

            sv->_val.set(TP_INT, i);
            sv->_syntaxElem = cd[2].se;
        }
        else {
            LockGuard<mutex> lckS(needLockSym, symval->accMtx());

            needLockVS = (_needLock && symval->hasValueStore() && !symval->valueStore()->isConst());
            LockGuard<mutex> lckV(needLockVS, symval->valueStore()->accMtx());

			// if simple value then fetch value directly to stack, else fetch as array
			CmplVal *v = symval->simpleValue();
			if (v)
				sv->_val.copyFrom(*v, true, false);
            else if (symval->valueStore())
                sv->_val.set(TP_ARRAY, symval->valueStore()->values(), true);
            else
                sv->_val.set(TP_NULL);		// value for symbol is not set
		}

        if (valCont) {
            sv->_addVal.moveFrom(valCont);
        }
        else if (cd->v.c.par & ICPAR_FETCH_NMSPACE) {
            const char *symNameStr = modp()->symbolInfo(symval->defId())->name();
            sv->_addVal.set(TP_STR, (intType)(modp()->data()->globStrings()->search(symNameStr)));
        }

		return cd + (cd->v.c.cnt + 1);
	}

    /**
     * executes intermediary code command for fetch of a pseudo symbol
     * @param cd		intermediary code command
     * @return			next intermediary code position / NULL if you have to leave this execution context after the command
     */
    IntCode::IcElem* ExecContext::execCodeFetchSpecial(IntCode::IcElem *cd)
    {
        bool lvalue = cd->v.c.par & ICPAR_FETCH_LVALUE;
        bool subsym = cd->v.c.par & ICPAR_FETCH_SUBSYM;

        if (cd->v.c.par & ICPAR_FETCH_INCDEC) {
            execError("increment/decrement not allowed with pseudo symbol", cd->se);
        }

        CmplVal *base = NULL;
        bool doPop = false;

        if (subsym) {
            base = stackCur()->simpleValue();

            if (!base) {
                valueError("invalid use of subsymbol operator", stackCur());

                CmplValAuto dv(TP_NULL);
                if (lvalue)
                    dv.set(TP_SPECIALSYM, new ValSpecialDummy(this, cd->se, lvalue, NULL));

                pop();
                pushVal(dv, cd->se);
                return cd + (cd->v.c.cnt + 1);
            }

            doPop = true;
        }

        CmplValAuto res(TP_NULL);
        if (lvalue) {
            res.set(TP_SPECIALSYM, ValSpecialBase::create(this, cd->v.c.minor, cd->se, lvalue, base));
        }
        else {
            // handle $arg and $this here for better performance
            if (cd->v.c.minor == ICS_SPECIAL_ARG || cd->v.c.minor == ICS_SPECIAL_THIS) {
                if (cd->v.c.minor == ICS_SPECIAL_ARG) {
                    if (_fctArg)
                        res.copyFrom(_fctArg->val(), true, false);
                    else
                        execError("pseudosymbol '$arg' cannot be used outside of a function", cd->se);
                }
                else {
                    if (_fctThis)
                        res.set(TP_CONTAINER, _fctThis);
                    else
                        execError("no '$this' container available", cd->se);
                }
            }
            else {
                CmplValAuto v(TP_SPECIALSYM, ValSpecialBase::create(this, cd->v.c.minor, cd->se, lvalue, base));
                ValSpecialBase *sp = v.valSpecial();

                if (sp->hasIndexedHandling())
                    res.moveFrom(v);
                else
                    sp->get(res);
            }
        }

        if (doPop)
            pop();

        pushVal(res, cd->se);
        return cd + (cd->v.c.cnt + 1);
    }

	/**
	 * executes intermediary code command for assign a value
	 * @param cd		intermediary code command
	 * @return			next intermediary code position / NULL if you have to leave this execution context after the command
	 */
	IntCode::IcElem* ExecContext::execCodeAssign(IntCode::IcElem *cd)
	{
		// get params
		unsigned cntLhs = cd->v.c.par & ICPAR_ASSIGN_CNTLHS;
		bool assignConst = cd->v.c.par & ICPAR_ASSIGN_CONST;
		bool assignOrdered = cd->v.c.par & ICPAR_ASSIGN_ORDERED;
        bool assignInitial = cd->v.c.par & ICPAR_ASSIGN_INITIAL;    //TODO
		bool setResName = cd->v.c.par & ICPAR_ASSIGN_RESNAME;
        PROTO_MOD_OUTL(_modp, "  cntLhs " << cntLhs << "; assignConst " << assignConst << "; assignInitial " << assignInitial << "; assignOrdered " << assignOrdered << "; setResName " << setResName);

		// get object type and data type
        _assObjType = -1;
        _assDataType = NULL;
        _assSyntaxElem = cd->se;
        _assStartVolaRhs = 0;
        _assNextRhs = false;

		if (cd->v.c.cnt > 0) {
            bool locAssType = cd->v.c.par & ICPAR_ASSIGN_OBJTYPE_LOCAL;
			unsigned i = cd[1].v.n.n1;
            if (i || locAssType) {
                SymbolValue *symval = (locAssType ? (_localSymbols + i) : (_modp->_globSymbols + i));
				CmplVal *v = symval->simpleValue();
				if (!v || v->t != TP_OBJECT_TYPE)
					internalError("given object type in assignment is not an object type");
                _assObjType = v->v.i;
			}

            locAssType = cd->v.c.par & ICPAR_ASSIGN_DATATYPE_LOCAL;
			i = cd[1].v.n.n2;
            if (i || locAssType) {
                SymbolValue *symval = (locAssType ? (_localSymbols + i) : (_modp->_globSymbols + i));
				CmplVal *v = symval->simpleValue();
				if (!v || v->t != TP_DATA_TYPE)
					internalError("given data type in assignment is not a data type");
                _assDataType = v->valType();
			}

			if (cd->v.c.cnt > 1)
                _assStartVolaRhs = cd[2].v.n.n1;
		}

        if (assignOrdered && !_assStartVolaRhs)
            assignOrdered = false;

		StackValue *svLhs;
        char op = '\0';

        _assRhs = stackCur();
        PROTO_MOD_OUTL(_modp,  "  rhs = " << _assRhs->val());
		
		if (cd->v.c.minor == ICS_ASSIGN_RHSONLY) {
            if (_assRhs->val().t == TP_NULL || (_assObjType != VAL_OBJECT_TYPE_CON && _assObjType != VAL_OBJECT_TYPE_OBJ)) {
                if (_assObjType == VAL_OBJECT_TYPE_VAR && _assRhs->val().t != TP_NULL) {
                    CmplValAuto t;
                    if (!checkContainerConvSpecial(t, _assRhs->val(), TP_OPT_VAR) || t.t != TP_NULL)
                        valueError("expression without assignment cannot be used with modificator 'var'", _assRhs);
                }
			}
            else if (setResName && (_assObjType == VAL_OBJECT_TYPE_CON || _assObjType == VAL_OBJECT_TYPE_OBJ)) {
                // convert right hand side to constraint or objective
                getCurAssignRhs(_assSyntaxElem);
			}
            stackPopTo(_assRhs);
        }
		else {
            switch (cd->v.c.minor) {
                case ICS_ASSIGN_LHSONLY:
                    assignInitial = true;
                    // no break

                case ICS_ASSIGN_EXTERN:
                    if (_assObjType == VAL_OBJECT_TYPE_OBJ || _assObjType == VAL_OBJECT_TYPE_CON)
                        valueError("alone left hand side cannot be used with modificator 'con' or 'obj'", _assRhs);
                    // no break

                case ICS_ASSIGN_ASSERT:
                    svLhs = _assRhs;
                    _assRhs = NULL;
                    break;

                case ICS_ASSIGN_REF:
                    if (!_assRhs->lvalue())
                        valueError("internal error: lvalue expected on stack, but not given", _assRhs, ERROR_LVL_FATAL);
                    if (_assRhs->hasIndex())
                        valueError("right hand side of ref assignment cannot have indexation", _assRhs);
                    _assObjType = -1;
                    _assDataType = NULL;
                    break;

                case ICS_ASSIGN_ADD:
                    op = '+';
                    break;
                case ICS_ASSIGN_SUB:
                    op = '-';
                    break;
                case ICS_ASSIGN_MUL:
                    op = '*';
                    break;
                case ICS_ASSIGN_DIV:
                    op = '/';
                    break;
            }

            if (_assRhs) {
                // if right hand side is a list then convert it to an array or tuple
                if (_assRhs->isList())
                    _assRhs = replaceListOnStack(_assRhs);

                //TODO: Wenn RHS Typ TP_SPECIALSYM, dann darin get aufrufen und auf stattdessen auf den Stack
                //          oder vielleicht diese Umwandlung mit in replaceListOnStack()?

                svLhs = stackPrev(_assRhs);
			}

            for (unsigned iLhs = 1; iLhs < cntLhs; iLhs++)
                svLhs = stackPrev(svLhs);

            StackValue *svLhsBase = svLhs;
            for (unsigned iLhs = 0; iLhs < cntLhs; iLhs++, svLhs++) {
                if (!svLhs->lvalue())
                    valueError("internal error: lvalue expected on stack, but not given", svLhs);
                else if (svLhs->val().t == TP_SYMBOL_VAL) {
                    SymbolValue *sym = (SymbolValue *)(svLhs->val().v.p);
                    if (sym) {
                        bool needLockSym = (_needLock && (sym->global() || (!sym->global() && (sym - _localSymbols) < _localSymbolCreateTo)));
                        LockGuard<mutex> lckS(needLockSym, sym->accMtx());

                        if (cd->v.c.minor == ICS_ASSIGN_EXTERN)
                            svLhs->importExtern(this, assignConst, cd->se);
                        else if (cd->v.c.minor == ICS_ASSIGN_ASSERT)
                            svLhs->checkAssert(this, assignConst, _assDataType, _assObjType, cd->se);
                        else
                            svLhs->doAssign(this, op, (cd->v.c.minor == ICS_ASSIGN_REF), assignConst, assignInitial, assignOrdered, setResName);
                    }
                }
                else {  // svLhs->val().t == TP_SPECIALSYM
                    if (cd->v.c.minor == ICS_ASSIGN_EXTERN || cd->v.c.minor == ICS_ASSIGN_ASSERT || cd->v.c.minor == ICS_ASSIGN_REF || assignConst || setResName)
                        valueError("invalid assign modificator for assign to pseudo symbol", svLhs);
                    else
                        svLhs->doAssignSpecial(this, op, assignInitial, assignOrdered);
                }
			}

            stackPopTo(svLhsBase);
		}

		return cd + (cd->v.c.cnt + 1);
	}


	/**
	 * executes intermediary code command for execution of an operation
	 * @param cd		intermediary code command
	 * @return			next intermediary code position / NULL if you have to leave this execution context after the command
	 */
	IntCode::IcElem* ExecContext::execCodeOperation(IntCode::IcElem *cd)
	{
        StackValue *sv1, *sv2;
        StackValue *sve = NULL;
        CmplVal *v;
        intType i;
        unsigned short ac;
        bool pushRes = true;
        bool transp = false;

		switch (cd->v.c.minor) {
			case ICS_OPER_FUNC:
				// function call
				sv1 = stackCur();
                sve = sv2 = stackPrev(sv1);
				v = sv2->simpleValue();

                if (!v)
                    valueError("function call for a not function-like value", sv2);

                if (v->t == TP_OBJECT_TYPE) {
                    //Umwandlung/Konstruktor
                    //TODO
                }
                else if (v->t == TP_FUNCTION || v->t == TP_DATA_TYPE) {
                    ValContainer *pt = _callThis;
                    _callThis = (sv2->_addVal.t == TP_CONTAINER ? sv2->_addVal.valContainer() : NULL);
                    if (!((ValFunctionBase *)(v->v.vp))->operCall(this, sv1))
                        valueError("internal error: unhandled function call", sv2, ERROR_LVL_FATAL);
                    _callThis = pt;
                }
                else if (v->toInt(i, typeConversionExact, modp())) {
                    // construct algorithmic set: first pseudo function call for expression like "1(1)(n)"
                    SetUtil::constructAlg(this, _opRes, sv2, sv1, NULL);
                }
                else if (SET_TP_WO_ORDER(*v) == TP_SET_R1_ALG && ((SetAlg *)(SET_VAL_WO_ORDER(*v).v.vp))->incomplete()) {
                    // construct algorithmic set: second pseudo function call for expression like "1(1)(n)"
                    SetUtil::constructAlg(this, _opRes, v->setBase(), sv1);
                }
                else {
                    valueError("internal error: unhandled function call", sv2, ERROR_LVL_FATAL);
                }
                break;

            case ICS_OPER_INDEX:
                // indexation operation
                sv1 = stackCur();
                sve = sv2 = stackPrev(sv1);

                if (!sv2->indexation(this, sv1)) {
                    pushRes = false;
                    sve = sv1;
                }
                break;

            default:
                // replace lists by arrays
                ac = cd->v.c.par & ICPAR_OPER_CNT;
                if (ac > 0) {
                    if (ac == 1) {
                        sve = sv1 = replaceListOnStack(stackCur());
                        sv2 = NULL;
                    }
                    else {
                        sv2 = replaceListOnStack(stackCur());
                        sve = sv1 = stackPrev(sv2);
                        if (sv1->isList()) {
                            CmplVal rl;
                            rl.setP(TP_REF_LIST, sv1);
                            pushVal(rl, sv1->syntaxElem());
                            sv1 = replaceListOnStack(stackCur());
                        }
                    }
                }
                else {
                    sve = sv1 = sv2 = NULL;
                }

                // execute operation
                if (!OperationBase::execOper(this, _opRes, transp, cd->se, cd->v.c.minor, (bool)(cd->v.c.par & ICPAR_OPER_CMP_FOLLOW), ac, sv1, sv2)) {
                    //TODO: sonstige Operation, insbesondere vielleicht in Codeblockheader (oder vielleicht doch gar nichts hier?)
                    // (fuer Transpose bei eindimensionalem Arrays hier weiter nichts zu tun, schon durch transp erledigt)
                    pushRes = false;
                    if (transp)
                        sve = NULL;
                }
                break;
		}

        if (sve)
            stackPopTo(sve);
        if (pushRes)
            pushOpResult(cd->se);

        if (transp)
            stackCur()->_transpose = true;

		return cd + (cd->v.c.cnt + 1);
	}


	/**
	 * executes intermediary code command for execution of a value construction
	 * @param cd		intermediary code command
	 * @return			next intermediary code position / NULL if you have to leave this execution context after the command
	 */
	IntCode::IcElem* ExecContext::execCodeConstruct(IntCode::IcElem *cd)
	{
		StackValue *sv1, *sv2, *sv3;
		StackValue *sve = NULL;
		unsigned long cnt = (cd->v.c.cnt ? (unsigned long)(cd[1].v.i) : cd->v.c.par);
		bool pushRes = true;

		switch (cd->v.c.minor) {
			case ICS_CONSTRUCT_ARRAY:
                if (cnt == 0) {
					_opRes.set(TP_NULL);
                }
                if (cnt == 1) {
                    if (stackCur()->val().t != TP_BLANK) {
                        pushRes = false;
                    }
                    else {
                        sve = stackCur();
                        _opRes.set(TP_NULL);
                    }
                }
                else
                {
                    sve = StackValue::constructList(this, _opRes, cnt, stackCur());
                }
				break;

			case ICS_CONSTRUCT_TUPEL:
                {
                    // keep index tuple as list on stack if next command is indexation operation, for better performance
                    IntCode::IcElem *nc = cd + cd->v.c.cnt + 1;
                    bool listTuple = (nc->v.c.major == INTCODE_OPERATION && nc->v.c.minor == ICS_OPER_INDEX);
                    sv1 = (cnt == 0 ? NULL : stackCur());
                    sve = TupleUtil::construct(this, _opRes, pushRes, cnt, listTuple, sv1);
                }
				break;

			case ICS_CONSTRUCT_IV_WOLB:
				if (cnt == 0) {
					Interval::construct(this, _opRes, NULL, NULL);
				}
				else {
					sv1 = sve = stackCur();
					Interval::construct(this, _opRes, NULL, sv1);
				}
				break;

			case ICS_CONSTRUCT_IV_LB:
				sv1 = stackCur();
				if (cnt == 1) {
					sve = sv1;
					Interval::construct(this, _opRes, sv1, NULL);
				}
				else {
					sv2 = sve = stackPrev(sv1);
					Interval::construct(this, _opRes, sv2, sv1);
				}
				break;

			case ICS_CONSTRUCT_SET:
				sv1 = stackCur();
				sv2 = stackPrev(sv1);
				sv3 = sve = stackPrev(sv2);
				SetUtil::constructAlg(this, _opRes, sv3, sv2, sv1);
				break;
		}

		if (sve)
			stackPopTo(sve);
		if (pushRes)
			pushOpResult(cd->se);

		return cd + (cd->v.c.cnt + 1);
	}


	/**
	 * executes intermediary code command for functions and jumps
	 * @param cd		intermediary code command
	 * @return			next intermediary code position / NULL if you have to leave this execution context after the command
	 */
	IntCode::IcElem* ExecContext::execCodeFunction(IntCode::IcElem *cd)
	{
		switch (cd->v.c.minor) {
			case ICS_FUNC_START:
				internalError("unexpected function start in intermediary code");
				break;

			case ICS_FUNC_END:
				if (!_fctContext)
					internalError("unexpected function end in intermediary code");
				return NULL;

			case ICS_FUNC_STORE:
                // construct user function object and push it on the stack
                _opRes.set(TP_FUNCTION, new ValFunctionUser(cd[1].v.n.n1));
                pushOpResult(cd->se);
				return _modp->_code + cd[1].v.n.n2;

			case ICS_FUNC_GOTO:
				return _modp->_code + cd[1].v.n.n1;

			default:
				internalError("invalid function subcommand in intermediary code");
		}

		return cd + (cd->v.c.cnt + 1);
	}


    /**
     * executes intermediary code command for code blocks
     * @param cd		intermediary code command
     * @param cbBody    execution for a single codeblock body
     * @param cbLvl     level of nested codeblocks
     * @param cbCancel  cancelling codeblock at level _cancelCbLvl; skip new codeblock if new one starts
     * @param endCtx    return whether execution in this execution context is ended
     * @return			next intermediary code position / NULL if you have to leave this execution context after the command
     */
    IntCode::IcElem* ExecContext::execCodeCodeblock(IntCode::IcElem *cd, bool cbBody, unsigned& cbLvl, bool& cbCancel, bool &endCtx)
    {
        if (cbBody && !cbLvl && cd->v.c.minor != ICS_CB_BLOCK_START) {
            endCtx = (cd->v.c.minor == ICS_CB_PART_END);
            return cd + (cd->v.c.cnt + 1);
        }

        CodeBlockContext *cb;
        bool toBlockEnd = false, directBlockEnd = false;
        endCtx = false;

        switch (cd->v.c.minor) {
            case ICS_CB_BLOCK_START:
                if (cbCancel) {
                    // dummy result TP_NULL for skipped codeblock; continue execution after codeblock end
                    pushNull(cd->se);
                    cd = codeBase() + cd[1].v.n.n1;
                    break;
                }

                cbLvl++;
                cb = CodeBlockContext::newContext(this, cd);
                pushCBContext(cb, cd->se);
                break;

            case ICS_CB_PART_START:
                cb = getCBContext();
                if (cb) {
                    cb->startPart(cd);
                }
                break;

            case ICS_CB_PART_BODY:
                cb = getCBContext();
                if (cb) {
                    cb->execPartBody(cd);
                    return codeBase() + cd[1].v.n.n2;
                }
                break;

            case ICS_CB_PART_END:
                if (cbCancel) {
                    toBlockEnd = true;
                }
                else {
                    cb = getCBContext();
                    if (cb) {
                        toBlockEnd = cb->endPart();
                    }
                    else {
                        if (cd->v.c.par & ICPAR_BLOCK_STMNT) {
                            // result value of code block without result expression is "null"
                            pushNull(cd->se);
                        }

                        uninitCBSymbols(cd[2].v.n.n2, cd[2].v.n.n1, true);

                        // directly proceed with ICS_CB_BLOCK_END
                        directBlockEnd = true;
                    }
                }

                // go to end of code block
                if (!directBlockEnd) {
                    if (!toBlockEnd)
                        break;
                    else
                        return codeBase() + cd[1].v.n.n1;
                }

                // directly proceed with ICS_CB_BLOCK_END
                cd = codeBase() + cd[1].v.n.n1;
#if PROTO
                if (_modp->isProtocol()) {
                    cd->protoOut(_modp, (unsigned)(cd - codeBase()));
                    for (unsigned i = 1; i <= cd->v.c.cnt; i++)
                        cd[i].protoOut(_modp, (unsigned)(cd + i - codeBase()));
                }
#endif
                // *NO* break

            case ICS_CB_BLOCK_END:
                if (cbCancel) {
                    LockGuard<recursive_mutex> lck(_needLock, _cancelMtx);
                    if (_cbContextTop == _cancelCbLvl + 1) {
                        _cancel = false;
                        cbCancel = false;

                        cb = getCBContext();
                        if (!cb)
                            internalError("inconsistency in codeblock cancelling");

                        IntCode::IcElem *repStart = cb->checkStartRepeat();
                        if (repStart)
                            return repStart + (repStart->v.c.cnt + 1);;
                    }
                }

                cbLvl--;
                cb = getCBContext();
                if (cb) {
                    CmplVal& res = cb->cbResult();
                    if (res.t == TP_BLANK)
                        pushNull(cd->se);
                    else
                        pushVal(res, cd->se, true);
                }
                else {
                    // result value of code block without executed part is "null"
                    if (!toBlockEnd && !directBlockEnd)
                        pushNull(cd->se);
                }

                popCBContext(cd->se);
                break;

            default:
                internalError("invalid function subcommand in intermediary code");
        }

        return cd + (cd->v.c.cnt + 1);
    }


    /**
     * executes intermediary code command for code block headers
     * @param cd		intermediary code command
     * @param cbHeader  execution for a single codeblock header
     * @return			next intermediary code position / NULL if you have to leave this execution context after the command
     */
    IntCode::IcElem* ExecContext::execCodeCBHeader(IntCode::IcElem *cd, bool cbHeader)
    {
        CodeBlockContext *cb = getCBContext();
        StackValue *sv;
        CmplVal *v;
        CmplValAuto cbhRes;
        bool b = false;

        switch (cd->v.c.minor) {
            case ICS_CBHEADER_START:
                if (!cbHeader && cb && (cd->v.c.par & ICPAR_CBHP_HCNT) && (((cd->v.c.par & ICPAR_CBHP_PHCBS) || (cb->ordered() && (cd->v.c.par & ICPAR_CBHP_NCSYM))))) {
                    // don't execute header now, but store it in codeblock context
                    cb->storeHeader(cd);
                    cd = codeBase() + cd[1].v.n.n1;
                }
                break;

            case ICS_CBHEADER_END:
                sv = stackCur();
                v = sv->simpleValue();

                if (v && (v->t == TP_CBHEAD_ITER || (v->t == TP_FORMULA && v->valFormula()->isBool()) || v->toBool(b, typeConversionAll, _modp))) {
                    bool nextPart = false;

                    if (v->t == TP_CBHEAD_ITER) {
                        CBHeaderIterInfo *cbhIter = (CBHeaderIterInfo *)(v->v.p);
                        v->unset();

                        if (SetBase::empty(cbhIter->iterSet())) {
                            nextPart = true;
                            cbhRes.set(TP_BIN, false);
                            delete cbhIter;
                        }
                        else if (cbHeader) {
                            cbhRes.setP(TP_CBHEAD_ITER, cbhIter);
                        }
                        else if (cb) {
                            cb->storeHeader(cbhIter, cd);
                        }
                        else {
                            delete cbhIter;
                            internalError("missing codeblock context for iteration");
                        }
                    }
                    else if (b || v->t == TP_FORMULA) {
                        if (cbHeader) {
                            if (v->t == TP_FORMULA)
                                cbhRes.copyFrom(v);
                            else
                                cbhRes.set(TP_BIN, true);
                        }
                        else {
                            if (cb && (cd->v.c.par & ICPAR_CBHP_HCNT) == 0)
                                cb->storeHeader(NULL, cd);

                            if (v->t == TP_FORMULA) {
                                //TODO: variablenhaltige Bedingung
                                //TODO: Codeblockcontext wird benoetigt, dort effektive Bedingung pro Codeblockpart verwalten
                                internalError("not implemented");
                            }
                        }
                    }
                    else {
                        nextPart = true;
                        cbhRes.set(TP_BIN, false);
                    }

                    if (!cbHeader && nextPart) {
                        // go to next part or to end of code block, get address from first argument of this command
                        pop();
                        return codeBase() + cd[1].v.n.n1;
                    }
                }
                else {
                    valueError("codeblock header must be a boolean expression", sv);
                    cbhRes.set(TP_BIN, false);
                }

                pop();
                if (cbHeader) {
                    pushVal(cbhRes, cd->se);
                }
                break;

            default:
                internalError("invalid function subcommand in intermediary code");
        }

        return cd + (cd->v.c.cnt + 1);
    }


    /**
     * executes intermediary code command for code blocks
     * @param cd		intermediary code command
     * @param cbHB      execution for a single codeblock header or body
     * @param cbLvl     level of nested codeblocks
     * @param cbTS      start level of nested codeblocks
     * @return			next intermediary code position / NULL if you have to leave this execution context after the command
     */
    IntCode::IcElem* ExecContext::execCodeCBControl(IntCode::IcElem *cd, bool cbHB, unsigned cbLvl, unsigned cbTS)
    {
        IntCode::IcElem *res = cd + (cd->v.c.cnt + 1);

        unsigned diffLvl = cd->v.c.par & ICPAR_CBC_CNTLVL;
        CodeBlockContext *cbDst = getCBContext(diffLvl);

        bool hasLhs = cd->v.c.par & ICPAR_CBC_HASLHS;
        bool lhsTuple = cd->v.c.par & ICPAR_CBC_LHSTUPLE;
        bool rhsValue = cd->v.c.par & ICPAR_CBC_RHSVALUE;

        if (!cbDst || (diffLvl && !hasLhs) || (!diffLvl && (!cbHB || cbLvl))) {
            internalError("inconsistency in codeblock context objects while executing control command");
            return cd + (cd->v.c.cnt + 1);
        }

        StackValue *svRhs = NULL, *svTpl = NULL, *sve = NULL;
        if (rhsValue) {
            svRhs = sve = stackCur();
            if (lhsTuple)
                svTpl = sve = stackPrev(svRhs);
        }
        else if (lhsTuple) {
            svTpl = sve = stackCur();
        }

        _opRes.set(TP_BLANK);

        switch (cd->v.c.minor) {
            case ICS_CBC_CONTINUE:
                if (diffLvl) {
                    cbDst->controlCommand(this, cd->v.c.minor, _cbContextTop - 1, svTpl, svRhs);
                    res = codeBase() + cd[1].v.n.n1;
                }
                else if (hasLhs) {
                    cbDst->assignResult(svRhs, svTpl);
                }
                else {
                    if (svRhs)
                        _opRes.copyFrom(svRhs->val(), true, false);
                }
                break;

            case ICS_CBC_BREAK:
            case ICS_CBC_REPEAT:
                cbDst->controlCommand(this, cd->v.c.minor, _cbContextTop - 1, svTpl, svRhs);
                res = codeBase() + cd[1].v.n.n2;
                break;

            default:
                internalError("invalid function subcommand in intermediary code");
        }

        if (sve)
            stackPopTo(sve);

        if (cbHB && !cbLvl)
            return NULL;
        else
            return res;
    }



	/**
	 * prepare stack to push a value
	 * @param se			syntax element in the cmpl text creating this stack value
	 * @return				stack element to take up the value to push
	 */
	StackValue* ExecContext::pushPre(unsigned se)
	{
		if (_stackTop == _stackCap) {
			_stackCap = ARR_NEWCAP(_stackCap);
			ARR_REALLOC(_stack, StackValue, _stackTop, _stackCap);
		}

		StackValue *sv = _stack + _stackTop++;
		PROTO_MOD_OUTL(_modp, "pushPre: " << _stackTop << " (" << se << ')');

		sv->init(se);
		return sv;
	}

	/**
	 * pointer to previous element on the stack relative to a given element
	 * @param sv		given base element
	 * @param err		true: if sv is already the first element then error / false: then return NULL
	 * @return			element before sv
	 */
    StackValue* ExecContext::stackPrev(StackValue *sv, bool err)
	{
		PROTO_MOD_OUTL(_modp, "stackPrev: " << (sv - _stack));

		if (sv > _stack) {
			if (!sv->_val.isList() || sv->_val.t == TP_REF_LIST) {
				PROTO_MOD_OUTL(_modp, "  -> " << sv[-1].val());
				return sv - 1;
			}

            unsigned long cnt = stackListTotalCnt(sv);
            if ((unsigned long)(sv - _stack) >= cnt) {
                PROTO_MOD_OUTL(_modp, "  -> " << sv[-cnt].val());
                return sv - cnt;
			}
		}

		if (err)
			internalError("stack underflow");

		return NULL;
	}

	/**
	 * pointer to previous element on the stack relative to a given element (static version, no check for underflow possible)
	 * @param sv		given base element
	 * @return			element before sv
	 */
	StackValue* ExecContext::stackPrevStatic(StackValue *sv)
	{
		if (!sv->_val.isList() || sv->_val.t == TP_REF_LIST)
			return sv - 1;
		else
            return sv - stackListTotalCnt(sv);
	}

    /**
     * get total count of stack values for a list
     * @param sv		list header element
     * @return			total count of elements on the stack for the list
     */
    unsigned long ExecContext::stackListTotalCnt(StackValue *sv)
    {
        unsigned long cnt;
        if (sv->_addVal.t == TP_INT) {
            cnt = sv->_addVal.v.i;
        }
        else {
            if (sv->_val.t == TP_LIST_SIMPLE || sv->_val.t == TP_LIST_SPARSE || sv->_val.t == TP_LIST_TUPLE) {
                cnt = sv->_val.v.i;
            }
            else {
                unsigned long c = 1, sz = sv->_val.v.i;
                StackValue *a = sv;

                cnt = 0;
                while (sz) {
                    a -= c;
                    if (!a->_val.isList() || a->_val.t == TP_REF_LIST)
                        c = 1;
                    else
                        c = stackListTotalCnt(a);

                    cnt += c;
                    sz--;
                }
            }

            sv->_addVal.set(TP_INT, (intType)cnt);
        }

        return cnt + 1;
    }

    /**
	 * discards the value on top of stack
	 */
	void ExecContext::pop()
	{
		if (_stackTop == 0)
			internalError("stack underflow");

		StackValue *sv = _stack + --_stackTop;

		if (sv->_val.isList() && sv->_val.t != TP_REF_LIST) {
			// direct list on stack, discard all values of the list
            unsigned long cnt = stackListTotalCnt(sv) - 1;
            if (_stackTop < cnt)
				internalError("stack underflow");

			_stackTop -= cnt;

			sv->unsetValue();
			for (unsigned long i = 0; i < cnt; i++, sv--)
				sv->unsetValue();
		}
		else {
			sv->unsetValue();
		}

		PROTO_MOD_OUTL(_modp, "pop: " << _stackTop);
	}

	/**
	 * discards value on the stack up to given element
	 * @param sv		given base element
	 * @param incl		discard also element sv
	 */
	void ExecContext::stackPopTo(StackValue *sv, bool incl)
	{
		// discard elements over sv
		StackValue *top = _stack + _stackTop;
		for (StackValue *s = sv + 1; s < top; s++)
			s->unsetValue();

		_stackTop = (sv - _stack) + 1;
		PROTO_MOD_OUTL(_modp, "popTo: " << _stackTop);

		// discard element sv
		if (incl)
			pop();
	}

    /**
     * replace a list value on the stack by an array or tuple
     * @param sv		list header
     * @return 			result value
     */
    StackValue *ExecContext::replaceListOnStack(StackValue *sv)
    {
        if (sv->isList()) {
            if (sv != stackCur())
                valueError("internal error: list value must be the topmost stack element to replace it", sv);

            CmplVal a;
            unsigned se = sv->syntaxElem();
            StackValue *lb;

            if (sv->val().t == TP_LIST_TUPLE) {
                TupleUtil::constructFromList(this, a, sv);
                lb = sv - (sv->val().v.i + 1);
            }
            else {
                lb = StackValue::arrayFromList(this, a, sv);
            }

            stackPopTo(lb);
            pushVal(a, se, true);
            return stackCur();
        }
        else {
            return sv;
        }
    }


    /**
     * get from stack value (which can be array or list) the first scalar values
     * @param sv            source stack value
     * @param maxCnt        max count of scalar values to fetch
     * @param args          array for returning fetched scalar values
     * @param se            array for returning syntax element numbers of fetched scalar values
     * @return              count of found values (can be greater than maxCnt if more values are found) / 0: found values are not scalar
     */
    unsigned ExecContext::getFirstSimpleValues(StackValue *sv, unsigned maxCnt, CmplVal *args, unsigned *se)
    {
        CmplVal& v = sv->val();
        if (v.isArray()) {
            CmplArrayIterator iter(*(v.array()));
            unsigned i = 0;

            for (iter.begin(); iter; iter++, i++) {
                if (i == maxCnt)
                    break;

                const CmplVal& t = iter.curTuple();
                if ((t.t != TP_INT && t.t != TP_ITUPLE_1INT) || t.v.i != (i + 1) || (*iter)->isArray())
                    return 0;

                args[i].copyFrom(*iter, true, false);
                se[i] = sv->syntaxElem();
            }

            return i;
        }

        else if (v.isList()) {
            StackValue *lst = sv;
            bool rf = (v.t == TP_REF_LIST);

            if (rf) {
                while (lst->val().t == TP_REF_LIST)
                    lst = (StackValue *)(lst->val().v.p);
            }

            unsigned long cnt = lst->val().v.i;
            StackValue *lb;
            if (lst->val().t != TP_LIST_SIMPLE && lst->val().t != TP_LIST_SPARSE) {
                lb = lst - 1;
                for (unsigned long i = 0; i < cnt; i++, lb--) {
                    if (lb->val().isList() || lb->val().isArray())
                        return 0;
                }
            }

            lb = lst - cnt;
            unsigned ic = (cnt < maxCnt ? (unsigned)cnt : maxCnt);

            for (unsigned i = 0; i < ic; i++, lb++) {
                args[i].copyFrom(lb->val(), true, false);
                se[i] = (rf ? sv->syntaxElem() : lb->syntaxElem());
            }

            return (cnt <= maxCnt ? (unsigned)cnt : (maxCnt + 1));
        }

        else {
            if (maxCnt) {
                args[0].copyFrom(v, true, false);
                se[0] = sv->syntaxElem();
            }
            return 1;
        }

        //TODO
        return 0;
    }



    /****** code block handling ****/

    /**
     * push an object to the code block context start
     * @param cb            code block context object or NULL if no context is needed
     * @param se			syntax element in the cmpl text creating this code block context object
     */
    void ExecContext::pushCBContext(CodeBlockContext *cb, unsigned se)
    {
        if (_cbContextTop == _cbContextCap) {
            _cbContextCap = ARR_NEWCAP(_cbContextCap);
            ARR_REALLOC(_cbContext, CodeBlockContext *, _cbContextTop, _cbContextCap);
        }

        _cbContext[_cbContextTop++] = cb;
        PROTO_MOD_OUTL(_modp, "pushCBContext: " << _cbContextTop << " (" << se << ')');
    }

    /**
     * get next upper existing code block context object on the code block stack
     * @param lvl       start position in the code block stack
     * @return          code block context object or NULL if no such context object exists
     */
    CodeBlockContext *ExecContext::getNextUpperCBContext(unsigned lvl)
    {
        unsigned i = lvl + 1;
        if (i >= _cbContextTop)
            return NULL;

        CodeBlockContext **res = _cbContext + i;
        if (*res)
            return *res;

        for (i++, res++; i < _cbContextTop; i++, res++) {
            if (*res)
                return *res;
        }

        return NULL;
    }

    /**
     * pop and discard code block context objects
     * @param se			syntax element in the cmpl text creating this code block context object
     * @param cnt           count of code block context objects to discard
     */
    void ExecContext::popCBContext(unsigned se, unsigned cnt)
    {
        while (cnt && _cbContextTop) {
            cnt--;
            _cbContextTop--;

            if (_cbContext[_cbContextTop]) {
                delete _cbContext[_cbContextTop];
            }

            PROTO_MOD_OUTL(_modp, "popCBContext: " << (_cbContextTop+1) << " (" << se << ')');
        }

        //TODO
    }


    /**
     * set value for codeblock symbol
     * @param n         number of codeblock symbol within array _localSymbols
     * @param va        value as CmplVal
     * @param vb        value as StackValue (only used if no <code>va</code>)
     */
    void ExecContext::setCBSymbolVal(unsigned n, const CmplVal *va, StackValue *vb)
    {
        SymbolValue *sym = _localSymbols + n;

        if (!sym->isUninitialized())
            internalError("double initialization for codeblock symbol");

        if (va) {
            sym->setSimpleConstVal(*va);
        }
        else if (vb) {
            CmplVal *vs = vb->simpleValue();
            if (vs) {
                sym->setSimpleConstVal(*vs);
            }
            else {
                ValueStore *store = sym->valueStore(true);
                store->setValue(this, vb, true);
                sym->setReadOnly();
            }
        }
    }

    /**
     * uninitialize local symbols
     * @param n         number of first symbol within array _localSymbols
     * @param to        max number of symbol + 1
     * @param delId		unset also SymbolValue::_defId
     */
    void ExecContext::uninitCBSymbols(unsigned n, unsigned to, bool delId)
    {
        for (SymbolValue *sym = _localSymbols + n; n < to; n++, sym++) {
            if (!sym->isUninitialized()) {
                sym->unset(delId, true);
            }
        }
    }


    /**
     * set and propagate cancel flag
     * @param cmd		control command (one of ICS_CBC_BREAK, ICS_CBC_CONTINUE, ICS_CBC_REPEAT)
     * @param dstLvl	nesting codeblock level of destination codeblock of the control command
     */
    void ExecContext::setCancel(int cmd, unsigned dstLvl)
    {
        LockGuard<recursive_mutex> lck(true, _cancelMtx);
        if (!_cancel || dstLvl < _cancelCbLvl || (dstLvl == _cancelCbLvl && _cancelCont && cmd != ICS_CBC_CONTINUE)) {
            _cancel = true;
            _cancelCont = (cmd == ICS_CBC_CONTINUE);
            _cancelCbLvl = dstLvl;

            for (unsigned n = max(dstLvl + 1, _cbContextCreateTop); n < _cbContextTop; n++) {
                if (_cbContext[n])
                    _cbContext[n]->setCancel(cmd, dstLvl);
            }
        }
    }



    /****** assignment ****/

    /**
     * get right hand side value for the current assignment
     * @param se		id of syntax element for use as default
     * @return 			right hand side value on the stack
     */
    StackValue *ExecContext::getCurAssignRhs(unsigned se)
    {
        if (_assNextRhs) {
            if (_assStartVolaRhs) {
                //TODO:
                //	Code ab _assStartVolaRhs erneut ausfuehren bis zur aktuellen Codeposition (moeglichst direkt in diesem ExecContext)
                //	dadurch wird RHS neu oben auf dem Stack hinterlassen, darauf _assRhs setzen
                stackPopTo(_assRhs, false);	//nur vorlaeufig
                valueError("volatile right hand side value not implemented", _assRhs);
                //stackPopTo(_assRhs, true);
                //run(_assStartVolaRhs, _curCommand);
                //_assRhs = stackCur();
            }
            else {
                if (_assRhs)
                    stackPopTo(_assRhs, false);
                else
                    pop();
            }
        }
        else if (!_assRhs) {
            // push default value to stack
            if (_assObjType == VAL_OBJECT_TYPE_CON || _assObjType == VAL_OBJECT_TYPE_OBJ) {
                valueError("no constraint or objective given within 'con' or 'obj'", stackCur());
                pushEmpty(se);
                _assRhs = stackCur();
            }
            else if (_assObjType == VAL_OBJECT_TYPE_VAR) {
                if (_assDataType) {
                    _assRhs = pushPre(se);
                    _assRhs->val().set(TP_DATA_TYPE, _assDataType);
                    _assDataType = NULL;
                }
            }
            else {
                _assRhs = pushPre(se);
                if (_assDataType && _assDataType->baseType() != TP_CONTAINER) {
                    _assDataType->defValCopy(_assRhs->val());
                    _assDataType = NULL;
                }
            }
        }

        if (_assRhs && _assRhs->isList())
            _assRhs = replaceListOnStack(_assRhs);

        StackValue *res = _assRhs;
        bool volRes = false;

        // convert to object type
        if (_assObjType != -1) {
            res = pushPre(_assRhs ? _assRhs->syntaxElem() : se);
            ObjectTypeUtil::convertTo(this, res->val(), _assObjType, _assRhs, _assSyntaxElem, res->syntaxElem());

            if (_assObjType != VAL_OBJECT_TYPE_PAR)
                volRes = true;
        }

        // convert to data type
        if (_assDataType) {
            StackValue *sv = res;
            res = pushPre(sv->syntaxElem());
            _assDataType->convertTo(this, res->val(), sv);
        }

        if (_assObjType == VAL_OBJECT_TYPE_VAR) {
            res->fixDataTypeVar();
        }

        if (volRes || _assStartVolaRhs)
            _assNextRhs = true;

        return res;
    }


    /****** utility functions ****/

    /**
     * check if source value is a container with a defined special convert function, and call this function
     * @param dst       store for result value of the called function
     * @param src       source value
     * @param tp        type of convert
     * @return          true if special convert function is found and called
     */
    bool ExecContext::checkContainerConvSpecial(CmplVal& dst, const CmplVal& src, tp_e tp)
    {
        if (src.t != TP_CONTAINER)
            return false;

        // get symbol number of searched element
        unsigned symIdSub;
        switch (tp) {
            case TP_OPT_VAR: symIdSub = modp()->symIdSubAsVar(); break;
            case TP_OPT_CON: symIdSub = modp()->symIdSubAsCon(); break;
            case TP_OPT_OBJ: symIdSub = modp()->symIdSubAsObj(); break;
            case TP_STR:     symIdSub = modp()->symIdSubAsString(); break;
            default:
                return false;
        }

        // check for function
        ValContainer *cont = src.valContainer();
        SymbolValue *sy = cont->getSimple(symIdSub, (_curCommand ? _curCommand - codeBase() : NULL));

        if (!sy)
            return false;

        CmplVal *vf = sy->simpleValue();
        if (!vf || vf->t != TP_FUNCTION)
            return false;

        // call function, with empty argument value, and with the container as $this
        CmplValAuto tmp;
        tmp.moveFrom(_opRes);

        StackValue arg;
        arg.init(_curCommand ? _curCommand->se : 0);
        arg.val().set(TP_NULL);

        ValContainer *pt = setCallThis(cont);
        vf->valFunction()->operCall(this, &arg);
        setCallThis(pt);

        dst.moveFrom(_opRes);
        _opRes.moveFrom(tmp);

        return true;
    }


	/****** error handling ****/

	/**
	 * internal error
	 * @param msg		error message
	 */		
	void ExecContext::internalError(const char *msg)
	{
		ostringstream ostr;
		ostr << msg << ", at code pos ";

#if PROTO
		_curCommand->protoOut(_modp, (unsigned)(_curCommand - _modp->_code), &ostr);
#else
		ostr << (unsigned)(_curCommand - _modp->_code);
#endif

		_modp->ctrl()->errHandler().internalError(ostr.str().c_str());
	}

    /**
     * other execution error
     * @param msg		error message
     * @param se		syntax element id of source value
     * @param level		one of ERROR_LVL_*
     */
    void ExecContext::execError(const char *msg, unsigned se, int level)
    {
        const SyntaxElement *sep = _modp->syntaxElement(se);

        ostringstream ostr;
        ostr << msg;

        const char *stxt = sep->text();
        if (stxt)
            ostr << ", at '" << stxt << "'";

#if PROTO
        if (_modp->isProtocol()) {
            *(_modp->protoStream()) << "error: " << msg << ", at code pos ";
            _curCommand->protoOut(_modp, (unsigned)(_curCommand - _modp->_code));
        }
#endif

        _modp->ctrl()->errHandler().error(level, ostr.str().c_str(), sep->loc());
    }

    /**
     * value is not suited for the current intermediary code command
     * @param msg		error message
     * @param val		value
     * @param se		syntax element id of source value
     * @param level		one of ERROR_LVL_*
     */
    void ExecContext::valueError(const char *msg, CmplVal& val, unsigned se, int level)
	{
        const SyntaxElement *sep = _modp->syntaxElement(se);

		ostringstream ostr;
		ostr << msg << " '";
        val.write(ostr, _modp);		//TODO: spezielle Werte anders ausgeben (z.B. SymbolValue)
		ostr << "'";

        const char *stxt = sep->text();
		if (stxt)
			ostr << ", at '" << stxt << "'";

#if PROTO
		if (_modp->isProtocol()) {
			*(_modp->protoStream()) << "error: " << msg << ", at code pos ";
			_curCommand->protoOut(_modp, (unsigned)(_curCommand - _modp->_code));
		}
#endif

        _modp->ctrl()->errHandler().error(level, ostr.str().c_str(), sep->loc());
	}

    /**
     * @param tp		type of failing assertion
     * @param ase		syntax element id of assert command
     * @param vse       syntax element id of failing value / 0: in assert command itself
     * @param level		one of ERROR_LVL_*
     */
    void ExecContext::assertionError(const char *tp, unsigned ase, unsigned vse, int level)
    {
        const char *msg1 = _modp->ctrl()->printBuffer("assertion about %s failed", tp);
        const SyntaxElement *asep = _modp->syntaxElement(ase);

        if (vse) {
            const SyntaxElement *vsep = _modp->syntaxElement(vse);
            _modp->ctrl()->errHandler().error(level, msg1, vsep->loc(), "for given assertion", asep->loc());
        }
        else {
            _modp->ctrl()->errHandler().error(level, msg1, asep->loc());
        }
    }

}

