
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


#include "ValueStore.hh"
#include "ValType.hh"
#include "SetUtil.hh"
#include "ExecContext.hh"
#include "Interpreter.hh"
#include "../../CommonData/OptModel.hh"



namespace cmpl
{

    /****** ValueAssertionBase ****/

    /**
     * destructor
     */
    ValueAssertionBase::~ValueAssertionBase()
    {
        if (_nextAss)
            delete _nextAss;
    }

    /**
     * add assertion
     * @param a         assertion to add
     */
    void ValueAssertionBase::addAssertion(ValueAssertion *a)
    {
        if (_nextAss)
            _nextAss->addAssertion(a);
        else
            _nextAss = a;
    }


    /****** ValueAssertion ****/

    /**
     * copy constructor
     * @param src
     */
    ValueAssertion::ValueAssertion(ValueAssertion& src)
    {
        _objType.copyFrom(src._objType, true, false);
        _dataType.copyFrom(src._dataType, true, false);
        _defSet.copyFrom(src._defSet, true, false);

        _subSet = src._subSet;
        _syntaxElem = src._syntaxElem;

        if (src._nextAss) {
            _nextAss = new ValueAssertion(*(src._nextAss));
        }
    }

    /**
     * check assertions, reports error if assertion fails
     * @param ctx               execution context
     * @param v                 value to check
     * @param ctp               check data type and object type
     * @param cds               check array definition set
     * @param vse               syntax element of value to check / 0: in assert command itself
     */
    void ValueAssertion::checkAsssertion(ExecContext *ctx, CmplVal& v, bool ctp, bool cds, unsigned vse)
    {
        if (ctp && _dataType) {
            if (!_dataType.valType()->checkValue(v)) {
                ctx->assertionError("data type", _syntaxElem, vse);
                return;
            }
        }

        if (ctp && _objType) {
            if (!ObjectTypeUtil::checkValue(_objType.v.i, v)) {
                ctx->assertionError("object type", _syntaxElem, vse);
                return;
            }
        }

        if (cds && _defSet) {
            if (_defSet.t != TP_SET_NULL && (!_subSet || !SetBase::containNull(_defSet))) {
                ctx->assertionError("array definition set", _syntaxElem, vse);
                return;
            }
        }

        if (_nextAss)
            _nextAss->checkAsssertion(ctx, v, ctp, cds, vse);
    }


    /**
     * check assertions, reports error if assertion fails
     * @param ctx               execution context
     * @param v                 array with values to check
     * @param ctp               check data type and object type
     * @param cds               check array definition set
     * @param vse               syntax element of value to check / 0: in assert command itself
     */
    void ValueAssertion::checkAsssertion(ExecContext *ctx, CmplArray& v, bool ctp, bool cds, unsigned vse)
    {
        if (ctp && (_dataType || _objType)) {
            CmplVal *p = v.at(0);
            for (unsigned long i = 0; i < v.size(); i++, p++) {
                if (_dataType && !_dataType.valType()->checkValue(*p)) {
                    ctx->assertionError("data type", _syntaxElem, vse);
                    return;
                }

                if (_objType && !ObjectTypeUtil::checkValue(_objType.v.i, *p)) {
                    ctx->assertionError("object type", _syntaxElem, vse);
                    return;
                }
            }
        }

        if (cds && _defSet) {
            if (!SetUtil::compareEq(&_defSet, &(v.defset()))) {
                if (!_subSet || !SetUtil::isSubSet(ctx, &(v.defset()), &_defSet)) {
                    ctx->assertionError("array definition set", _syntaxElem, vse);
                    return;
                }
            }
        }

        if (_nextAss)
            _nextAss->checkAsssertion(ctx, v, ctp, cds, vse);
    }


    /**
     * set <code>_subSet</code> from <code>_dataType</code>
     */
    void ValueAssertion::setSubSet()
    {
        if (!_dataType || !_defSet) {
            _subSet = false;
        }
        else {
            CmplVal n(TP_NULL);
            _subSet = _dataType.valType()->checkValue(n);
        }
    }



	/****** ValueStore ****/

