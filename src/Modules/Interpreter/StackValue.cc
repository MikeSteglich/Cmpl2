
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

#include "StackValue.hh"
#include "Interpreter.hh"
#include "ExecContext.hh"
#include "Interval.hh"
#include "SetUtil.hh"
#include "SetInfinite.hh"
#include "TupleUtil.hh"
#include "ValType.hh"
#include "ValSpecial.hh"
#include "OperationBase.hh"
#include "../../Control/MainControl.hh"


namespace cmpl
{

	/*********** StackValue **********/

    /**
     * get whether TP_SPECIALSYM value can be an lvalue
     */
    bool StackValue::specialSymLval()
    {
        return (_val.t == TP_SPECIALSYM && _val.valSpecial()->canLvalue());
    }


	/**
	 * check if this stack value is TP_STRINGP (only value direct in _val can be it) and change it then to TP_STR
	 * @param ctx			execution context
	 * @return				true if value is changed to TP_STR
	 */
    void StackValue::ifStringPChangeToStr(ExecContext *ctx)
    {
        if (_val.t == TP_STRINGP) {
            _val.stringPToStr(ctx->modp());
        }
    }


    /**
     * perform indexation operation and store result in execution context
     * @param ctx			execution context
     * @param ind			index value
     * @return				true: result stored in execution context / false: this changed to result
     */
    bool StackValue::indexation(ExecContext *ctx, StackValue *ind)
    {
        // check for special operation on data type
        CmplVal *v = simpleValue();
        if (v && (v->t == TP_DATA_TYPE || v->t == TP_FUNCTION)) {
            // check for special handling of indexation operation
            ValFunctionBase *fb = (ValFunctionBase *)(v->v.vp);
            if (fb->operIndex(ctx, ind))
                return true;
        }

        if (lvalue()) {
            // store index value as _addVal in this
            if (_addVal) {
                if (hasIndex()) {
                    ctx->valueError("multiple indexation not allowed for lvalue", ind);
                    return false;
                }

                _addVal.dispUnset();
            }

            TupleUtil::toIndexTuple(ctx, _addVal, ind, false);
            return false;
        }

        // check if indexation with index tuple or with set
        CmplValAuto ci;
        unsigned its = 0;

        if (ind->_val.t == TP_LIST_TUPLE) {
            ci.set(TP_LIST_TUPLE, ind->_val.v.i);
        }
        else {
            if (ind->_val.isTuple() || ind->_val.isSet()) {
                ci.copyFrom(ind->_val);
            }
            else if (!SetUtil::convertToSetOrTuple(ctx, ci, ind->_val, typeConversionExact, true)) {
                ctx->valueError("value not usable for indexation", ind);
                return false;
            }

            if (!ci.isITuple()) {
                if (ci.isSet() || !ci.useValP()) {
                    its = 1;
                }
                else {
                    Tuple *tpl = ci.tuple();
                    if (tpl->tupleType() != Tuple::tupleIndexOnly) {
                        for (unsigned r = 0; r < tpl->rank(); r++) {
                            if (!tpl->at(r)->isScalarIndex()) {
                                its = r + 1;
                                break;
                            }
                        }
                    }
                }
            }
        }

        // do indexation
        return indexation(ctx, ci, its, ind);
    }

    /**
     * perform indexation operation
     * @param ctx			execution context
     * @param ind			index value (must be tuple or set)
     * @param its           number of first index part containing a set + 1 / 0: all index parts are scalar
     * @param orgInd        original index value
     * @return				true: result stored in execution context / false: this changed to result
     */
    bool StackValue::indexation(ExecContext *ctx, CmplVal& ind, unsigned its, StackValue *orgInd)
    {
        // handle lists
        if (_val.isList()) {
            StackValue *lst = this;
            while (lst->_val.t == TP_REF_LIST)
                lst = (StackValue *)(lst->_val.v.p);

            if (lst->_val.t == TP_LIST_TUPLE) {
                StackValue tp;
                tp.init(lst->_syntaxElem);
                TupleUtil::constructFromList(ctx, tp._val, lst);

                if (!tp.indexation(ctx, ind, its, orgInd))
                    ctx->opResult().moveFrom(tp._val, false);

                tp.unsetValue();
                return true;
            }
            else {
                if (ind.t == TP_LIST_TUPLE) {
                    CmplValAuto ci;
                    TupleUtil::constructFromList(ctx, ci, orgInd);
                    return lst->indexationList(ctx, ci, its, orgInd);
                }
                else {
                    return lst->indexationList(ctx, ind, its, orgInd);
                }
            }
        }

        // do indexation
        if (!its) {
            if (ind.t == TP_ITUPLE_NULL && simpleValue()) {
                // trivial indexation, let the value unchanged
                return false;
            }
            else if (_val.t == TP_ARRAY) {
                // indexation with tuple, returns scalar value
                CmplArray *arr = _val.array();
                unsigned long i;
                if (SetUtil::tupleInSet(ctx, arr->defset(), ind, i)) {
                    ctx->opResult().copyFrom(arr->at(i), true, false);
                    return true;
                }
            }
        }
        else {
            if (ind.t == TP_SET_ALL || ind.t == TP_TUPLE_EMPTY || ind.t == TP_BLANK) {
                // trivial indexation, let the value unchanged
                return false;
            }
            else if (_val.t == TP_ARRAY) {
                // indexation with set, returns array
                try {
                    CmplArray *arr = _val.array();
                    TupleMatching tm(ctx, TupleMatching::matchIndex, arr->defset(), ind, true);

                    CmplValAuto rdefset;
                    tm.match(rdefset);

                    CmplArray *resarr;
                    CmplValAuto res(TP_ARRAY, (resarr = new CmplArray(rdefset)));

                    vector<unsigned long> *resinds = tm.resIndex();
                    if (resinds && resinds->size()) {
                        CmplVal *a = resarr->at(0);
                        bool av = true;

                        for (unsigned long i : *resinds) {
                            CmplVal *v = arr->at(i);
                            if (v->t == TP_EMPTY)
                                av = false;

                            a->copyFrom(v, true, false);
                            ++a;
                        }

                        resarr->setValidInfo(av);
                    }

                    ctx->opResult().copyFrom(res, true, false);
                    return true;
                }
                catch (TupleMatchingValueException& ex) {
                    if (ex.invSrc())
                        ctx->valueError("invalid array for indexation", orgInd);
                    else
                        ctx->valueError("invalid value given as index tuple set", orgInd);

                    return false;
                }
            }
            else {
                // no matching element
                ctx->opResult().set(TP_NULL);
                return true;
            }
        }

        ctx->valueError("element not found in array with given index tuple", orgInd);
        return false;
    }

