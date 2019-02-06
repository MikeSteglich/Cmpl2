
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


#include "ValFormula.hh"


namespace cmpl
{


    /************** ValFormulaVar **********/

    /**
     * get whether this formula is an expression with boolean value
     */
    bool ValFormulaVar::isBool() const
    {
        // boolean expression if optimization variable is binary without factor
        return (_optVar.t == TP_OPT_VAR && _factor.isNumOne(true) && _optVar.optVar()->binVar());
    }

    /**
     * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
     * @param neg           return if the binary variable negated
     * @return              binary variable / NULL: other formula
     */
    OptVar* ValFormulaVar::asSingleBin(bool& neg)
    {
        return (isBool() ? _optVar.optVar() : NULL);
    }

    /**
     * fills coefficients from this constraint for linear model per column
     * @param row			identity number of this row
     * @param coeffs		array to fill with vector of coefficients per column
     * @param lhs			this formula is left hand side of comparison
     */
    void ValFormulaVar::fillCoeffInLinearModelColIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, bool lhs)
    {
        if (_optVar.t == TP_OPT_VAR) {
            if (!_factor.isNumNull()) {
                unsigned long n = _optVar.optVar()->id();
                vector<LinearModel::Coefficient> *cp = coeffs + n - 1;

                if (cp->size() && cp->back().idRC == row)
                    cp->back().add(_factor, !lhs);
                else
                    cp->push_back(LinearModel::Coefficient(row, _factor, !lhs));
            }
        }
    }


    /**
     * fills coefficients from this constraint for linear model per row
     * @param row			identity number of this row
     * @param coeffs		vector to fill of coefficients for this row
     * @param colMap		map number of column to index in vector coeffs
     * @param lhs			this formula is left hand side of comparison
     */
    void ValFormulaVar::fillCoeffInLinearModelRowIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, map<unsigned long, unsigned long>& colMap, bool lhs)
    {
        if (_optVar.t == TP_OPT_VAR) {
            if (!_factor.isNumNull()) {
                unsigned long n = _optVar.optVar()->id();

                if (colMap.count(n))
                    coeffs->at(colMap[n]).add(_factor, !lhs);
                else {
                    colMap[n] = coeffs->size();
                    coeffs->push_back(LinearModel::Coefficient(n, _factor, !lhs));
                }
            }
        }
    }



    /************** ValFormulaVarProd **********/

    /**
     * set model properties from this constraint
     * @param prop          properties of optimization model
     */
    void ValFormulaVarProd::setModelProperties(OptModel::Properties& prop) const
    {
        unsigned cr = 0, ci = 0, cb = 0;
        for (unsigned i = 0; i < _optVars.size(); i++) {
            OptVar *v = _optVars[i].optVar();
            if (v->binVar())
                cb++;
            else if (v->intVar())
                ci++;
            else
                cr++;
        }

        if ((cb && prop.vartypes == 0) || (ci && prop.vartypes < 2))
            prop.vartypes = (ci ? 2 : 1);

        if (_optVars.size() > 1) {
            if (cr >= 2 && !prop.varprodReal)
                prop.varprodReal = 1;

            if ((cb || ci) && prop.varprodInt < 2) {
                if (ci && cr + ci >= 2)
                    prop.varprodInt = 2;
                else if (prop.varprodInt == 0)
                    prop.varprodInt = 1;
            }
        }
    }



    /************** ValFormulaLinearComb **********/

    /**
     * set model properties from this constraint
     * @param prop          properties of optimization model
     */
    void ValFormulaLinearComb::setModelProperties(OptModel::Properties& prop) const
    {
        for (unsigned i = 1; i < _terms.size(); i += 2) {
            if (!_terms[i-1].isNumNull()) {
                if (_terms[i].t == TP_OPT_VAR) {
                    if (prop.vartypes < 2) {
                        OptVar *v = _terms[i].optVar();
                        if (v->binVar() && prop.vartypes == 0)
                            prop.vartypes = 1;
                        else if (v->intVar())
                            prop.vartypes = 2;
                    }
                }
                else if (_terms[i].t == TP_FORMULA) {
                    ValFormula *f = _terms[i].valFormula();
                    f->setModelProperties(prop);
                }
            }
        }
    }


    /**
     * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
     * @param neg           return if the binary variable negated
     * @return              binary variable / NULL: other formula
     */
    OptVar* ValFormulaLinearComb::asSingleBin(bool& neg)
    {
        if (_linear && _terms.size() == 2 && _terms[0].isNumOne() && _constTerm.isNumNull(true)) {
            CmplVal& v = _terms[1];
            if (v.t == TP_OPT_VAR && v.optVar()->binVar()) {
                neg = false;
                return v.optVar();
            }
        }

        return NULL;
    }

    /**
     * fills coefficients from this constraint for linear model per column
     * @param row			identity number of this row
     * @param coeffs		array to fill with vector of coefficients per column
     * @param lhs			this formula is left hand side of comparison
     */
    void ValFormulaLinearComb::fillCoeffInLinearModelColIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, bool lhs)
    {
        if (!_linear)
            throw NonLinearModelException(row);

        for (unsigned i = 0; i < _terms.size(); i += 2) {
            if (!_terms[i].isNumNull()) {
                unsigned long n = _terms[i+1].optVar()->id();
                vector<LinearModel::Coefficient> *cp = coeffs + n - 1;

                if (cp->size() && cp->back().idRC == row)
                    cp->back().add(_terms[i], !lhs);
                else
                    cp->push_back(LinearModel::Coefficient(row, _terms[i], !lhs));
            }
        }
    }


    /**
     * fills coefficients from this constraint for linear model per row
     * @param row			identity number of this row
     * @param coeffs		vector to fill of coefficients for this row
     * @param colMap		map number of column to index in vector coeffs
     * @param lhs			this formula is left hand side of comparison
     */
    void ValFormulaLinearComb::fillCoeffInLinearModelRowIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, map<unsigned long, unsigned long>& colMap, bool lhs)
    {
        if (!_linear)
            throw NonLinearModelException(row);

        for (unsigned i = 0; i < _terms.size(); i += 2) {
            if (!_terms[i].isNumNull()) {
                unsigned long n = _terms[i+1].optVar()->id();

                if (colMap.count(n))
                    coeffs->at(colMap[n]).add(_terms[i], !lhs);
                else {
                    colMap[n] = coeffs->size();
                    coeffs->push_back(LinearModel::Coefficient(n, _terms[i], !lhs));
                }
            }
        }
    }


    /**
     * fills right hand side of this constraint for linear model
     * @param row			identity number of this row
     * @param rhs			right hand side to fill (valid are only TP_INT and TP_REAL)
     * @param lhs			this formula is left hand side of comparison
     */
    void ValFormulaLinearComb::fillRhsInLinearModelIntern(unsigned long row, LinearModel::Coefficient *rhs, bool lhs)
    {
        if (!_linear)
            throw NonLinearModelException(row);

        if (!_constTerm.isNumNull(true)) {
            rhs->add(_constTerm, lhs);
        }
    }



    /************** ValFormulaCompare **********/

    /**
     * set model properties from this constraint
     * @param prop          properties of optimization model
     */
    void ValFormulaCompare::setModelProperties(OptModel::Properties& prop) const
    {
        if (_leftSide.t == TP_FORMULA)
            _leftSide.valFormula()->setModelProperties(prop);

        if (_rightSide.t == TP_FORMULA)
            _rightSide.valFormula()->setModelProperties(prop);
    }


    /**
     * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
     * @param neg           return if the binary variable negated
     * @return              binary variable / NULL: other formula
     */
    OptVar* ValFormulaCompare::asSingleBin(bool& neg)
    {
        if (_leftSide.t == TP_FORMULA && _rightSide.isScalarNumber()) {
            bool ineg;
            OptVar *sbv = _leftSide.valFormula()->asSingleBin(ineg);
            if (sbv && !ineg) {
                if (_rightSide.isNumOne()) {
                    if (_compGe) {
                        neg = _compNeg;
                        return sbv;
                    }
                }

                else if (_rightSide.isNumNull()) {
                    if (_compLe) {
                        neg = !_compNeg;
                        return sbv;
                    }
                }
            }
        }

        return NULL;
    }

    /**
     * swap sides to ensure that a simple value stands on the right side
     */
    void ValFormulaCompare::checkSwapSides()
    {
        if (_leftSide.isScalarNumber()) {
            CmplVal s;
            s.moveFrom(_leftSide);
            _leftSide.moveFrom(_rightSide);
            _rightSide.moveFrom(s);

            swap(_compGe, _compLe);
        }

        if (_leftSide.t == TP_OPT_VAR) {
            CmplVal f(TP_FORMULA, new ValFormulaVar(syntaxElem(), _leftSide.optVar()));
            _leftSide.moveFrom(f, true);
        }

        if (_rightSide.t == TP_OPT_VAR) {
            CmplVal f(TP_FORMULA, new ValFormulaVar(syntaxElem(), _rightSide.optVar()));
            _rightSide.moveFrom(f, true);
        }
    }

    /**
     * fills coefficients from this constraint for linear model per column
     * @param row			identity number of this row
     * @param coeffs		array to fill with vector of coefficients per column
     */
    void ValFormulaCompare::fillCoeffInLinearModelCol(unsigned long row, vector<LinearModel::Coefficient> *coeffs)
    {
        if (_leftSide.t == TP_FORMULA) {
            ValFormula *f = _leftSide.valFormula();
            f->fillCoeffInLinearModelColIntern(row, coeffs, true);
        }

        if (_rightSide.t == TP_FORMULA) {
            ValFormula *f = _rightSide.valFormula();
            f->fillCoeffInLinearModelColIntern(row, coeffs, false);
        }
    }


    /**
     * fills coefficients from this constraint for linear model per row
     * @param row			identity number of this row
     * @param coeffs		vector to fill of coefficients for this row
     */
    void ValFormulaCompare::fillCoeffInLinearModelRow(unsigned long row, vector<LinearModel::Coefficient> *coeffs)
    {
        map<unsigned long, unsigned long> colMap;

        if (_leftSide.t == TP_FORMULA) {
            ValFormula *f = _leftSide.valFormula();
            f->fillCoeffInLinearModelRowIntern(row, coeffs, colMap, true);
        }

        if (_rightSide.t == TP_FORMULA) {
            ValFormula *f = _rightSide.valFormula();
            f->fillCoeffInLinearModelRowIntern(row, coeffs, colMap, false);
        }
    }


    /**
     * fills mode and right hand side of this constraint for linear model
     * @param row			identity number of this row
     * @param mode			mode to fill (valid are: 'N', 'L', 'G', 'E': like in MPS; or '+': maximize, or '-': minimize)
     * @param rhs			right hand side to fill
     */
    void ValFormulaCompare::fillModeRhsInLinearModel(unsigned long row, char *mode, LinearModel::Coefficient *rhs)
    {
        if (!linearConstraint())
            throw NonLinearModelException(row);

        if (_rightSide.t == TP_FORMULA) {
            ValFormula *f = _rightSide.valFormula();
            f->fillRhsInLinearModelIntern(row, rhs, false);
        }
        else if (_rightSide.isScalarNumber()) {
            rhs->add(_rightSide);
        }

        if (_leftSide.t == TP_FORMULA) {
            ValFormula *f = _leftSide.valFormula();
            f->fillRhsInLinearModelIntern(row, rhs, true);
        }
        else if (_leftSide.isScalarNumber()) {
            rhs->add(_leftSide, true);
        }

        *mode = (_compGe ? (_compLe ? 'E' : 'G') : (_compLe ? 'L' : 'N'));
    }



    /************** ValFormulaObjective **********/

    /**
     * constructor
     * @param f         formula to minimize or to maximize, should be TP_FORMULA
     * @param ma        true: maximize; false: minimize
     */
    ValFormulaObjective::ValFormulaObjective(unsigned se, CmplVal *f, bool ma): ValFormula(se)
    {
        if (f->t == TP_OPT_VAR)
            _formula.set(TP_FORMULA, new ValFormulaVar(se, f->optVar()));
        else
            _formula.copyFrom(f, true, false);

        _maximize = ma;
    }

    /**
     * fills coefficients from this constraint for linear model per column
     * @param row			identity number of this row
     * @param coeffs		array to fill with vector of coefficients per column
     */
    void ValFormulaObjective::fillCoeffInLinearModelCol(unsigned long row, vector<LinearModel::Coefficient> *coeffs)
    {
        if (_formula.t == TP_FORMULA) {
            ValFormula *f = _formula.valFormula();
            f->fillCoeffInLinearModelColIntern(row, coeffs, true);
        }
    }


    /**
     * fills coefficients from this constraint for linear model per row
     * @param row			identity number of this row
     * @param coeffs		vector to fill of coefficients for this row
     */
    void ValFormulaObjective::fillCoeffInLinearModelRow(unsigned long row, vector<LinearModel::Coefficient> *coeffs)
    {
        map<unsigned long, unsigned long> colMap;

        if (_formula.t == TP_FORMULA) {
            ValFormula *f = _formula.valFormula();
            f->fillCoeffInLinearModelRowIntern(row, coeffs, colMap, true);
        }
    }


    /**
     * fills mode and right hand side of this constraint for linear model
     * @param row			identity number of this row
     * @param mode			mode to fill (valid are: 'N', 'L', 'G', 'E': like in MPS; or '+': maximize, or '-': minimize)
     * @param rhs			right hand side to fill
     */
    void ValFormulaObjective::fillModeRhsInLinearModel(unsigned long row, char *mode, LinearModel::Coefficient *rhs)
    {
        if (!linearConstraint())
            throw NonLinearModelException(row);

        if (_formula.t == TP_FORMULA) {
            ValFormula *f = _formula.valFormula();
            f->fillModeRhsInLinearModel(row, mode, rhs);
        }

        *mode = (_maximize ? '+' : '-');
    }



    /************** ValFormulaLogCon **********/

    /**
     * set model properties from this constraint
     * @param prop          properties of optimization model
     */
    void ValFormulaLogCon::setModelProperties(OptModel::Properties& prop) const
    {
        int pcp = prop.conditions;

        for (unsigned i = 0; i < _formulas.size(); i++) {
            _formulas[i].valFormula()->setModelProperties(prop);
        }

        if (_logNeg || _logOr || (!pcp && prop.conditions == -1))
            prop.conditions = 1;
        else if (!prop.conditions)
            prop.conditions = -1;
    }

    /**
     * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
     * @param neg           return if the binary variable negated
     * @return              binary variable / NULL: other formula
     */
    OptVar* ValFormulaLogCon::asSingleBin(bool& neg)
    {
        if (_formulas.size() == 1) {
            CmplVal& f = _formulas[0];
            if (f.t == TP_FORMULA) {
                ValFormula *frml = f.valFormula();
                if (frml->isBool()) {
                    bool ineg;
                    OptVar *sbv = frml->asSingleBin(ineg);
                    if (sbv) {
                        neg = (ineg != _logNeg);
                        return sbv;
                    }
                }
            }
        }

        return NULL;
    }

}

