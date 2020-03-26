
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


#include "ValFunction.hh"
#include "Interpreter.hh"
#include "Interval.hh"
#include "TupleUtil.hh"
#include "SetUtil.hh"
#include "OperationBase.hh"
#include "../../Control/MainControl.hh"



namespace cmpl
{

    /****** ValFunctionBase ****/

    /**
     * calls function for every single element of an array or a list (result is array over the same definition set as argument value)
     * @param ctx			execution context
     * @param res           return of result value
     * @param arg			pointer to argument value
     */
    void ValFunctionBase::callForArrayElements(ExecContext *ctx, CmplVal& res, StackValue *arg)
    {
        if (arg->isList())
            arg = ctx->replaceListOnStack(arg);

        CmplVal *s = arg->simpleValue();
        if (s) {
            operCallSimple(ctx, res, *s, false, arg->syntaxElem());
        }
        else if (arg->val().t == TP_ARRAY) {
            CmplArray *arr = new CmplArray(arg->val().array()->defset());
            arr->copyValidInfo(arg->val().array());

            CmplVal *r = arr->at(0);
            s = arg->val().array()->at(0);

            for (unsigned long i = 0; i < arr->size(); i++, r++, s++)
                operCallSimple(ctx, *r, *s, false, arg->syntaxElem());

            res.set(TP_ARRAY, arr);
        }
        else {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented for value type", funcName()), arg);
            res.set(TP_NULL);
        }
    }


    /**
     * recursive call for aggregating the elements of an array or a list
     * @param ctx			execution context
     * @param res           return of result value
     * @param arg			pointer to argument value
     */
    void ValFunctionBase::callForArrayAggrRek(ExecContext *ctx, CmplVal &res, StackValue *arg)
    {
        if (arg->isList()) {
            if (arg->val().t == TP_LIST_TUPLE) {
                CmplValAuto tp;
                TupleUtil::constructFromList(ctx, tp, arg);
                operCallSimple(ctx, res, tp, false, arg->syntaxElem());
            }
            else {
                while (arg->val().t == TP_REF_LIST)
                    arg = (StackValue *)(arg->val().v.p);

                unsigned long cnt = ExecContext::stackListTotalCnt(arg) - 1;
                for (unsigned long i = cnt; i > 0; i--) {
                    CmplVal *s = arg[-i].simpleValue();
                    if (s && !s->isList()) {
                        operCallSimple(ctx, res, *s, false, arg->syntaxElem());
                    }
                    else if (arg[-i].val().t == TP_ARRAY || arg[-i].val().t == TP_REF_LIST) {
                        callForArrayAggrRek(ctx, res, arg - i);
                    }
                }
            }
        }
        else {
            CmplVal *s = arg->simpleValue();
            if (s) {
                operCallSimple(ctx, res, *s, false, arg->syntaxElem());
            }
            else if (arg->val().t == TP_ARRAY) {
                CmplArray *arr = arg->val().array();
                if (arr->hasUserOrder()) {
                    CmplArrayIterator iter(*arr, false, true, false);
                    for (iter.begin(); iter; iter++) {
                        if (operCallSimple(ctx, res, **iter, true, arg->syntaxElem()))
                            break;
                    }
                }
                else {
                    s = arr->at(0);
                    for (unsigned long i = 0; i < arr->size(); i++, s++) {
                        if (operCallSimple(ctx, res, *s, true, arg->syntaxElem()))
                            break;
                    }
                }
            }
            else {
                ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented for value type", funcName()), arg);
            }
        }
    }



    /****** ValFunctionUser ****/

    /**
     * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
     * @param ctx			execution context
     * @param arg			pointer to argument value
     * @return				true if this has handled the operation
     */
    bool ValFunctionUser::operCall(ExecContext *ctx, StackValue *arg)
    {
        // function argument
        StackValue *fctArg = arg;
        if (arg->isList() && arg->val().t != TP_REF_LIST)
        {
            CmplVal rl;
            rl.setP(TP_REF_LIST, arg);
            ctx->pushVal(rl, arg->syntaxElem());
            fctArg = ctx->stackCur();
        }

        // run function in own execution context
        ExecContext fctExec(ctx->modp(), ctx, true, fctArg);

        CmplVal res;
        fctExec.run(_startPos, true, &res);

        ctx->opResult().moveFrom(res);
        return true;
    }