    /**
     * perform indexation operation on list, this must contain a list (not TP_REF_LIST)
     * @param ctx			execution context
     * @param ind			index value (must be tuple or set, and not TP_LIST_TUPLE)
     * @param its           number of first index part containing a set + 1 / 0: all index parts are scalar
     * @param orgInd        original index value
     * @return				true: result stored in execution context / false: this changed to result
     */
    bool StackValue::indexationList(ExecContext *ctx, CmplVal& ind, unsigned its, StackValue *orgInd)
    {
        if (ind.t == TP_ITUPLE_NULL) {
            ctx->valueError("element not found in array with given index tuple", orgInd);
            return false;
        }

        // split the first element from the index value
        CmplValAuto fe, re;
        if (ind.isScalarIndex() || its == 1) {
            fe.copyFrom(ind, true, false);
        }
        else if (ind.isTuple()) {
            fe.copyFrom(Tuple::at(ind, 0), true, false);
            if (fe.t == TP_ITUPLE_1INT || fe.t == TP_ITUPLE_1STR)
                fe.t = (fe.t == TP_ITUPLE_1INT ? TP_INT : TP_STR);

            unsigned r = Tuple::rank(ind);
            if (r > 1)
                ind.tuple()->partTuple(re, 1, r - 1);
        }
        /*
         * Fall (ind.isSet()) ist hier gar nicht moeglich, da obige Pruefung "its" schon garantiert, dass "ind" Tuple ist, mit erstem Element einfachem Indexwert
         *
        else if (ind.isSet()) {
            if (ind.useValP()) {
                SetBase *s = ind.setBase();
                CmplVal *bs = NULL;

                if (s->maxRank() >= 2 && s->minRank() >= 1) {
                    if (s->finite()) {
                        bs = (ind.t == TP_SET_FIN ? ind.setFinite()->baseSet() : &ind);
                        bs = (bs->t == TP_SET_REC_MULT ? bs->setRecMult()->partSet(0) : bs);
                    }
                    else if (ind.t == TP_SET_INF_TPL) {
                        bs = ind.setInfiniteTpl()->partSet(0);
                    }

                    if (bs && (bs->isScalarIndex())) {
                        fe.copyFrom(bs, true, false);

                        if (ind.t == TP_SET_REC_MULT) {
                            ind.setRecMult()->partSet(re, 1, s->maxRank() - 1);
                        }
                        else if (ind.t == TP_SET_FIN) {
                            unsigned br = ind.setFinite()->baseRank();
                            if (br == 1) {
                                re.copyFrom(ind.setFinite()->subSet(0), true, false);
                            }
                            else {
                                CmplValAuto nbs;
                                ind.setFinite()->baseSet()->setRecMult()->partSet(nbs, 1, br-1);

                                unsigned long bsc = ind.setFinite()->baseCnt();
                                CmplVal *subs = new CmplVal[bsc];
                                CmplVal *ss = ind.setFinite()->subSet(0);
                                CmplVal *sd = subs;

                                for (unsigned long i = 0; i < bsc; i++, ss++, sd++)
                                    sd->copyFrom(ss, true, false);

                                re.set(TP_SET_FIN, new SetFinite(nbs, subs, s->minRank()-1, s->maxRank()-1));
                            }
                        }
                        else { // ind.t == TP_SET_INF_TPL
                            unsigned pc = ind.setInfiniteTpl()->partCnt();
                            if (pc == 2) {
                                re.copyFrom(ind.setInfiniteTpl()->partSet(1), true, false);
                            }
                            else {  // pc > 2
                                //TODO: geeigneter Konstruktor o.ae. fehlt noch in SetInfiniteTpl;
                                //  fuer "re" muessen einfach alle Teile ausser dem ersten wieder zu SetInfiniteTpl zusammengefasst werden, der entstehende Set ist jedenfalls TP_SET_INF_TPL
                            }
                        }
                    }
                }
            }
        }
        */
        else {
            ctx->internalError("wrong type of index value");
            return false;
        }

        if (!fe.isScalarIndex()) {
            // special list indexation not possible: convert list to array and use it for indexation
            //TODO: fuer bessere Performance sollte die Liste auf dem Stack durch das Array ersetzt werden,
            //      damit bei naechster aehnlicher Indexierung nicht erneut das Array neu aufgebaut werden muss.
            StackValue arr;
            arr.init(_syntaxElem);
            arrayFromList(ctx, arr._val, this);

            bool res = arr.indexation(ctx, ind, 1, orgInd);
            arr.unsetValue();

            return res;
        }
        else if (fe.t == TP_STR || fe.v.i < 1 || fe.v.i > _val.v.i) {
            ctx->opResult().set(TP_NULL);
            if (its == 0)
                ctx->valueError("element not found in array with given index tuple", orgInd);
        }
        else {
            // get list element belonging to index fe
            StackValue *elem;
            int offset = _val.v.i + 1 - fe.v.i;

            if (_val.t == TP_LIST_SIMPLE || _val.t == TP_LIST_SPARSE) {
                elem = this - offset;
            }
            else {
                elem = this - 1;
                offset--;

                while (offset > 0) {
                    elem = ExecContext::stackPrevStatic(elem);
                    offset--;
                }
            }

            // if no remaining index, then the found list element is the result, otherwise recursive call for indexation the list element with the remaining index
            if (!re) {
                CmplVal *v = elem->simpleValue();
                if (v && v->t != TP_NULL && v->t != TP_BLANK) {
                    ctx->opResult().copyFrom(v, true, false);
                }
                else {
                    ctx->valueError("element not found in array with given index tuple", orgInd);
                    ctx->opResult().set(TP_NULL);
                }
            }
            else
            {
                bool res = elem->indexation(ctx, re, (its ? its - 1 : 0), orgInd);
                if (!res)
                    ctx->opResult().copyFrom(elem->val(), true, false);
            }
        }

        return true;
    }