	/**
	 * set value from a stack value
	 * @param ctx				execution context
	 * @param sv				value to copy (can be also an array or an list, but no symbol value) (if a list it must be the top element on the value stack)
	 * @param disp				discard all previous values
     * @param srn				set row/col name for result matrix to this name
     * @param va                value, alternative to <code>sv</code>
     * @param se                syntax element, only used if <code>va</code> is given
     */
    void ValueStore::setValue(ExecContext *ctx, StackValue *sv, bool disp, const char *srn, CmplVal *va, unsigned se)
	{
        if (!sv && !va)
            return;

        copyOnWrite(disp);

        OptModel *resModel = (srn ? ctx->modp()->getResModel() : NULL);
        CmplVal symName;
        if (resModel)
            symName.set(TP_STR, (intType)(ctx->modp()->data()->globStrings()->search(srn)));

        if (disp || !_values) {
            if ((sv && sv->isSimple()) || (va && !va->isSpecial())) {
				// check assertions
//                if (_constSet && _values && !_values->isScalar()) {
//                    //TODO: noch einfügen: Art der Assertion; Syntaxelement der Assertion-Definition
//                    if (sv)
//                        ctx->assertionError(sv);
//                    else
//                        ctx->assertionError(*va, se);
//                }

//				//TODO: assertions für Typ und Objekttyp

                CmplVal& v = (sv ? *(sv->simpleValue()) : *va);

                if (v.t != TP_NULL) {
                    // set value
                    if (_values && !_values->isScalar()) {
                        delete _values;
                        _values = NULL;
                    }
                    if (!_values) {
                        CmplVal ds = CmplVal(TP_SET_NULL);
                        _values = new CmplArray(ds);
                        _values->incRef();
                    }

                    _values->at(0)->copyFrom(v, true, true);
                    _values->setValidInfo((v ? TP_EMPTY : TP_SET_EMPTY));
                    _values->setObjType(v.getObjectType());

                    if (resModel && v.isOptRC()) {
                        CmplVal tpl(TP_ITUPLE_NULL);
                        setValInValueTree(ctx, &v, (sv ? sv->syntaxElem() : se), resModel, symName, tpl);
                    }
                }
                else if (!_values || _values->defset().t != TP_SET_EMPTY) {
                    // set to empty array
                    if (_values)
                        delete _values;

                    _values = new CmplArray();
                    _values->incRef();
                }
			}
			else {
                // a list should be already be replaced by an array or tuple
                if (sv && sv->isList())
                        ctx->valueError("internal error: list value for assign", sv);

                if ((sv ? sv->val() : *va).t != TP_ARRAY) {
                    if (sv)
                        ctx->valueError("internal error: value to assign must be an array", sv);
                    else
                        ctx->valueError("internal error: value to assign must be an array", *va, se);
                }

                CmplArray *arr = (sv ? sv->val().array() : va->array());

				// check assertions
//                if (_constSet && _values && _values->defset() != arr->defset())	{ //TODO: muss Set-Vergleich sein, statt Pointer-Vergleich
//                    //TODO: noch einfügen: Art der Assertion; Syntaxelement der Assertion-Definition
//                    if (sv)
//                        ctx->assertionError(sv);
//                    else
//                        ctx->assertionError(*va, se);
//                }

//				//TODO: assertions für Typ und Objekttyp

				// set value as reference to given array
				if (_values) {
					delete _values;
					_values = NULL;
				}

				arr->incRef();
				_values = arr;

                if (resModel) {
                    CmplArrayIterator iter(*arr);
                    for (iter.begin(); iter; iter++) {
                        CmplVal *v = *iter;
                        if (v->isOptRC())
                            setValInValueTree(ctx, v, (sv ? sv->syntaxElem() : se), resModel, symName, iter.curTuple());
                    }
                }
			}
		}

		else {
			//TODO
		}
	}


	/**
	 * set value from a single value
	 * @param ctx				execution context
	 * @param v					value to copy
	 * @param disp				discard all previous values
	 */
	void ValueStore::setValue(ExecContext *ctx, CmplVal& v, bool disp)
	{
        copyOnWrite(disp);

		//TODO
	}


	/**
	 * set value to a value described only by its type
	 * @param ctx				execution context
	 * @param tp				type for value
	 * @param disp				discard all previous values
	 */
	void ValueStore::setValue(ExecContext *ctx, tp_e tp, bool disp)
	{
        copyOnWrite(disp);

		//TODO
	}