	/****** ValFunctionInternSum ****/

    /**
     * calls the function for a simple source value (no array or list)
     * @param ctx			execution context
     * @param res			store for result value
     * @param src			source value
     * @param aggr          called for aggregating elements of an array or a list
     * @param se			syntax element id of source value
     * @return              only used if aggr: true if result is final
     */
    bool ValFunctionInternSum::operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, bool aggr, unsigned se)
    {
        if (!res || res.t == TP_NULL) {
            res.copyFrom(src, true, false);
        }
        else {
            CmplValAuto a1;
            a1.moveFrom(res, false);
            OperationBase::plus(ctx, &res, se, &a1, &src);
        }

        return false;
    }


	/****** ValFunctionInternMax ****/

    /**
     * calls the function for a simple source value (no array or list)
     * @param ctx			execution context
     * @param res			store for result value
     * @param src			source value
     * @param aggr          called for aggregating elements of an array or a list
     * @param se			syntax element id of source value
     * @return              only used if aggr: true if result is final
     */
    bool ValFunctionInternMax::operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, bool aggr, unsigned se)
    {
        if (src && src.t != TP_NULL) {
            CmplVal srcv;
            if (src.isScalarNumber()) {
                srcv.copyFrom(src);
            }
            else if (src.isInterval()) {
                Interval::uppBoundVal(srcv, src);
            }
            else if (src.isSet() && SET_VAL_WO_ORDER(src).rank1()) {
                CmplVal d;
                SetUtil::rank1IntBounds(d, srcv, src);
            }

            if ((!res || res.t == TP_NULL) && srcv.isScalarNumber()) {
                res.copyFrom(srcv, true, false);
            }
            else if (srcv.isScalarNumber() && res.isScalarNumber()) {
                if (res.t == TP_INFINITE || srcv.t == TP_INFINITE) {
                    if ((res.t == TP_INFINITE && res.v.i > 0) || (srcv.t == TP_INFINITE && srcv.v.i < 0)) {
                        return (res.t == TP_INFINITE && res.v.i > 0);
                    }
                    else if ((srcv.t == TP_INFINITE && srcv.v.i > 0) || (res.t == TP_INFINITE && res.v.i < 0)) {
                        res.copyFrom(srcv);
                        return (srcv.t == TP_INFINITE && srcv.v.i > 0);
                    }
                }
                else if (srcv.isScalarInt() && res.isScalarInt()) {
                    if (srcv.v.i > res.v.i)
                        res.copyFrom(srcv);
                }
                else {
                    if (srcv.numAsReal() > res.numAsReal())
                        res.copyFrom(srcv);
                }

            }
            else {
                ctx->valueError(ctx->modp()->ctrl()->printBuffer("invalid argument for function '%s'", funcName()), src, se);
                return true;
            }
        }

        return false;
    }


	/****** ValFunctionInternMin ****/

    /**
     * calls the function for a simple source value (no array or list)
     * @param ctx			execution context
     * @param res			store for result value
     * @param src			source value
     * @param aggr          called for aggregating elements of an array or a list
     * @param se			syntax element id of source value
     * @return              only used if aggr: true if result is final
     */
    bool ValFunctionInternMin::operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, bool aggr, unsigned se)
    {
        if (src && src.t != TP_NULL) {
            CmplVal srcv;
            if (src.isScalarNumber()) {
                srcv.copyFrom(src);
            }
            else if (src.isInterval()) {
                Interval::lowBoundVal(srcv, src);
            }
            else if (src.isSet() && SET_VAL_WO_ORDER(src).rank1()) {
                CmplVal d;
                SetUtil::rank1IntBounds(srcv, d, src);
            }

            if ((!res || res.t == TP_NULL) && srcv.isScalarNumber()) {
                res.copyFrom(srcv, true, false);
            }
            else if (srcv.isScalarNumber() && res.isScalarNumber()) {
                if (res.t == TP_INFINITE || srcv.t == TP_INFINITE) {
                    if ((res.t == TP_INFINITE && res.v.i < 0) || (srcv.t == TP_INFINITE && srcv.v.i > 0)) {
                        return (res.t == TP_INFINITE && res.v.i < 0);
                    }
                    else if ((srcv.t == TP_INFINITE && srcv.v.i < 0) || (res.t == TP_INFINITE && res.v.i > 0)) {
                        res.copyFrom(srcv);
                        return (srcv.t == TP_INFINITE && srcv.v.i < 0);
                    }
                }
                else if (srcv.isScalarInt() && res.isScalarInt()) {
                    if (srcv.v.i < res.v.i)
                        res.copyFrom(srcv);
                }
                else {
                    if (srcv.numAsReal() < res.numAsReal())
                        res.copyFrom(srcv);
                }

            }
            else {
                ctx->valueError(ctx->modp()->ctrl()->printBuffer("invalid argument for function '%s'", funcName()), src, se);
                return true;
            }
        }

        return false;
    }


    /****** ValFunctionInternAnd ****/

    /**
     * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
     * @param ctx			execution context
     * @param arg			pointer to argument value
     * @return				true
     */
    bool ValFunctionInternAnd::operCall(ExecContext *ctx, StackValue *arg)
    {
        ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented", funcName()), arg);
        //TODO:
        //  - Ergebnis bin 0, wenn mindest ein Eingangsdatum bin 0 ist
        //  - Ergebnis formula, aus und-verknüpften Eingangsformeln, wenn alle nicht-formula Eingangswerte bin 1 sind
        //  - Ergebnis bin 1 sonst (insbesondere auch wenn gar kein Eingangsdatum)
        // oder Funktionalitaet des &&-Operators aufrufen (bei Array mehrfach)?

        ctx->opResult().set(TP_BIN, false);
        return true;
    }


    /****** ValFunctionInternOr ****/

    /**
     * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
     * @param ctx			execution context
     * @param arg			pointer to argument value
     * @return				true
     */
    bool ValFunctionInternOr::operCall(ExecContext *ctx, StackValue *arg)
    {
        ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented", funcName()), arg);
        //TODO:
        //  - Ergebnis bin 1, wenn mindest ein Eingangsdatum bin 1 ist
        //  - Ergebnis formula, aus oder-verknüpften Eingangsformeln, wenn alle nicht-formula Eingangswerte bin 0 sind
        //  - Ergebnis bin 0 sonst (insbesondere auch wenn gar kein Eingangsdatum)
        // oder Funktionalitaet des ||-Operators aufrufen (bei Array mehrfach)?

        ctx->opResult().set(TP_BIN, false);
        return true;
    }


	/****** ValFunctionInternCount ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
	bool ValFunctionInternCount::operCall(ExecContext *ctx, StackValue *arg)
	{
		ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented", funcName()), arg);
		//TODO: returns int
		
		ctx->opResult().set(TP_NULL);
		return true;
	}


	/****** ValFunctionInternDef ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
	bool ValFunctionInternDef::operCall(ExecContext *ctx, StackValue *arg)
	{
		ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented", funcName()), arg);
		//TODO: returns int
		
		ctx->opResult().set(TP_NULL);
		return true;
	}


	/****** ValFunctionInternValid ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
	bool ValFunctionInternValid::operCall(ExecContext *ctx, StackValue *arg)
	{
		ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented", funcName()), arg);
		//TODO: returns bin
		
		ctx->opResult().set(TP_NULL);
		return true;
	}


	/****** ValFunctionInternDim ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
	bool ValFunctionInternDim::operCall(ExecContext *ctx, StackValue *arg)
	{
        if (arg->isList())
            arg = ctx->replaceListOnStack(arg);

        if (arg->simpleValue()) {
            ctx->opResult().set(TP_INT, (intType)0);
        }
        else if (arg->val().t == TP_ARRAY) {
            // get last tuple of definition set, use first element of this tuple
            CmplVal& ds = arg->val().array()->defset();
            if (SetBase::cnt(ds) == 0) {
                ctx->opResult().set(TP_INT, (intType)0);
            }
            else {
                CmplValAuto lt;
                SetIterator::at(lt, ds, 0, SetIterator::iteratorTupleSimple, false, true);
                if (lt.isITuple())
                    ctx->opResult().copyFrom(Tuple::at(lt, 0), true, false);
                else
                    ctx->opResult().copyFrom(lt, true, false);
            }
        }
        else {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented", funcName()), arg);
            ctx->opResult().set(TP_INT, (intType)0);
        }
		
		return true;
	}


	/****** ValFunctionInternDefset ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
	bool ValFunctionInternDefset::operCall(ExecContext *ctx, StackValue *arg)
	{
        if (arg->isList())
            arg = ctx->replaceListOnStack(arg);

        if (arg->simpleValue()) {
            ctx->opResult().set(TP_SET_NULL);
        }
        else if (arg->val().isArray()) {
            CmplArray *arr = arg->val().array();
            if (arg->val().t == TP_ARRAY_COMP)
                arr = StackValue::arrayFromArrayComp(ctx, arr);     //TODO: Bestimmung volles Array hier nicht notwendig, defSet reicht

            ctx->opResult().copyFrom(arr->defset(), true, false);
        }
        else {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented for value type", funcName()), arg);
            ctx->opResult().set(TP_NULL);
        }
		
		return true;
	}


	/****** ValFunctionInternValidset ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
	bool ValFunctionInternValidset::operCall(ExecContext *ctx, StackValue *arg)
	{
        if (arg->isList())
            arg = ctx->replaceListOnStack(arg);

        if (arg->simpleValue()) {
            ctx->opResult().set(arg->simpleValue()->t != TP_EMPTY ? TP_SET_NULL : TP_SET_EMPTY);
        }
        else if (arg->val().isArray()) {
            CmplArray *arr = arg->val().array();
            if (arg->val().t == TP_ARRAY_COMP)
                arr = StackValue::arrayFromArrayComp(ctx, arr);        //TODO: Bestimmung volles Array hier nicht notwendig, validSet reicht

            SetUtil::getArrayValidSet(ctx, ctx->opResult(), arr);
        }
        else {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented for value type", funcName()), arg);
            ctx->opResult().set(TP_NULL);
        }

        return true;
    }


	/****** ValFunctionInternLen ****/

    /**
     * calls the function for a simple source value (no array or list)
     * @param ctx			execution context
     * @param res			store for result value
     * @param src			source value
     * @param aggr          called for aggregating elements of an array or a list
     * @param se			syntax element id of source value
     * @return              only used if aggr: true if result is final
     */
    bool ValFunctionInternLen::operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, bool aggr, unsigned se)
	{
        if (src.isSet()) {
            if (src.isSetFin())
                res.set(TP_INT, (intType)SetBase::cnt(src));
            else
                res.set(TP_INFINITE, 1);
        }
        else if (src.isTuple()) {
            // tuple is handled as a set with one element
            res.set(TP_INT, 1);
        }
        else if (src.isScalarString()) {
            // function used for string len
            if (src.t == TP_STRINGP)
                res.set(TP_INT, (intType)(src.v.s->size()));
            else
                res.set(TP_INT, (intType)(strlen(src.stringAsCharP(ctx->modp()))));
        }
        else {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("invalid argument for function '%s'", funcName()), src, se);
            res.set(TP_INT, 0);
            return true;
        }

        return false;
	}


	/****** ValFunctionInternRank ****/

    /**
     * calls the function for a simple source value (no array or list)
     * @param ctx			execution context
     * @param res			store for result value
     * @param src			source value
     * @param aggr          called for aggregating elements of an array or a list
     * @param se			syntax element id of source value
     * @return              only used if aggr: true if result is final
     */
    bool ValFunctionInternRank::operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, bool aggr, unsigned se)
    {
        if (src.isSet()) {
            unsigned l = SetBase::minRank(src);
            unsigned u = SetBase::maxRank(src, UINT_MAX);

            if (l == u) {
                res.set(TP_INT, (intType)l);
            }
            else {
                CmplVal lb(TP_INT, (intType)l);
                CmplVal ub;
                if (u == UINT_MAX)
                    ub.set(TP_INFINITE, 1);
                else
                    ub.set(TP_INT, (intType)u);

                Interval::construct(res, lb, ub);
            }
        }
        else if (src.isTuple()) {
            res.set(TP_INT, (intType)(Tuple::rank(src)));
        }
        else if (!src.isSpecial()) {
            res.set(TP_INT, 1);
        }
        else {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("invalid argument for function '%s'", funcName()), src, se);
            res.set(TP_INT, 0);
            return true;
        }

        return false;
	}


	/****** ValFunctionInternEcho ****/

    /**
     * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
     * @param ctx			execution context
     * @param arg			pointer to argument value
     * @return				true
     */
    bool ValFunctionInternEcho::operCall(ExecContext *ctx, StackValue *arg)
    {
        LockGlobalGuard(true, LockGlobalGuard::coutLock);

        if (ctx->modp()->echoDuration())
            cout << ctx->modp()->durStartApp().count() / 1000. << ": ";

        callForArrayAggr(ctx, ctx->opResult(), arg);
        cout << endl;

        ctx->opResult().set(TP_NULL);
        return true;
    }

    /**
     * calls the function for a simple source value (no array or list)
     * @param ctx			execution context
     * @param res			store for result value
     * @param src			source value
     * @param aggr          called for aggregating elements of an array or a list
     * @param se			syntax element id of source value
     * @return              only used if aggr: true if result is final
     */
    bool ValFunctionInternEcho::operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, bool aggr, unsigned se)
    {
        if (!res || res.t == TP_NULL)
            res.set(TP_INT, (intType)0);
        else
            cout << ' ';

        CmplValAuto t;
        if (ctx->checkContainerConvSpecial(t, src, TP_STR))
            t.write(cout, ctx->modp());
        else
            src.write(cout, ctx->modp());

        return false;
    }

