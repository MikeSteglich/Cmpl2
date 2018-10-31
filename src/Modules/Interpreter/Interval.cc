
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


#include <math.h>

#include "Interval.hh"
#include "SetUtil.hh"
#include "Interpreter.hh"
#include "ExecContext.hh"
#include "../../Control/MainControl.hh"


namespace cmpl
{

	/****** Interval ****/

	/**
	 * get whether the interval v is an empty interval
	 */
    bool Interval::isEmpty(const CmplVal &v)
	{
		if (v.t == TP_INTERVAL_EMPTY)
			return true;

		if (!hasLowBound(v) || !hasUppBound(v))
			return false;

		if (v.t == TP_INTERVAL) {
			CmplVal& lb = v.interval()->_lowBound;
			CmplVal& ub = v.interval()->_uppBound;
			if (lb.t == TP_INT && ub.t == TP_INT)
				return (lb.v.i > ub.v.i);
			else
				return ((lb.t == TP_REAL ? lb.v.r : (realType) lb.v.i) > (ub.t == TP_REAL ? ub.v.r : (realType) ub.v.i));
		}

		return ((v.t == TP_INTERVAL_0_UB_R && v.v.r < 0) || (v.t == TP_INTERVAL_1_UB_R && v.v.r < 1) || (v.t == TP_INTERVAL_0_UB_I && v.v.i < 0) || (v.t == TP_INTERVAL_1_UB_I && v.v.i < 1));
	}

	/**
	 * get lower bound of interval v as a real number (only if hasLowBound(v), or TP_INTERVAL_EMPTY) (for TP_INTERVAL_EMPTY return 0)
	 */
    realType Interval::lowBoundReal(const CmplVal &v)
	{
		if (hasLowBound(v)) {
			if (v.t == TP_INTERVAL_0_INF || v.t == TP_INTERVAL_0_UB_R || v.t == TP_INTERVAL_0_UB_I)
				return 0;
			else if (v.t == TP_INTERVAL_1_INF || v.t == TP_INTERVAL_1_UB_R || v.t == TP_INTERVAL_1_UB_I)
				return 1;
			else if (v.t == TP_INTERVAL_LB_R)
				return v.v.r;
			else if (v.t == TP_INTERVAL_LB_I)
				return (realType) v.v.i;
			else if (v.t == TP_INTERVAL) {
				CmplVal& b = v.interval()->_lowBound;
				return (b.t == TP_REAL ? b.v.r : (realType) b.v.i);
			}
		}

		return 0;
	}

	/**
	 * get upper bound of interval v as a real number (only if hasUppBound(v), or TP_INTERVAL_EMPTY) (for TP_INTERVAL_EMPTY return -1)
	 */
    realType Interval::uppBoundReal(const CmplVal &v)
	{
		if (hasUppBound(v)) {
			if (v.t == TP_INTERVAL_0_UB_R || v.t == TP_INTERVAL_1_UB_R || v.t == TP_INTERVAL_UB_R)
				return v.v.r;
			else if (v.t == TP_INTERVAL_0_UB_I || v.t == TP_INTERVAL_1_UB_I || v.t == TP_INTERVAL_UB_I)
				return (realType) v.v.i;
			else if (v.t == TP_INTERVAL) {
				CmplVal& b = v.interval()->_uppBound;
				return (b.t == TP_REAL ? b.v.r : (realType) b.v.i);
			}
		}

		if (v.t == TP_INTERVAL_EMPTY)
			return -1;

		return 0;
	}

	/**
	 * get lower bound of interval v as an int number (only if hasLowBound(v), or TP_INTERVAL_EMPTY) (for TP_INTERVAL_EMPTY return 0)
	 */
    intType Interval::lowBoundInt(const CmplVal &v)
	{
		if (hasLowBound(v)) {
			if (v.t == TP_INTERVAL_0_INF || v.t == TP_INTERVAL_0_UB_R || v.t == TP_INTERVAL_0_UB_I)
				return 0;
			else if (v.t == TP_INTERVAL_1_INF || v.t == TP_INTERVAL_1_UB_R || v.t == TP_INTERVAL_1_UB_I)
				return 1;
			else if (v.t == TP_INTERVAL_LB_R)
				return (intType) ceil(v.v.r);
			else if (v.t == TP_INTERVAL_LB_I)
				return v.v.i;
			else if (v.t == TP_INTERVAL) {
				CmplVal& b = v.interval()->_lowBound;
				return (b.t == TP_REAL ? (intType) ceil(b.v.r) : b.v.i);
			}
		}

		return 0;
	}