    /**
     * fetch and increment single int value
     * @param ctx               execution context
     * @param pre               prefix or postfix incrementation
     * @param inc               increment value
     * @param se                syntax element
     * @return                  fetched value
     */
    intType ValueStore::fetchInc(ExecContext *ctx, bool pre, int inc, unsigned se)
    {
        if (_values->defset().t != TP_SET_NULL) {
            CmplVal v(TP_ARRAY, this, false);
            ctx->valueError("increment/decrement used with array value, possible only for scalar int", v, se);
            return 0;
        }

        if (_values->at(0)->t != TP_INT) {
            ctx->valueError("increment/decrement used with non-int value, possible only for scalar int", *(_values->at(0)), se);
            return 0;
        }

        copyOnWrite(false);

        intType res;
        CmplVal *p = _values->at(0);

        if (pre) {
            p->v.i += inc;
            res = p->v.i;
        }
        else {
            res = p->v.i;
            p->v.i += inc;
        }

        return res;
    }


	/**
	 * copy values if necessary before write to the array
	 * @param disp				writing will discard all previous values
	 */
	void ValueStore::copyOnWrite(bool disp)
	{
		if (_values && _values->refCnt() > 1) {
			// copy on write
			if (disp && !_constSet) {
				_values->decRef();
				_values = NULL;
			}
            else {
                CmplArray *nv;

                if (disp)
                    nv = new CmplArray(_values->defset());
                else
                    nv = new CmplArray(_values);

                nv->incRef();
                _values->decRef();
                _values = nv;
			}
		}
	}


    /**
     * copy all data of another value store to this
     * @param src               source symbol value
     * @param assertions        copy also assertions
     */
    void ValueStore::copyAllFrom(ValueStore *src, bool assertions)
    {
        if (assertions) {
            if (_nextAss) {
                delete _nextAss;
                _nextAss = NULL;
            }

            if (src->_nextAss) {
                _nextAss = new ValueAssertion(*(src->_nextAss));
            }
        }

        if (_values && _values->decRef()) {
            delete _values;
            _values = NULL;
        }

        if (src->_values) {
            src->_values->incRef();
            _values = src->_values;
        }
    }


    /**
     * set or move value for variable or constraint within the value tree for the result matrix
     * @param ctx				execution context
     * @param v					value to set in the value tree
     * @param se				syntax element id of the value
     * @param resMatrix			result matrix
     * @param fi				first index part (can be TP_INT, TP_STR, TP_ITUPLE* or TP_LIST_TUPLE), or TP_EMPTY then <code>sc</code> holds only the remaining tuple parts up from <code>sub</code>
     * @param sc				second index part (can be TP_INT, TP_STR, TP_ITUPLE* or TP_LIST_TUPLE)
     * @param sub				subtree for the element if known
     */
    void ValueStore::setValInValueTree(ExecContext *ctx, CmplVal *v, unsigned se, OptModel *resMatrix, const CmplVal& fi, const CmplVal& sc, ValueTree *sub)
    {
        if (!v->isOptRC()) {
            ctx->valueError("Internal Error: value for setValInValueTree() is not a variable or constraint", *v, se);
            return;
        }

        if (v->optRC()->isInTree()) {
            ctx->valueError("optimization variable/constraint has had already name and tuple for result matrix", *v, se, ERROR_LVL_WARN);	//TODO: Ausgabe bisheriger Name+Tuple
        }

        ValueTreeRoot *vtr = (v->t == TP_OPT_VAR ? &(resMatrix->cols()) : &(resMatrix->rows()));
        LockGuard<mutex> lck(ctx->needLock(), vtr->accMtx());

        int err = v->optRC()->setInValueTree(vtr, fi, sc, sub);
        if (err == 1) {
            if (v->t == TP_OPT_VAR)
                ctx->valueError("optimization variable with this name and tuple already exists", *v, se);	//TODO: Ausgabe Tuple aus fi+sc
            else
                ctx->valueError("optimization constraint with this name and tuple already exists", *v, se);	//TODO: Ausgabe Tuple aus fi+sc
        }
    }



    /****** SymbolValue ****/

    /**
     * copy contents of another symbol value to this
     * @param src               source symbol value
     * @param ref               copy value store as reference
     */
    void SymbolValue::copyAllFrom(SymbolValue *src, bool ref)
    {
        if (ref || !src->hasValueStore()) {
            copyFrom(src, true);
        }
        else {
            unset();

            bool needLockVS = (src->valueStore()->refCnt() > 1);
            LockGuard<mutex> lckV(needLockVS, &(src->valueStore()->accMtx()));

            ValueStore *v = valueStore(true);
            v->copyAllFrom(src->valueStore(), true);
        }

        _defId = src->_defId;
        _global = src->_global;
        _readOnly = src->_readOnly;
    }

}

