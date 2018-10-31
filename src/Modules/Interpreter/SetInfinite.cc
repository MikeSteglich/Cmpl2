
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


#include "SetInfinite.hh"
#include "../../CommonData/IntCode.hh"


namespace cmpl
{

	/****** SetInfinite ****/



    /****** SetInfiniteTpl ****/

    /**
     * constructor
     * @param pc			count of part sets
     * @param arr			array with part sets
     */
    SetInfiniteTpl::SetInfiniteTpl(unsigned pc, CmplVal *arr)
    {
        _partCnt = pc;
        _parts = arr;

        _markNF = false;
        _isCanonical = true;
        _subOrder = false;

        CmplVal *s = arr;
        for (unsigned r = 0; r < pc; r++, s++) {
            if (_isCanonical && !SetBase::isCanonical(*s))
                _isCanonical = false;

            if (!_subOrder && SetBase::hasUserOrder(*s))
                _subOrder = true;
        }
    }


    /**
     * get minimal rank of tuples within the tuple set
     */
    unsigned SetInfiniteTpl::minRank() const
    {
        unsigned r = 0;

        CmplVal *p = _parts;
        for (unsigned i = 0; i < _partCnt; i++, p++)
            r += SetBase::minRank(*p);

        return r;
    }


    /**
     * get maximal rank of tuples within the tuple set
     * @param ub        upper bound for return value
     */
    unsigned SetInfiniteTpl::maxRank(unsigned ub) const
    {
        unsigned r = 0;

        CmplVal *p = _parts;
        for (unsigned i = 0; i < _partCnt; i++, p++) {
            unsigned rr = SetBase::maxRank(*p, ub);
            if (rr == ub || r + rr >= ub || r + rr < r)
                return ub;

            r += rr;
        }

        return r;
    }


    /**
     * get whether all tupels in the tuple set have the same rank
     */
    bool SetInfiniteTpl::oneRank() const
    {
        CmplVal *p = _parts;
        for (unsigned i = 0; i < _partCnt; i++, p++) {
            if (!SetBase::oneRank(*p))
                return false;
        }

        return true;
    }


    /**
     * get max bound for tuple part count this set is divisible in
     */
    unsigned SetInfiniteTpl::maxTupleParts() const
    {
        unsigned res = _partCnt;

        CmplVal *p = _parts;
        for (unsigned i = 0; i < _partCnt; i++, p++) {
            if (p->isSet() && !SetBase::rank1(*p)) {
                if (SetBase::finite(*p))
                    res += SetBase::maxRank(*p) - 1;
                else if (p->t == TP_SET_INF_TPL)        //TODO: offensichtlich falsch, denn Teil darf nicht TP_SET_INF_TPL sein
                    res += p->setInfiniteTpl()->maxTupleParts() - 1;
                //TODO: uebrige Sets
            }
        }

        return res;
    }


    /**
     * push all tuple divisible parts in a vector
     * @param dtp       vector to push parts in
     * @return          true if parts are pushed to vector; false if set is not tuple divisible
     */
    bool SetInfiniteTpl::partsToVector(vector<CmplVal>& dtp) const
    {
        CmplVal *p = _parts;
        for (unsigned i = 0; i < _partCnt; i++, p++) {
            if (p->isSet() && p->useValP() && !SetBase::rank1(*p))
                SetBase::partsToVector(*p, dtp);
            else
                dtp.push_back(CmplVal(p));
        }

        return true;
    }


    /**
     * get set with all user order removed
     * @param res		value for result
     */
    void SetInfiniteTpl::stripOrder(CmplVal& res)
    {
        SetInfiniteTpl *s;
        if (_subOrder) {
            CmplVal *arr = new CmplVal[_partCnt];
            CmplVal *q, *d;
            unsigned r;

            for (r = 0, q = _parts, d = arr; r < _partCnt; r++, d++, q++)
                d->copyFrom(SET_VAL_WO_ORDER(*q), true);

            s = new SetInfiniteTpl(_partCnt, arr);
        }
        else {
            s = this;
        }

        res.set(TP_SET_INF_TPL, s);
    }



    /****** SetInfiniteSet ****/

    /**
     * constructor
     * @param pc			count of part sets
     * @param arr			array with part sets
     * @param op            constructing operation
     */
    SetInfiniteSet::SetInfiniteSet(unsigned pc, CmplVal *arr, unsigned short op)
    {
        _partCnt = pc;
        _parts = arr;
        _constructOp = op;

        _markNF = false;
        _isCanonical = true;

        CmplVal *s = arr;
        for (unsigned r = 0; r < pc; r++, s++) {
            if (SetBase::hasUserOrder(*s)) {
                CmplVal s2;
                SetBase::stripOrder(*s, s2);
                s->moveFrom(s2, true);
            }

            if (_isCanonical && !SetBase::isCanonical(*s))
                _isCanonical = false;
        }
    }


    /**
     * get minimal rank of tuples within the tuple set
     */
    unsigned SetInfiniteSet::minRank() const
    {
        CmplVal *p = _parts;
        unsigned r = SetBase::minRank(*p);

        p++;
        if (r == 0) {
            return (_constructOp == ICS_OPER_SUB && SetBase::minRank(*p) == 0 ? 1 : 0);
        }
        else {
            if (_constructOp == ICS_OPER_ADD) {
                for (unsigned i = 1; i < _partCnt; i++, p++)
                    r = min(SetBase::minRank(*p), r);
            }
            else if (_constructOp == ICS_OPER_MUL) {
                for (unsigned i = 1; i < _partCnt; i++, p++)
                    r = max(r, SetBase::minRank(*p));
            }
        }

        return r;
    }


    /**
     * get maximal rank of tuples within the tuple set
     * @param ub        upper bound for return value
     */
    unsigned SetInfiniteSet::maxRank(unsigned ub) const
    {
        CmplVal *p = _parts;
        unsigned r = SetBase::maxRank(*p, ub);
        if (r == ub && _constructOp != ICS_OPER_MUL)
            return ub;

        p++;
        if (_constructOp == ICS_OPER_ADD) {
            for (unsigned i = 1; i < _partCnt; i++, p++) {
                unsigned rr = SetBase::maxRank(*p, ub);
                if (rr == ub)
                    return ub;

                if (rr > r)
                    r = rr;
            }
        }
        else if (_constructOp == ICS_OPER_MUL) {
            unsigned rr = SetBase::maxRank(*p, ub);
            if (rr < r)
                r = rr;
        }

        return r;
    }


    /**
     * get whether all tupels in the tuple set have the same rank
     */
    bool SetInfiniteSet::oneRank() const
    {
        if (SetBase::oneRank(*_parts))
            return (minRank() == maxRank());
        else
            return false;
    }

}

