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


#include "OptModel.hh"
#include "ValFormula.hh"


using namespace std;


namespace cmpl
{
	// defines data class
	DATA_CLASS( OptModel );




    /****** OptVar ****/

    /**
     * constructor
     * @param om		result matrix
     * @param tp		data type
     * @param defTp		data type tp is default type
     * @param se		id of syntax element in the cmpl text creating this matrix element
     */
    OptVar::OptVar(OptModel *om, CmplVal &tp, bool defTp, unsigned se)
    {
        _dataType.copyFrom(tp, true, false);
        _hasDataType = !defTp;
        _syntaxElem = se;

        ValueTreeRoot& vtr = om->cols();
        vtr.insertNewElem(this);
        incRef();
    }



    /****** OptCon ****/

    /**
     * constructor
     * @param om		result matrix
     * @param f			formula for constraint or objective
     * @param obj		true: objective / false: constraint
     * @param se		id of syntax element in the cmpl text creating this matrix element
     */
    OptCon::OptCon(OptModel *om, CmplVal& f, bool obj, unsigned se)
    {
        _formula.copyFrom(f, true, false);
        _objective = obj;
        _syntaxElem = se;

        ValueTreeRoot& vtr = om->rows();
        vtr.insertNewElem(this);
        incRef();
    }

    /**
     * get whether this is a linear constraint or objective
     */
    bool OptCon::linearConstraint()
    {
        return (_formula.t == TP_FORMULA ? _formula.valFormula()->linearConstraint() : false);
    }



    /****** LinearModel ****/

    /**
     * add another value to the coefficient
     * @param v			other value
     * @param neg		negate value v
     */
    void LinearModel::Coefficient::add(CmplVal& v, bool neg)
    {
        intType iv = (!v ? (neg ? -1 : 1) : (v.t == TP_INT || v.t == TP_BIN ? (neg ? -v.v.i : v.v.i) : 0));
        realType rv = (v.t == TP_REAL ? (neg ? -v.v.r : v.v.r) : 0.0);

        if (iCoeff != 0) {
            if (iv)
                iCoeff += iv;
            else {
                rCoeff = (realType)iCoeff + rv;
                iCoeff = 0;
            }
        }
        else if (rCoeff != 0) {
            rCoeff += (iv ? (realType)iv : rv);
        }
        else {
            iCoeff = iv;
            rCoeff = rv;
        }
    }


    /**
     * get coefficient value as string suitable for output
     * @param rf		format spezifier for real number output or NULL for standard format
     * @param ms		max length of output string
     * @return 			coefficient value as string
     */
    string LinearModel::Coefficient::outString(const char *rf, unsigned ms) const
    {
        char vstr[101];

        unsigned sz;
        if (iCoeff != 0 || rCoeff == 0)
            sz = snprintf(vstr, 100, CMPLINT_STDFORMAT, iCoeff);
        else
            sz = snprintf(vstr, 100, (rf ?: CMPLREAL_STDFORMAT), rCoeff);

        if (sz > ms)
            throw OutputValueToLongException();

        return string(vstr);
    }


    /**
     * fill _coeffs, _rhs and _mode from sourve optimization matrix _om
     */
    void LinearModel::fill()
    {
        ValueTreeRoot& vtr = (_byCol ? _om->cols() : _om->rows());
        ValueTreeRoot& rw = _om->rows();

        _coeffs = new vector<Coefficient>[vtr.size()];
        _rhs = new Coefficient[rw.size()];
        _mode = new char[rw.size()];

        Coefficient *rhsp = _rhs;
        char *modep = _mode;

        for (unsigned long r = 1; r <= rw.size(); r++, rhsp++, modep++) {
            ValueTreeElem *vte = rw.getElem(r);
            if (vte) {
                OptCon *oc = dynamic_cast<OptCon *>(vte);
                if (!oc)
                    throw NonLinearModelException(r);

                ValFormula *frm = oc->formula();

                if (!frm || !frm->linearConstraint())
                    throw NonLinearModelException(r);

                if (_byCol)
                    frm->fillCoeffInLinearModelCol(r, _coeffs);
                else
                    frm->fillCoeffInLinearModelRow(r, _coeffs+r-1);

                *modep = 'N';
                rhsp->init(r);
                frm->fillModeRhsInLinearModel(r, modep, rhsp);
            }
            else {
                *modep = 0;
            }
        }
    }



    /****** OptModel ****/

    /**
     * get array of names for usage on formatted outputs of the columns or rows of the model
     * @param col				true for column names or false for row names
     * @param sstore			stored string values
     * @param prefStd			prefix for standard name if the element have no name in the value tree / NULL if no standard name
     * @param prefSubs			prefix for substitute name, used if a regular name not exists or is not unique
     * @param quote				quote char for strings, 0 if no one
     * @param rplSp				replacement char for space, 0 for removing spaces, space char for leaving spaces unchanged
     * @param mLen				max length for result name
     * @return					array of the names
     */
    string *OptModel::outNamesArray(bool col, StringStore *sstore, const char *prefStd, const char *prefSubs, char quote, char rplSp, unsigned mLen)
    {
        ValueTreeRoot& vtr = (col ? _cols : _rows);
        unordered_map<string, unsigned long> names;

        unsigned cntSubs = 0;
        for (unsigned long i = 0; i < vtr.size(); i++) {
            if (vtr[i])
                vtr[i]->insOutName(sstore, names, prefStd, prefSubs, cntSubs, quote, rplSp, mLen);
        }

        string *arr = new string[vtr.size()];
        for (unordered_map<string, unsigned long>::iterator it = names.begin(); it != names.end(); it++)
            arr[it->second-1] = it->first;

        return arr;
    }


    /**
     * delete all data
     */
    void OptModel::cleanUp()
    {
        //TODO

        if (_modCol)
            delete _modCol;

        if (_modRow)
            delete _modRow;
    }


    /**
     * check if serialization to or from stream should be done for the data object
     * @param si		serialization info
     * @param data		main data object
     * @return			true if serialization should be done
     */
    bool OptModel::checkSerialize(MainData::SerializeInfo& si, const MainData *data)
    {
        //TODO
        return false;
    }


    /**
     * write data object to output stream
     * @param si		serialization info
     * @param data		main data object
     */
    void OptModel::serializeTo(MainData::SerializeInfo& si, const MainData *data)
    {
        //TODO
    }


    /**
     * fill data object from input stream
     * @param si		serialization info
     * @param data		main data object
     * @param pos		position of input string, returns iterated position
     * @param subCnt	count of sub data objects
     * @param lc		line count per element or 0 if elements are len coded
     * @param rline		remaining section start line
     */
    void OptModel::deserializeFrom(MainData::SerializeInfo& si, const MainData *data, int subCnt, int lc, string &rline)
    {
        //TODO
    }


    /**
     * sets  whether the model is integer or not
     * @param isInt				true for integer
     */
    bool OptModel::isLinearModel() {

        if (!_linearModelChecked) {
            unsigned long rowCnt = _rows.size();

            for (unsigned long i = 0; i < rowCnt; i++) {
                OptCon *oc = dynamic_cast<OptCon *>(_rows[i]);
                if (oc) {
                    if (!oc->linearConstraint())
                        _isLinearModel=false;
                }
            }

           _linearModelChecked=true;
        }
        return _isLinearModel;
    }

}