    /**
     * perform assignment with this (being a TP_SYMBOL_VAL value) as assign destination
     * @param ctx			execution context
     * @param op			assign operation (+,-,*,/) or '\0'
     * @param ref			reference assignment
     * @param cnst			mark destination as const
     * @param init          only initial assignment
     * @param ord			ordered assignment
     * @param srn			set row/col name for result matrix
     */
    void StackValue::doAssign(ExecContext *ctx, char op, bool ref, bool cnst, bool init, bool ord, bool srn)
    {
        // this contains a SymbolValue
        SymbolValue *sym = (SymbolValue *)(_val.v.p);

        if (init) {
            if (sym->readOnly())
                return;

            if (!sym->isUninitialized() && !sym->isNull() && !sym->isSimpleEmpty()) {
                //TODO: Fall beruecksichtigen, dass hasIndex() && _addVal->isSet():
                //  dann pruefen, ob sich durch die Indizierung ein nichtleeres Array ergibt, wenn ja, dann return

                if (!hasIndex() || !(_addVal.isITuple()))
                    return;

                CmplArray *arr = _val.array();
                unsigned long i;
                if (SetUtil::tupleInSet(ctx, arr->defset(), _addVal, i) && !(arr->at(i)->isEmpty()))
                    return;
            }
        }

        if (sym->readOnly()) {
            ctx->valueError("cannot write to const symbol", this);
            return;
        }

        if (cnst && !sym->isUninitialized()) {
            ctx->valueError("cannot mark as const an already defined symbol", this);
            return;
        }

        StackValue *rhs = ctx->getCurAssignRhs(_syntaxElem);
        if (ref) {
            if (hasIndex())
                ctx->valueError("left hand side of ref assignment cannot have indexation", this);
            else if (!rhs->lvalue())
                ctx->valueError("right hand side of ref assignment must be an lvalue", rhs);
            else if (rhs->hasIndex())
                ctx->valueError("right hand side of ref assignment cannot have indexation", rhs);
            else {
                SymbolValue *src = (SymbolValue *)(rhs->val().v.p);
                if (sym != src) {
                    LockGuard<mutex> lckS(ctx->needLock(), src->accMtx());
                    sym->copyFrom((SymbolValue *)(rhs->val().v.p), false);
                }
            }

            if (cnst)
                sym->setReadOnly();

            return;
        }

        CmplVal *rhsSimple = rhs->simpleValue();
        CmplVal *lhsInd = (hasIndex() ? &_addVal : NULL);

        if (!sym->isUninitialized() && (hasIndex() || (rhsSimple && sym->simpleValue()))) {
            bool needLockVS = (sym->hasValueStore() && sym->valueStore()->refCnt() > 1);
            LockGuard<mutex> lckV(needLockVS, (needLockVS ? &(sym->valueStore()->accMtx()) : NULL));

            if (!lhsInd || lhsInd->isITuple()) {
                // assign scalar value
                if (rhsSimple && rhsSimple->t != TP_NULL)
                    doAssignScalar(ctx, sym, lhsInd, rhsSimple, rhs->syntaxElem(), op, srn);
                else
                    ctx->valueError("left hand side is indexed as scalar, but right hand side is an array", rhs);
            }
            else {
                //TODO (auch Lock fuer Bestimmung Quellarray)
                ctx->valueError("re-assignment with indexation not implemented", this);
            }

            return;
        }

        StackValue *popTo = NULL;
        bool assArray = true;

        if (rhsSimple && rhsSimple->t != TP_NULL) {
            if (lhsInd && lhsInd->t != TP_SET_ALL && lhsInd->t != TP_SET_NULL) {
                if (lhsInd->isSetInf()) {
                    ctx->valueError("scalar right hand side cannot be assigned to destination indexed by infinite set", rhs);
                    return;
                }

                //TODO: wenn ord, dann anders notwendig, weil jedes einzelne Element schon zugewiesen werden muss, bevor das naechste bestimmt wird
                rhs = popTo = fillAssignArray(ctx, *lhsInd, rhsSimple, rhs->syntaxElem(), ord);
            }
            else if (cnst) {
                PROTO_MOD_OUTL(ctx->modp(), "  setSimpleConstVal: sym " << sym->defId());
                sym->setSimpleConstVal(*rhsSimple);
                assArray = false;

                if (srn && rhsSimple->isOptRC()) {
                    OptModel *resModel = ctx->modp()->getResModel();
                    CmplVal symName(TP_STR, (intType)(ctx->modp()->data()->globStrings()->search(ctx->modp()->symbolInfo(sym->defId())->name())));
                    CmplVal tpl(TP_ITUPLE_NULL);
                    ValueStore::setValInValueTree(ctx, rhsSimple, rhs->syntaxElem(), resModel, symName, tpl);
                }
            }
        }

        if (assArray) {
            if ((!rhsSimple || rhsSimple->t == TP_NULL) && hasIndex() && lhsInd->t != TP_SET_ALL)
                ctx->valueError("assigment with indexed destination not implemented", this);

            PROTO_MOD_OUTL(ctx->modp(), "  setValueStore: sym " << sym->defId());
            ValueStore *store = sym->valueStore(true);

            LockGuard<mutex> lckV((ctx->needLock() && store->refCnt() > 1), store->accMtx());
            store->setValue(ctx, rhs, true, (srn ? ctx->modp()->symbolInfo(sym->defId())->name() : NULL));

            if (cnst)
                sym->setReadOnly();
        }

        if (popTo)
            ctx->stackPopTo(popTo);
    }