	/**
	 * get upper bound of interval v as an int number (only if hasUppBound(v), or TP_INTERVAL_EMPTY) (for TP_INTERVAL_EMPTY return -1)
	 */
    intType Interval::uppBoundInt(const CmplVal &v)
	{
		if (hasUppBound(v)) {
			if (v.t == TP_INTERVAL_0_UB_R || v.t == TP_INTERVAL_1_UB_R || v.t == TP_INTERVAL_UB_R)
				return (intType) floor(v.v.r);
			else if (v.t == TP_INTERVAL_0_UB_I || v.t == TP_INTERVAL_1_UB_I || v.t == TP_INTERVAL_UB_I)
				return v.v.i;
			else if (v.t == TP_INTERVAL) {
				CmplVal& b = v.interval()->_uppBound;
				return (b.t == TP_REAL ? (intType) floor(b.v.r) : b.v.i);
			}
		}

		if (v.t == TP_INTERVAL_EMPTY)
			return -1;

		return 0;
	}


	/**
	 * construct an interval from stack values
	 * @param ctx			execution context
	 * @param res			store for result interval
	 * @param lb			value for lower bound / NULL: no lower bound
	 * @param ub			value for upper bound / NULL: no upper bound
	 */
	void Interval::construct(ExecContext *ctx, CmplVal &res, StackValue *lb, StackValue *ub)
	{
		if (!lb && !ub) {
			res.set(TP_INTERVAL_ALL);
			return;
		}

		CmplVal vlb, vub;
		if (lb) {
			CmplVal *v = lb->simpleValue();
			if (!v)
				ctx->valueError("lower bound for interval must be a scalar value", lb);
			if (!v->toNumber(vlb, typeConversionFromSub, ctx->modp()))
				ctx->valueError("lower bound for interval must be a scalar numeric value", lb);
		}
		if (ub) {
			CmplVal *v = ub->simpleValue();
			if (!v)
				ctx->valueError("upper bound for interval must be a scalar value", ub);
			if (!v->toNumber(vub, typeConversionFromSub, ctx->modp()))
				ctx->valueError("upper bound for interval must be a scalar numeric value", ub);
		}

		construct(res, vlb, vub);
	}

	/**
	 * construct an interval from values
	 * @param res			store for result interval
	 * @param lb			value for lower bound (must be TP_INT, TP_REAL or TP_INFINITE) / TP_EMPTY: no lower bound
	 * @param ub			value for upper bound (must be TP_INT, TP_REAL or TP_INFINITE) / TP_EMPTY: no upper bound
	 */
	void Interval::construct(CmplVal &res, CmplVal& lb, CmplVal& ub)
	{
		// handle infinite bounds
		if (lb.t == TP_INFINITE) {
			if (lb.v.i > 0) {
				res.set(TP_INTERVAL_EMPTY);
				return;
			}
			lb.unset();
		}

		if (ub.t == TP_INFINITE) {
			if (ub.v.i < 0) {
				res.set(TP_INTERVAL_EMPTY);
				return;
			}
			ub.unset();
		}

		if (lb) {
			bool lb0 = ((lb.t == TP_INT && lb.v.i == 0) || (lb.t == TP_REAL && lb.v.r == 0));
			bool lb1 = ((lb.t == TP_INT && lb.v.i == 1) || (lb.t == TP_REAL && lb.v.r == 1));

			if (ub) {
				// lower bound and upper 
				if ((lb.t == TP_INT && ub.t == TP_INT && lb.v.i > ub.v.i) || (lb.t == TP_INT ? (realType)(lb.v.i) : lb.v.r) > (ub.t == TP_INT ? (realType)(ub.v.i) : ub.v.r)) {
					res.set(TP_INTERVAL_EMPTY);
				}
				else if (lb0) {
					if (ub.t == TP_INT)
						res.set(TP_INTERVAL_0_UB_I, ub.v.i);
					else
						res.set(TP_INTERVAL_0_UB_R, ub.v.r);
				}
				else if (lb1) {
					if (ub.t == TP_INT)
						res.set(TP_INTERVAL_1_UB_I, ub.v.i);
					else
						res.set(TP_INTERVAL_1_UB_R, ub.v.r);
				}
				else {
					res.set(TP_INTERVAL, new Interval(lb, ub));
				}
			}
			else if (lb) {
				// only lower bound
				if (lb0)
					res.set(TP_INTERVAL_0_INF);
				else if (lb1)
					res.set(TP_INTERVAL_1_INF);
				else if (lb.t == TP_INT)
					res.set(TP_INTERVAL_LB_I, lb.v.i);
				else
					res.set(TP_INTERVAL_LB_R, lb.v.r);
			}
		}
		else {
			if (ub) {
				// only upper bound
				if (ub.t == TP_INT)
					res.set(TP_INTERVAL_UB_I, ub.v.i);
				else
					res.set(TP_INTERVAL_UB_R, ub.v.r);
			}
			else {
				// no bound
				res.set(TP_INTERVAL_ALL);
			}
		}
	}

}