//	/**
//	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
//	 * @param ctx			execution context
//	 * @param arg			pointer to argument value
//	 * @return				true
//	 */
//    bool ValFunctionInternEcho::operCall(ExecContext *ctx, StackValue *arg)
//    {
//        CmplVal *v = arg->simpleValue();
//        if (v && !v->isList()) {
//            v->write(cout, ctx->modp());
//            cout << endl;
//        }
//        else if (arg->isList()) {
//            CmplVal &r = arg->val();
//            if (r.t == TP_LIST_TUPLE) {
//                CmplVal o;
//                TupleUtil::constructFromList(ctx, o, arg);
//                o.write(cout, ctx->modp());
//                cout << endl;
//                o.dispose();
//            }
//            else {
//                while (arg->val().t == TP_REF_LIST)
//                    arg = (StackValue *)(arg->val().v.p);

//                unsigned long cnt = ExecContext::stackListTotalCnt(arg) - 1;
//                for (unsigned long i = cnt; i > 0; i--) {
//                    CmplVal *a = arg[-i].simpleValue();
//                    if (a && !a->isList()) {
//                        a->write(cout, ctx->modp());
//                        cout << ' ';
//                    }
//                    else if (arg[-i].val().t == TP_ARRAY) {
//                        echoArraySimple(ctx, arg[-i].val().array());
//                    }
//                }
//                cout << endl;
//            }
//        }
//        else if (arg->val().t == TP_ARRAY) {
//            echoArraySimple(ctx, arg->val().array());
//            cout << endl;
//        }
//        else {
//            //TODO
//            ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented for value type", funcName()), arg);
//        }