    /**
     * perform assignment with this (being a TP_SPECIALSYM value) as assign destination
     * @param ctx			execution context
     * @param op			assign operation (+,-,*,/) or '\0'
     * @param init          only initial assignment
     * @param ord			ordered assignment
     */
    void StackValue::doAssignSpecial(ExecContext *ctx, char op, bool init, bool ord)
    {
        // this contains a pseudo symbol handling value
        ValSpecialBase *vsp = _val.valSpecial();

        if (hasIndex() && !vsp->hasIndexedHandling()) {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("left hand side pseudo symbol %s cannot have indexation", vsp->funcName()), this);
            return;
        }

        StackValue *rhs = ctx->getCurAssignRhs(_syntaxElem);
        CmplVal *rhsSimple = rhs->simpleValue();

        StackValue *popTo = NULL;
        if (hasIndex() && rhsSimple && _addVal.t != TP_SET_ALL && _addVal.t != TP_SET_NULL) {
            if (_addVal.isSetInf()) {
                ctx->valueError("scalar right hand side cannot be assigned to destination indexed by infinite set", rhs);
                return;
            }

            //TODO: wenn ord, dann anders notwendig, weil jedes einzelne Element schon zugewiesen werden muss, bevor das naechste bestimmt wird
            //  fuer Pseudosymbol aber wohl nie relevant
            rhs = popTo = fillAssignArray(ctx, _addVal, rhsSimple, rhs->syntaxElem(), ord);
        }

        if (op) {
            //TODO: insbesondere += (fuer String), wenn rhsSimple && !hasIndex():
            //          dann ueber vsp->set() erst Wert holen, dann Operation ausfuehren, und Ergebnis als rhs verwenden
            ctx->valueError("assigment to pseudo symbol with operation not implemented", this);
            return;
        }

        if (init) {
            //TODO: Zuweisung nur ausfuehren, wenn bisher kein Wert
            //  dafuer erst testweise Wert holen und pruefen ob leer
            ctx->valueError("only initial assigment to pseudo symbol not implemented", this);
            return;
        }

        if (hasIndex())
            vsp->setIndexed(rhs->val(), rhs->syntaxElem(), _addVal);
        else
            vsp->set(rhs->val(), rhs->syntaxElem());