//        ctx->opResult().set(TP_NULL);
//        return true;
//    }

//    /**
//     * simple array output
//     * @param ctx			execution context
//     * @param arr			array
//     */
//    void ValFunctionInternEcho::echoArraySimple(ExecContext *ctx, CmplArray *arr)
//    {
//        CmplArrayIterator iter(*arr, true, true);
//        for (iter.begin(); iter; iter++) {
//            CmplVal *v = *iter;
//            v->write(cout, ctx->modp());
//            cout << ' ';
//        }
//    }


	/****** ValFunctionInternError ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
	bool ValFunctionInternError::operCall(ExecContext *ctx, StackValue *arg)
	{
		ctx->valueError("user error", arg, ERROR_LVL_FATAL);

		ctx->opResult().set(TP_NULL);
		return true;
	}


	/****** ValFunctionInternFormat ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
	bool ValFunctionInternFormat::operCall(ExecContext *ctx, StackValue *arg)
	{
		ctx->valueError(ctx->modp()->ctrl()->printBuffer("function '%s' not implemented", funcName()), arg);
		//TODO: returns string
		
		ctx->opResult().set(TP_NULL);
		return true;
	}


    /****** ValFunctionDivInteger ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
    bool ValFunctionDivInteger::operCall(ExecContext *ctx, StackValue *arg)
	{
        CmplValAuto args[2];
        unsigned se[2];
        intType res = 1;

        if (ctx->getFirstSimpleValues(arg, 2, args, se) != 2) {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("wrong count of arguments for function '%s'", funcName()), arg);
        }
        else {
            intType i1, i2;
            if (!args[0].toInt(i1, typeConversionValue, ctx->modp())) {
                ctx->valueError(ctx->modp()->ctrl()->printBuffer("for function '%s' first argument must be an integer value", funcName()), args[0], se[0]);
            }
            else if (!args[1].toInt(i2, typeConversionValue, ctx->modp())) {
                ctx->valueError(ctx->modp()->ctrl()->printBuffer("for function '%s' second argument must be an integer value", funcName()), args[1], se[1]);
            }
            else if (i2 == 0) {
                ctx->valueError(ctx->modp()->ctrl()->printBuffer("for function '%s' second argument must not be 0", funcName()), args[1], se[1]);
            }
            else {
                res = execDiv(i1, i2);
            }
        }
		
        ctx->opResult().set(TP_INT, res);
		return true;
	}



	/****** ValFunctionInternSrand ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
    bool ValFunctionInternSrand::operCall(ExecContext *ctx, StackValue *arg)
    {
        CmplVal *v = arg->simpleValue();
        intType i;
        if (v && !v->isList()) {
            if (v->toInt(i, typeConversionExact, ctx->modp())) {
                  srand( i );
                  ctx->opResult().set(TP_INT, i);
            } else {
                ctx->valueError(ctx->modp()->ctrl()->printBuffer("wrong argument for function %s", funcName()), arg);
                ctx->opResult().set(TP_NULL);
            }

        } else {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("wrong <array|list|symbol> argument for function %s", funcName()), arg);
            ctx->opResult().set(TP_NULL);
        }


        return true;
    }


	/****** ValFunctionInternRand ****/

	/**
	 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
	 * @param ctx			execution context
	 * @param arg			pointer to argument value
	 * @return				true
	 */
    bool ValFunctionInternRand::operCall(ExecContext *ctx, StackValue *arg)
    {
        CmplVal *v = arg->simpleValue();
        intType i,res;
        if (v && !v->isList()) {
            if (v->toInt(i, typeConversionExact, ctx->modp())) {
                if (i<=RAND_MAX) {
                  res=rand()%i;
                  ctx->opResult().set(TP_INT, res);
                } else {
                    ctx->valueError(ctx->modp()->ctrl()->printBuffer("wrong argument for function %s", funcName()), arg);
                    ctx->opResult().set(TP_NULL);
                }
            } else {
                ctx->valueError(ctx->modp()->ctrl()->printBuffer("wrong argument for function %s", funcName()), arg);
                ctx->opResult().set(TP_NULL);
            }

        } else {
            ctx->valueError(ctx->modp()->ctrl()->printBuffer("wrong <array|list|symbol> argument for function %s", funcName()), arg);
            ctx->opResult().set(TP_NULL);
        }

        return true;
    }

}