        if (popTo)
            ctx->stackPopTo(popTo);
    }


    /**
     * set data type as fixed for optimization variables
     */
    void StackValue::fixDataTypeVar()
    {
        if (_val.t == TP_OPT_VAR) {
            _val.optVar()->fixDataType();
        }
        else if (_val.t == TP_ARRAY) {
            CmplArray *arr = _val.array();
            CmplVal *v = arr->at(0);

            for (unsigned long i = 0; i < arr->size(); i++, v++) {
                if (v->t == TP_OPT_VAR)
                    v->optVar()->fixDataType();
            }
        }
    }

    /**
     * fill array to assign with scalar values
     * @param ctx			execution context
     * @param ds			definition set of the array
     * @param frhs			first value to fill in
     * @param ord			ordered assignment
     * @return 				array on the stack
     */
    StackValue *StackValue::fillAssignArray(ExecContext *ctx, CmplVal& ds, CmplVal *frhs, unsigned se, bool ord)
    {
        CmplArray *arr = new CmplArray(ds);

        if (arr->size() > 0) {
            bool allValid = (bool)(*frhs);

            arr->at(0)->copyFrom(frhs);

            for (unsigned long i = 1; i < arr->size(); i++) {
                StackValue *sv = ctx->getCurAssignRhs(_syntaxElem);
                CmplVal *v = sv->simpleValue();

                if (v) {
                    if (allValid && !(bool)(*v))
                        allValid = false;

                    arr->at(i)->copyFrom(v);
                }
                else {
                    ctx->valueError("every part of right hand side in assignment must be scalar", sv);
                    allValid = false;
                    arr->at(i)->unset();
                }
            }

            arr->setValidInfo(allValid);
        }

        StackValue *res = ctx->pushPre(se);
        res->_val.set(TP_ARRAY, arr);
        return res;
    }


    /**
     * assign one scalar value within the array of an already defined symbol
     * @param ctx			execution context
     * @param sym			symbol to assign the value in
     * @param tpl			indexing tuple within the value array of the symbol / NULL: no index tuple
     * @param rhs			right hand side value
     * @param op			assign operation (+,-,*,/) or '\0'
     * @param srn			set row/col name for result matrix
     */
    void StackValue::doAssignScalar(ExecContext *ctx, SymbolValue *sym, CmplVal *tpl, CmplVal *rhs, unsigned se, char op, bool srn)
    {
        if (!sym->hasValueStore()) {
            ctx->valueError("illegal left hand side", this);
            return;
        }

        if (!op && rhs->t == TP_STRINGP)
            rhs->stringPToStr(ctx->modp());

        // copy on write if neccessary
        ValueStore *vst = sym->valueStore();
        vst->copyOnWrite(false);

        CmplArray *arr = vst->values();
        if (!arr) {
            ctx->valueError("illegal left hand side", this);
            return;
        }

        // search tuple in the definition set of the value array of the symbol
        CmplVal& ds = arr->defset();
        unsigned long ind;

        CmplVal tplNull(TP_ITUPLE_NULL);
        CmplVal& itpl = (tpl ? *tpl : tplNull);

        if (srn && rhs->isOptRC()) {
            OptModel *resModel = ctx->modp()->getResModel();
            CmplVal symName(TP_STR, (intType)(ctx->modp()->data()->globStrings()->search(ctx->modp()->symbolInfo(sym->defId())->name())));
            ValueStore::setValInValueTree(ctx, rhs, se, resModel, symName, itpl);
        }

        if (SetUtil::tupleInSet(ctx, ds, itpl, ind)) {
            // set value in array
            if (!op) {
                arr->at(ind)->copyFrom(rhs, true, true);
            }
            else {
                CmplVal org;
                org.moveFrom(arr->at(ind));
                unsigned short opc = (op=='+' ? ICS_OPER_ADD : (op=='-' ? ICS_OPER_SUB : (op=='*' ? ICS_OPER_MUL : ICS_OPER_DIV)));

                OperationBase::execBinaryOper(ctx, arr->at(ind), _syntaxElem, opc, false, &org, rhs);
            }

            if (arr->allValid() && !(arr->at(ind)))
                arr->delValidInfo();
            if (arr->hasObjType() && (arr->at(ind)) && !(arr->at(ind)->hasObjectType(arr->objType())))
                arr->delObjType(true);
        }
        else {
            if (!op) {
                // grow definition set and array, and insert value
                CmplVal nds;
                unsigned long ii = SetUtil::addTupleToSet(ctx, nds, ds, itpl, false, true);

                arr->insertValues(nds, ii, rhs);
                nds.dispose();
            }
            else {
                 ctx->valueError("left hand side element not found", this);
            }
        }
    }


    /**
     * check assertion for this
     * @param ctx			execution context
     * @param cnst			mark destination as const
     * @param dt            data type for assertion / NULL: no such assertion
     * @param ot            object type for assertion / NULL: no such assertion
     * @param se            syntax element id
     */
    void StackValue::checkAssert(ExecContext *ctx, bool cnst, ValType *dt, intType ot, unsigned se)
    {
        // this must be an lvalue
        if (_val.t != TP_SYMBOL_VAL) {
            ctx->internalError("wrong value type in StackValue::checkAssert()");
            return;
        }

        // value must be already initialized
        SymbolValue *sym = (SymbolValue *)(_val.v.p);
        if (sym->isUninitialized()) {
            ctx->valueError("uninitialized value in assert", this);
            return;
        }

        // create assertion object
        ValueAssertion *ass = new ValueAssertion(se);
        unique_ptr<ValueAssertion> assp(ass);

        if (dt)
            ass->setDataType(dt);
        if (ot >= 0)
            ass->setObjType(ot);
        if (_addVal.isSet() || _addVal.isTuple())
            ass->setDefset(_addVal);

        if (sym->hasValueStore()) {
            ValueStore *vst = sym->valueStore();
            LockGuard<mutex> lckV((ctx->needLock() && vst->refCnt() > 1), vst->accMtx());

            ass->checkAsssertion(ctx, *(vst->values()), true, true);

            vst->addAssertion(ass);
            assp.release();
        }
        else {
            ass->checkAsssertion(ctx, sym->simpleConstVal(), true, true);
        }
    }


    /**
     * import extern values to this
     * @param ctx			execution context
     * @param cnst			mark destination as const
     * @param se            syntax element id
     */
    void StackValue::importExtern(ExecContext *ctx, bool cnst, unsigned se)
    {
        // this must be an lvalue
        if (_val.t != TP_SYMBOL_VAL) {
            ctx->internalError("wrong value type in StackValue::importExtern()");
            return;
        }

        SymbolValue *sym = (SymbolValue *)(_val.v.p);
        if (sym->readOnly()) {
            ctx->valueError("cannot write to const symbol", this);
            return;
        }

        if (cnst && !sym->isUninitialized()) {
            ctx->valueError("cannot mark as const an already defined symbol", this);
            return;
        }

        // get symbol name including namespace
        intType nmSpace = (_addVal.t == TP_STR ? _addVal.v.i : -1);
        const char *symNameStr = ctx->modp()->symbolInfo(sym->defId())->name();

        string symNmsName;
        if (nmSpace >= 0) {
            symNmsName = ctx->modp()->data()->globStrings()->at(nmSpace);
            symNmsName += '.';
        }
        symNmsName += symNameStr;

        PROTO_MOD_OUTL(ctx->modp(), "  read external values for symbol " << symNmsName);

        // read external data values
        CmplValAuto v;
        ctx->modp()->importExtern(ctx, _syntaxElem, v, symNmsName);

        if (v.t != TP_ARRAY && cnst) {
            sym->setSimpleConstVal(v);
        }
        else {
            PROTO_MOD_OUTL(ctx->modp(), "  setValueStore: sym " << sym->defId());
            sym->unset();
            ValueStore *store = sym->valueStore(true);

            store->setValue(ctx, NULL, true, NULL, &v, se);

            if (cnst)
                sym->setReadOnly();
        }
    }


    /**
     * make iteration step over numeric index values of first index part of array or list in this
     * @param ctx           execution context
     * @param nprv          index value of previous iteration step / 0: start iteration
     * @param prev          previous iteration step result / NULL: not known or start iteration
     * @param nth           iterate to the element nprv + nth
     * @return              pointer to array or list part (existing element on stack or element new pushed on stack) / NULL: no such element or iteration ended
     */
    StackValue *StackValue::iterArray(ExecContext *ctx, unsigned& iter, StackValue *prev, unsigned nth)
    {
        StackValue *res = NULL;
        unsigned nelem = iter + nth;

        if (!nth && (prev || !iter)) {
            res = prev;
        }

        if (_val.isArray()) {
            CmplArray *arr = _val.array();
            CmplVal& ds = arr->defset();
            unsigned rma = SetBase::maxRank(ds);
            unsigned long num;
            CmplVal ind(TP_INT, (intType)nelem);
            CmplValAuto v(TP_EMPTY);

            if (rma == 1) {
                if (SetIterator::isScalarIn(ds, ind, num))
                    v.copyFrom(arr->at(num), true, false);
            }
            else if (rma > 1) {
                //TODO: pruefen ob ds Indizes mit erstem Indexteil nelem enthaelt
                //  wenn ja:
                //      wenn nur ein solches Element, und nelem dessen vollstaendiger Index: Wert des Elements auf den Stack, Pointer darauf zurueck
                //      sonst: neues Array erstellen, mit allen passenden Elementen, mit defset um das erste Element verringert
                // (entspricht indexation mit unendlichem Set "[nelem,]" und koennte also einfach das aufrufen, sobald implementiert)
            }

            if (!v) {
                //TODO: Groesstes numerisches Element bestimmen, dass ds im ersten Indexteil besitzt
                //  wenn groesser gleich nelem, dann:
                //      v.set(TP_NULL);
            }

            if (v) {
                res = ctx->pushPre(_syntaxElem);
                res->_val.moveFrom(v);
            }
        }

        else if (_val.isList()) {
            StackValue *lst = this;
            while (lst->_val.t == TP_REF_LIST)
                lst = (StackValue *)(lst->_val.v.p);

            // get list element belonging to index nelem
            if (nelem < 1 || nelem > _val.v.i) {
                res = NULL;
            }
            else {
                int offset = _val.v.i + 1 - nelem;

                if (_val.t == TP_LIST_SIMPLE || _val.t == TP_LIST_SPARSE) {
                    res = lst - offset;
                }
                else {
                    res = lst - 1;
                    offset--;

                    while (offset > 0) {
                        res = ExecContext::stackPrevStatic(res);
                        offset--;
                    }
                }
            }
        }

        iter = nelem;
        return res;
    }


    /**
     * construct a list on the stack from stack values
	 * @param ctx			execution context
	 * @param res			store for resulting list header
     * @param cnt			count of components for list on stack
     * @param top			topmost component for list on stack / NULL: if cnt==0
     * @return				stack element to pop to before pushing result list / NULL: no element to pop
	 */
	StackValue *StackValue::constructList(ExecContext *ctx, CmplVal &res, unsigned long cnt, StackValue *top)
	{
		// discard trailing nulls and blanks
		StackValue *ptop = NULL;
		while (cnt && top->simpleValue() && (top->simpleValue()->t == TP_NULL || top->simpleValue()->t == TP_BLANK)) {
			ptop = top;
			top = ctx->stackPrev(ptop);
			cnt--;
		}

		if (cnt == 0) {
			res.set(TP_NULL);
		}
		else {
			// just mark the values as list; don't inspect list here to avoid an extra iteration over the values (so because list type is not known now use TP_LIST_COMP)
			res.set(TP_LIST_COMP, (intType)cnt);
		}

		return ptop;
	}

	/**
	 * construct an array from a list on the stack
	 * @param ctx			execution context
	 * @param res			store for resulting array
	 * @param lst			topmost component for tuple on stack, must be the list header
	 * @return				stack element to pop to before pushing result tuple
	 */
	StackValue *StackValue::arrayFromList(ExecContext *ctx, CmplVal &res, StackValue *lst)
	{
		StackValue *pt = lst;

		if (lst->_val.isList() && lst->_val.t != TP_LIST_TUPLE) {
            bool rf = (lst->_val.t == TP_REF_LIST);
            if (rf) {
                while (lst->_val.t == TP_REF_LIST)
					lst = (StackValue *)(lst->_val.v.p);
			}

			// check list properties and size
			unsigned long cnt, size;
			unsigned rank;
			bool hasNull, allValid, hasInvalid;

            if (lst->_val.t != TP_LIST_SIMPLE) {
                size = checkListRec(lst, cnt, rank, hasNull, allValid, hasInvalid);
            }
            else {
                cnt = size = lst->_val.v.i;
                allValid = true;
                hasInvalid = false;
            }

			// construct array from list
			CmplVal *arr = new CmplVal[size];
			CmplVal defset;

			CmplVal *dst = arr + size;
			StackValue *lb = arrayFromListRec(ctx, &dst, defset, lst, 0);

			CmplArray *n = new CmplArray(arr, defset, allValid, hasInvalid);
			res.set(TP_ARRAY, n);

			if (!rf)
				pt = lb;
		}
		else {
			// just use value itself
			res.copyFrom(lst->_val);
		}

		return pt;
	}

	/**
	 * check list properties, and that list type
	 * @param lst			list header on the stack
	 * @param cnt			returns count of non-empty elements
	 * @param rank			returns rank of the list
	 * @param hasNull		returns whether the list contains direct null values
	 * @param allValid		returns whether all direct or indirect elements of the list are valid / false: not known
	 * @param hasInvalid	returns whether in the direct or indirect elements of the list are at least one invalid / false: not known 
	 * @return				count of non-null direct or indirect elements of the list
	 */
	unsigned long StackValue::checkListRec(StackValue *lst, unsigned long& cnt, unsigned& rank, bool& hasNull, bool& allValid, bool& hasInvalid)
	{
		unsigned long sz = lst->_val.v.i;
		unsigned long size = 0;
        unsigned long totalStack = 0;

		cnt = 0;
		rank = 1;
		hasNull = false;
		allValid = true;
		hasInvalid = false;

		while (lst->_val.t == TP_REF_LIST)
			lst = (StackValue *)(lst->_val.v.p);

		StackValue *sv = lst - 1;

		for (unsigned long i = sz; i > 0; i--, sv = ExecContext::stackPrevStatic(sv)) {
			if (sv->_val.isList() && sv->_val.t != TP_LIST_TUPLE) {
				unsigned long cnt2;
				unsigned rank2;
				bool hasNull2, allValid2, hasInvalid2;
				unsigned long size2 = checkListRec(sv, cnt2, rank2, hasNull2, allValid2, hasInvalid2); 

				size += size2;
				cnt += cnt2;
                totalStack += sv->_addVal.v.i + 1;
				if (rank < rank2 + 1)
					rank = rank2 + 1;

				if (!allValid2) {
					allValid = false;
					if (hasInvalid2)
						hasInvalid = true;
				}
			}
			else if (sv->_val.t == TP_ARRAY) {
				CmplArray *arr = sv->_val.array();
				size += arr->size();
				cnt += arr->cnt();
                totalStack++;

				unsigned rank2 = arr->rank();
				if (rank < rank2 + 1)
                    rank = rank2 + 1;

				if (!arr->allValid()) {
					allValid = false;
					if (arr->hasInvalid())
						hasInvalid = true;
				}
			}
			else {
                size++;
				if (sv->_val.t == TP_NULL || sv->_val.t == TP_BLANK)
					hasNull = true;
				else if (sv->_val)
					cnt++;
				else {
					allValid = false;
					hasInvalid = true;
				}

                totalStack++;
                if (sv->_val.t == TP_LIST_TUPLE)
                    totalStack += sv->_val.v.i;
			}
		}

        lst->_addVal.set(TP_INT, (intType)totalStack);
		if (hasNull)
			lst->_val.t = (rank == 1 ? TP_LIST_SPARSE : TP_LIST_COMP_SPARSE);
		else
			lst->_val.t = (rank == 1 ? TP_LIST_SIMPLE : TP_LIST_COMP);

		return cnt;
	}

	/**
	 * construct an array from a hierachical list on the stack
	 * @param ctx			execution context
	 * @param dstp			pointer to current pointer to store array elements, decrement to next element
	 * @param defset		store for resulting definition set
	 * @param lst			topmost component for tuple on stack, must be the list header of a list
	 * @param rec			recursion counter
	 * @return				first stack element to pop for this list
	 */
	StackValue *StackValue::arrayFromListRec(ExecContext *ctx, CmplVal **dstp, CmplVal &defset, StackValue *lst, unsigned rec)
	{
		PROTO_MOD_OUTL(ctx->modp(), "  array from list: start rec #" << rec);

		StackValue *pt = NULL;
		if (lst->_val.t == TP_REF_LIST) {
			pt = lst;
			lst = (StackValue *)(lst->_val.v.p);

			while (lst->_val.t == TP_REF_LIST)
				lst = (StackValue *)(lst->_val.v.p);
		}

		unsigned long sz = lst->_val.v.i;
		StackValue *sv = lst - 1;

		CmplVal *dst = *dstp;

		if (lst->_val.t == TP_LIST_SIMPLE) {
			for (unsigned long i = sz; i > 0; i--) {
				(--dst)->copyFrom(sv->simpleValue());
                PROTO_MOD_OUTL(ctx->modp(), "    " << rec << '@' << i << ": " << *dst);
				
				if (i > 1)
					sv = ExecContext::stackPrevStatic(sv);
			}

			defset.set(TP_SET_R1_1_UB, (intType)sz);
		}
		else if (lst->_val.t == TP_LIST_SPARSE) {
			SetConstructHelper sh(ctx->modp(), true);

			for (unsigned long i = sz; i > 0; i--) {
				if (sv->_val.t != TP_NULL && sv->_val.t != TP_BLANK) {
                    sh.add(i);

					(--dst)->copyFrom(sv->simpleValue());
                    PROTO_MOD_OUTL(ctx->modp(), "    " << rec << '@' << i << ": " << *dst);
				}

				if (i > 1)
					sv = ExecContext::stackPrevStatic(sv);
			}

			sh.construct(defset);
		}
		else {
			SetConstructHelper sh(ctx->modp(), true);
			StackValue *lb;

			for (unsigned long i = sz; i > 0; i--) {
				lb = NULL;

				if (sv->_val.t != TP_NULL && sv->_val.t != TP_BLANK) {
					if (sv->_val.isList() && sv->_val.t != TP_LIST_TUPLE) {
						CmplVal subset;
						lb = arrayFromListRec(ctx, &dst, subset, sv, rec+1);
                        PROTO_MOD_OUTL(ctx->modp(), "    " << rec << '@' << i << ": list (size: " << SetBase::cnt(subset) << ')');

						sh.addBaseAndSubset(i, true, subset);
						subset.dispose();
					}
					else if (sv->_val.t == TP_ARRAY) {
						CmplArray *arr = sv->_val.array();
						for (unsigned long j = arr->size(); j > 0; )
							(--dst)->copyFrom(arr->at(--j));

                        PROTO_MOD_OUTL(ctx->modp(), "    " << rec << '@' << i << ": array (size: " << arr->size() << ')');
						sh.addBaseAndSubset(i, true, arr->defset());
					}
					else {
                        sh.add(i);
						(--dst)->copyFrom(sv->simpleValue());
                        PROTO_MOD_OUTL(ctx->modp(), "    " << rec << '@' << i << ": " << *dst);
					}
				}

				if (lb)
					sv = (i > 1 ? lb - 1 : lb);
				else if (i > 1)
					sv = ExecContext::stackPrevStatic(sv);
			}

			sh.construct(defset);
		}

		*dstp = dst;

		PROTO_MOD_OUTL(ctx->modp(), "  array from list: end rec #" << rec);
		return (pt ?: sv);
	}


    /**
     * convert compound Array (TP_ARRAY_COMP) to regular Array (TP_ARRAY), source array is deleted
     * @param ctx			execution context
     * @param src           source array (can contain TP_NULL and subarrays)
     * @return              src converted to regular array without other arrays as element
     */
    CmplArray *StackValue::arrayFromArrayComp(ExecContext *ctx, CmplArray *src)
    {
        CmplArray *res;

        // check for contained arrays or null elements
        CmplArrayIterator ait(*src);
        bool hasComp = false;
        unsigned long cntNull = 0;
        unsigned long cntEmpty = 0;

        for (ait.begin(); ait; ait++) {
            if ((*ait)->t == TP_ARRAY || (*ait)->t == TP_ARRAY_COMP) {
                hasComp = true;
                break;
            }
            else if ((*ait)->t == TP_NULL || (*ait)->t == TP_BLANK) {
                cntNull++;
            }
            else if ((*ait)->t == TP_EMPTY) {
                cntEmpty++;
            }
        }

        if (!hasComp) {
            // no array recursion
            if (!cntNull) {
                // use array src as result
                res = src;
                if (!cntEmpty) {
                    res->setValidInfo(true);
                }
                else {
                    CmplVal vs(TP_SET_EMPTY);
                    CmplVal r;

                    for (ait.begin(); ait; ait++) {
                        if ((*ait)->t != TP_EMPTY) {
                            SetUtil::addTupleToSet(ctx, r, vs, **ait, false, false);
                            vs.moveFrom(r, true);
                        }
                    }

                    if (SetUtil::canonicalSet(r, vs))
                        vs.moveFrom(r, true);

                    res->setValidInfo(vs);
                    vs.dispose();
                }
            }
            else if (cntNull == src->cnt()) {
                // result is empty array
                CmplVal ds(TP_SET_EMPTY);
                res = new CmplArray(ds);
                res->setValidInfo(true);
                ds.dispose();
            }
            else {
                // new result array with the non-null elements
                CmplVal ds(TP_SET_EMPTY);
                CmplVal vs(TP_SET_EMPTY);
                CmplVal r;

                for (ait.begin(); ait; ait++) {
                    if ((*ait)->t != TP_NULL && (*ait)->t != TP_BLANK) {
                        SetUtil::addTupleToSet(ctx, r, ds, ait.curTuple(), false, false);
                        ds.moveFrom(r, true);

                        if (cntEmpty && (*ait)->t != TP_EMPTY) {
                            SetUtil::addTupleToSet(ctx, r, vs, ait.curTuple(), false, false);
                            vs.moveFrom(r, true);
                        }
                    }
                }

                if (SetUtil::canonicalSet(r, ds))
                    ds.moveFrom(r, true);

                res = new CmplArray(ds);
                CmplVal *d = res->at(0);
                for (ait.begin(); ait; ait++) {
                    if ((*ait)->t != TP_NULL && (*ait)->t != TP_BLANK)
                        (d++)->moveFrom(*ait, false);
                }

                if (!cntEmpty) {
                    res->setValidInfo(true);
                }
                else {
                    if (SetUtil::canonicalSet(r, vs))
                        vs.moveFrom(r, true);

                    res->setValidInfo(vs);
                }

                ds.dispose();
                vs.dispose();
            }
        }

        else {
            // recursive iteration over the array
            CmplVal ds(TP_SET_EMPTY);
            CmplVal vs(TP_SET_EMPTY);
            CmplVal r;
            unsigned long num;

            //TODO: Aufbau Set ueber SetUtil::addTupleToSet fuer jedes einzelne Tupel ist nicht effizient, besser anders gestalten

            CmplArrayIteratorRec aitr(*src);
            for (aitr.begin(); aitr; aitr++) {
                if ((*aitr)->t != TP_NULL && (*aitr)->t != TP_BLANK) {
                    const CmplVal &ctpl = aitr.curTuple();

                    if (SetUtil::tupleInSet(ctx, ds, ctpl, num)) {
                        // ignore element because index tuple already exists
                        (*aitr)->dispSet(TP_BLANK);
                    }
                    else {
                        if (!cntEmpty && (*aitr)->t == TP_EMPTY) {
                            cntEmpty = 1;
                            vs.copyFrom(ds, true, false);
                        }

                        SetUtil::addTupleToSet(ctx, r, ds, ctpl, false, false);
                        ds.moveFrom(r, true);

                        if (cntEmpty && (*aitr)->t != TP_EMPTY) {
                            SetUtil::addTupleToSet(ctx, r, vs, ctpl, false, false);
                            vs.moveFrom(r, true);
                        }
                    }
                }
            }

            if (SetUtil::canonicalSet(r, ds))
                ds.moveFrom(r, true);

            res = new CmplArray(ds);
            CmplVal *d = res->at(0);
            for (aitr.begin(); aitr; aitr++) {
                if ((*aitr)->t != TP_NULL && (*aitr)->t != TP_BLANK)
                    (d++)->moveFrom(*aitr, false);
            }

            if (!cntEmpty) {
                res->setValidInfo(true);
            }
            else {
                if (SetUtil::canonicalSet(r, vs))
                    vs.moveFrom(r, true);

                res->setValidInfo(vs);
            }

            ds.dispose();
            vs.dispose();
        }

        if (res != src)
            delete src;

        return res;
    }

}

