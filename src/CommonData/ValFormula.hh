
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


#ifndef VALFORMULA_HH
#define VALFORMULA_HH


#include "CmplVal.hh"
#include "OptModel.hh"


using namespace std;



namespace cmpl
{
	/**
	 * base class for formulas, especially for use in constraints
	 */
	class ValFormula : public CmplObjBase
	{
    private:
        unsigned _syntaxElem;               ///< id of syntax element in the cmpl text creating this formula value

    protected:
        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         */
        ValFormula(unsigned se): _syntaxElem(se)    { }

    public:
        /**
         * get id of syntax element in the cmpl text creating this matrix element
         */
        unsigned syntaxElem() const                 { return _syntaxElem; }

        /**
         * get whether this formula is suitable for linear constraint or objective
         */
        virtual bool linearConstraint() const   	{ return false; }

        /**
         * get whether this formula is an expression with boolean value
         */
        virtual bool isBool() const                 { return false; }

        /**
         * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
         * @param neg           return if the binary variable negated
         * @return              binary variable / NULL: other formula
         */
        virtual OptVar* asSingleBin(bool& neg)      { return NULL; }

        /**
         * get whether this formula is suitable for optimization row (linear or non-linear)
         * @param obj			true: as objective / false: as constraint
         * @return
         */
        virtual bool canOptRow(bool obj) const		{ return false; }

        /**
         * get count of direct parts of the formula
         */
        virtual unsigned partCount() const          { return 0; }

        /**
         * get direct part
         * @param i     number of part
         * @return
         */
        virtual CmplVal *getPart(unsigned i)        { return NULL; }


        /************** functions for filling linear model **********/
    public:
        /**
         * fills coefficients from this constraint for linear model per column
         * @param row			identity number of this row
         * @param coeffs		array to fill with vector of coefficients per column
         */
        virtual void fillCoeffInLinearModelCol(unsigned long row, vector<LinearModel::Coefficient> *coeffs)					{ throw NonLinearModelException(row); }

        /**
         * fills coefficients from this constraint for linear model per row
         * @param row			identity number of this row
         * @param coeffs		vector to fill of coefficients for this row
         */
        virtual void fillCoeffInLinearModelRow(unsigned long row, vector<LinearModel::Coefficient> *coeffs)					{ throw NonLinearModelException(row); }

        /**
         * fills mode and right hand side of this constraint for linear model
         * @param row			identity number of this row
         * @param mode			mode to fill (valid are: 'N', 'L', 'G', 'E': like in MPS; or '+': maximize, or '-': minimize)
         * @param rhs			right hand side to fill
         */
        virtual void fillModeRhsInLinearModel(unsigned long row, char *mode, LinearModel::Coefficient *rhs)					{ throw NonLinearModelException(row); }

        /**
         * fills coefficients from this constraint for linear model per column
         * @param row			identity number of this row
         * @param coeffs		array to fill with vector of coefficients per column
         * @param lhs			this formula is left hand side of comparison
         */
        virtual void fillCoeffInLinearModelColIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, bool lhs)		{ throw NonLinearModelException(row); }

        /**
         * fills coefficients from this constraint for linear model per row
         * @param row			identity number of this row
         * @param coeffs		vector to fill of coefficients for this row
         * @param colMap		map number of column to index in vector coeffs
         * @param lhs			this formula is left hand side of comparison
         */
        virtual void fillCoeffInLinearModelRowIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, map<unsigned long, unsigned long>& colMap, bool lhs)		{ throw NonLinearModelException(row); }

        /**
         * fills right hand side of this constraint for linear model
         * @param row			identity number of this row
         * @param rhs			right hand side to fill
         * @param lhs			this formula is left hand side of comparison
         */
        virtual void fillRhsInLinearModelIntern(unsigned long row, LinearModel::Coefficient *rhs, bool lhs)					{ throw NonLinearModelException(row); }


        //TODO: andere virtuelle Funktionen fuer Zugriff, soweit ausserhalb Interpreter-Modul benoetigt
	};



    /**
     * base class for formula for linear combination of optimization variables
     */
    class ValFormulaLinearCombBase : public ValFormula
    {
    protected:
        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         */
        ValFormulaLinearCombBase(unsigned se): ValFormula(se)   { }

    public:
        /**
         * get whether this formula is suitable for linear constraint or objective
         */
        bool linearConstraint() const override 		{ return true; }

        /**
         * get whether this formula is suitable for optimization row (linear or non-linear)
         * @param obj			true: as objective / false: as constraint
         * @return
         */
        bool canOptRow(bool obj) const override		{ return true; }

        /**
         * get count of terms
         */
        virtual unsigned termCnt() const			{ return 0; }

        /**
         * get factor of a term
         * @param i		number of term
         */
        virtual CmplVal *termFac(unsigned i)        { return NULL; }

        /**
         * get factor of a term
         * @param i		optimization variable of term
         */
        virtual CmplVal *termVar(unsigned i)        { return NULL; }

        /**
         * get constant term
         */
        virtual CmplVal *constTerm()    			{ return NULL; }


        /************** filling linear model **********/
    public:
        /**
         * fills coefficients from this constraint for linear model per column
         * @param row			identity number of this row
         * @param coeffs		array to fill with vector of coefficients per column
         */
        void fillCoeffInLinearModelCol(unsigned long row, vector<LinearModel::Coefficient> *coeffs) override		{ fillCoeffInLinearModelColIntern(row, coeffs, true); }

        /**
         * fills coefficients from this constraint for linear model per row
         * @param row			identity number of this row
         * @param coeffs		vector to fill of coefficients for this row
         */
        void fillCoeffInLinearModelRow(unsigned long row, vector<LinearModel::Coefficient> *coeffs)	override		{ map<unsigned long, unsigned long> colMap; fillCoeffInLinearModelRowIntern(row, coeffs, colMap, true); }

        /**
         * fills mode and right hand side of this constraint for linear model
         * @param row			identity number of this row
         * @param mode			mode to fill (valid are: 'N', 'L', 'G', 'E': like in MPS; or '+': maximize, or '-': minimize)
         * @param rhs			right hand side to fill
         */
        void fillModeRhsInLinearModel(unsigned long row, char *mode, LinearModel::Coefficient *rhs)	override		{ *mode = 'N'; fillRhsInLinearModelIntern(row, rhs, true); }
    };


    /**
     * class for formula of single optimization variable with optional factor
     */
    class ValFormulaVar : public ValFormulaLinearCombBase
    {
    protected:
        CmplVal _factor;					///< factor, can only be TP_REAL or TP_INT (or TP_EMPTY if no factor)
        CmplVal _optVar;					///< optimization variable, must be TP_OPT_VAR

    public:
        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaVar(ValFormulaVar *f): ValFormulaLinearCombBase(f->syntaxElem()), _factor(f->_factor), _optVar(f->_optVar)						{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         */
        inline ValFormulaVar(unsigned se, OptVar *ov): ValFormulaLinearCombBase(se), _factor(), _optVar(TP_OPT_VAR, ov, true)							{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         * @param f			factor
         */
        inline ValFormulaVar(unsigned se, OptVar *ov, CmplVal& f): ValFormulaLinearCombBase(se), _factor(f), _optVar(TP_OPT_VAR, ov, true)              { }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         * @param r			factor
         */
        inline ValFormulaVar(unsigned se, OptVar *ov, realType r): ValFormulaLinearCombBase(se), _factor(TP_REAL, r), _optVar(TP_OPT_VAR, ov, true)		{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         * @param i			factor
         */
        inline ValFormulaVar(unsigned se, OptVar *ov, intType i): ValFormulaLinearCombBase(se), _factor(TP_INT, i), _optVar(TP_OPT_VAR, ov, true)       { }

        /**
         * destructor
         */
        virtual ~ValFormulaVar()		{ _factor.dispose(); _optVar.dispose(); }


        /**
         * get whether this formula is an expression with boolean value
         */
        bool isBool() const override;

        /**
         * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
         * @param neg           return if the binary variable negated
         * @return              binary variable / NULL: other formula
         */
        OptVar* asSingleBin(bool& neg) override;

        /**
         * get count of direct parts of the formula
         */
        unsigned partCount() const override             { return 2; }

        /**
         * get direct part
         * @param i     number of part
         * @return
         */
        CmplVal *getPart(unsigned i) override           { return (i == 0 ? &_factor : (i == 1 ? &_optVar : NULL)); }

        /**
         * get count of terms
         */
        unsigned termCnt() const override               { return 1; }

        /**
         * get factor of a term
         * @param i		number of term
         * @return
         */
        CmplVal *termFac(unsigned i) override           { return (i == 0 && _factor ? &_factor : NULL); }

        /**
         * get factor of a term
         * @param i		optimization variable of term
         * @return
         */
        CmplVal *termVar(unsigned i) override           { return (i == 0 ? &_optVar : NULL); }


        /**
         * write contents of the object to a stream
         * @param modp			calling module
         * @param mode			mode for output: 0=direct; 1=part of other value
         */
        void write(ostream& ostr, ModuleBase *modp, int mode = 0) const override     { ostr << "<f-v: "; if (_factor) { _factor.write(ostr, modp, 1); ostr << '*'; } _optVar.write(ostr, modp, 1); ostr << '>'; }


        /************** filling linear model **********/
    public:
        /**
         * fills coefficients from this constraint for linear model per column
         * @param row			identity number of this row
         * @param coeffs		array to fill with vector of coefficients per column
         * @param lhs			this formula is left hand side of comparison
         */
        void fillCoeffInLinearModelColIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, bool lhs) override;

        /**
         * fills coefficients from this constraint for linear model per row
         * @param row			identity number of this row
         * @param coeffs		vector to fill of coefficients for this row
         * @param colMap		map number of column to index in vector coeffs
         * @param lhs			this formula is left hand side of comparison
         */
        void fillCoeffInLinearModelRowIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, map<unsigned long, unsigned long>& colMap, bool lhs) override;

        /**
         * fills right hand side of this constraint for linear model
         * @param row			identity number of this row
         * @param rhs			right hand side to fill
         * @param lhs			this formula is left hand side of comparison
         */
        void fillRhsInLinearModelIntern(unsigned long row, LinearModel::Coefficient *rhs, bool lhs)	override							{ /* leave rhs unchanged, nothing to do */ }
    };


    /**
     * class for formula of product of two or more single optimization variables, and with an optional constant factor
     */
    class ValFormulaVarProd : public ValFormula
    {
    protected:
        CmplVal _factor;					///< factor, can only be TP_REAL or TP_INT (or TP_EMPTY if no factor)
        vector<CmplVal> _optVars;			///< optimization variables, must be TP_OPT_VAR

    public:
        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaVarProd(ValFormulaVarProd *f): ValFormula(f->syntaxElem()), _factor(f->_factor), _optVars(f->_optVars)					{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f			formula for variable
         */
        inline ValFormulaVarProd(unsigned se, ValFormulaVar *f): ValFormula(se)      { if(f->termFac(0)) _factor.copyFrom(f->termFac(0)); _optVars.push_back(CmplVal(f->termVar(0))); }

        /**
         * destructor
         */
        virtual ~ValFormulaVarProd()		{ _factor.dispose(); for (unsigned i = 0; i < _optVars.size(); i++) { _optVars[i].dispose(); }; }

        /**
         * get count of direct parts of the formula
         */
        unsigned partCount() const override             { return (_optVars.size() + 1); }

        /**
         * get direct part
         * @param i     number of part
         * @return
         */
        CmplVal *getPart(unsigned i) override           { return (i == 0 ? &_factor : (i <= _optVars.size() ? &(_optVars[i-1]) : NULL)); }

        /**
         * write contents of the object to a stream
         * @param modp			calling module
         * @param mode			mode for output: 0=direct; 1=part of other value
         */
        void write(ostream& ostr, ModuleBase *modp, int mode = 0) const override    { ostr << "<f-vp: "; if (_factor) { _factor.write(ostr, modp, 1); } for (unsigned i = 0; i < _optVars.size(); i++) { ostr << '*'; _optVars[i].write(ostr, modp, 1); } ostr << '>'; }
    };


    /**
     * formula for linear combination of optimization variables
     */
    class ValFormulaLinearComb : public ValFormulaLinearCombBase
    {
    protected:
        bool _linear;                       ///< flag whether this formula is suitable for linear constraint or objective
        CmplVal _constTerm;					///< term without variable, can only be TP_REAL or TP_INT (or TP_EMPTY if no such term exists)
        vector<CmplVal> _terms;				///< every term has two elements in this vector, first coefficient (must be TP_REAL or TP_INT), second variable (must be TP_OPT_VAR if _linear)

    public:
        /**
         * empty constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         */
        inline ValFormulaLinearComb(unsigned se): ValFormulaLinearCombBase(se), _linear(true), _constTerm(), _terms()                       { }

        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaLinearComb(ValFormulaLinearComb *f): ValFormulaLinearCombBase(f->syntaxElem()), _linear(f->_linear), _constTerm(f->_constTerm), _terms(f->_terms)		{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f			formula for variable
         */
        inline ValFormulaLinearComb(unsigned se, ValFormulaVar *f): ValFormulaLinearCombBase(se), _linear(true), _constTerm(), _terms()		{ _terms.push_back(f->termFac(0) ? CmplVal(f->termFac(0)) : CmplVal()); _terms.push_back(CmplVal(f->termVar(0))); }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         */
        inline ValFormulaLinearComb(unsigned se, OptVar *ov): ValFormulaLinearCombBase(se), _linear(true), _constTerm(), _terms()			{ _terms.push_back(CmplVal()); _terms.push_back(CmplVal(TP_OPT_VAR, ov)); }

        /**
         * destructor
         */
        virtual ~ValFormulaLinearComb()					{ _constTerm.dispose(); for (unsigned i = 0; i < _terms.size(); i++) { _terms[i].dispose(); } }


        /**
         * get whether this formula is suitable for linear constraint or objective
         */
        bool linearConstraint() const override          { return _linear; }

        /**
         * get count of direct parts of the formula
         */
        unsigned partCount() const override             { return (_terms.size() + 1); }

        /**
         * get direct part
         * @param i     number of part
         * @return
         */
        CmplVal *getPart(unsigned i) override           { return (i == 0 ? &_constTerm : (i <= _terms.size() ? &(_terms[i-1]) : NULL)); }

        /**
         * get count of terms
         */
        unsigned termCnt() const override               { return _terms.size() / 2; }

        /**
         * get factor of a term
         * @param i		number of term
         */
        CmplVal *termFac(unsigned i) override           { unsigned j = 2*i; return (j < _terms.size() && _terms[j] ? &(_terms[j]) : NULL); }

        /**
         * get factor of a term
         * @param i		optimization variable of term
         */
        CmplVal *termVar(unsigned i) override           { unsigned j = 2*i + 1; return (j < _terms.size() ? &(_terms[j]) : NULL); }

        /**
         * get constant term
         */
        CmplVal *constTerm() override                   { return &_constTerm; }

        /**
         * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
         * @param neg           return if the binary variable negated
         * @return              binary variable / NULL: other formula
         */
        OptVar* asSingleBin(bool& neg) override;

        /**
         * write contents of the object to a stream
         * @param modp			calling module
         * @param mode			mode for output: 0=direct; 1=part of other value
         */
        void write(ostream& ostr, ModuleBase *modp, int mode = 0) const override     { ostr << "<f-lc: "; if (_constTerm) { _constTerm.write(ostr, modp, 1); } for (unsigned i = 0; i < _terms.size(); i += 2) { ostr << " + "; if (_terms[i]) { _terms[i].write(ostr, modp, 1); ostr << '*'; } _terms[i+1].write(ostr, modp, 1); } ostr << '>'; }


        /************** filling linear model **********/
    public:
        /**
         * fills coefficients from this constraint for linear model per column
         * @param row			identity number of this row
         * @param coeffs		array to fill with vector of coefficients per column
         * @param lhs			this formula is left hand side of comparison
         */
        void fillCoeffInLinearModelColIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, bool lhs) override;

        /**
         * fills coefficients from this constraint for linear model per row
         * @param row			identity number of this row
         * @param coeffs		vector to fill of coefficients for this row
         * @param colMap		map number of column to index in vector coeffs
         * @param lhs			this formula is left hand side of comparison
         */
        void fillCoeffInLinearModelRowIntern(unsigned long row, vector<LinearModel::Coefficient> *coeffs, map<unsigned long, unsigned long>& colMap, bool lhs) override;

        /**
         * fills right hand side of this constraint for linear model
         * @param row			identity number of this row
         * @param rhs			right hand side to fill
         * @param lhs			this formula is left hand side of comparison
         */
        void fillRhsInLinearModelIntern(unsigned long row, LinearModel::Coefficient *rhs, bool lhs) override;
    };


    /**
     * formula for compare operation
     */
    class ValFormulaCompare : public ValFormula
    {
    protected:
        CmplVal _leftSide;					///< left side of compare, must be TP_FORMULA
        CmplVal _rightSide;					///< right side of compare, can be TP_FORMULA or TP_REAL or TP_INT
        bool _compGe;						///< check for left side greater or equal right side
        bool _compLe;						///< check for left side lesser or equal right side
        bool _compNeg;						///< negate comparison

    public:
        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaCompare(ValFormulaCompare *f): ValFormula(f->syntaxElem()), _leftSide(f->_leftSide), _rightSide(f->_rightSide), _compGe(f->_compGe), _compLe(f->_compLe), _compNeg(f->_compNeg)     { }

        /**
         * constructor
         * @param f			source formula
         */
        inline ValFormulaCompare(unsigned se, ValFormulaCompare *f, bool ge, bool le, bool neg): ValFormula(se), _leftSide(f->_leftSide), _rightSide(f->_rightSide), _compGe(ge), _compLe(le), _compNeg(neg) { }

        /**
         * constructor
         */
        inline ValFormulaCompare(unsigned se, CmplVal *ls, CmplVal *rs, bool ge, bool le, bool neg): ValFormula(se), _leftSide(ls), _rightSide(rs), _compGe(ge), _compLe(le), _compNeg(neg)                  { checkSwapSides(); }

        /**
         * constructor
         */
        inline ValFormulaCompare(unsigned se, ValFormula *ls, CmplVal *rs, bool ge, bool le, bool neg): ValFormula(se), _leftSide(TP_FORMULA, ls), _rightSide(rs), _compGe(ge), _compLe(le), _compNeg(neg)   { checkSwapSides(); }

        /**
         * destructor
         */
        virtual ~ValFormulaCompare()				{ _leftSide.dispose(); _rightSide.dispose(); }

        /**
         * get whether this formula is suitable for linear constraint or objective
         */
        bool linearConstraint()	const override		{ return (!_compNeg && (_leftSide.t == TP_REAL || _leftSide.t == TP_INT || (_leftSide.t == TP_FORMULA && _leftSide.valFormula()->linearConstraint())) && (_rightSide.t == TP_REAL || _rightSide.t == TP_INT || (_rightSide.t == TP_FORMULA && _rightSide.valFormula()->linearConstraint())) && (_leftSide.t == TP_FORMULA || _rightSide.t == TP_FORMULA)); }

        /**
         * get whether this formula is an expression with boolean value
         */
        bool isBool() const override                { return true; }

        /**
         * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
         * @param neg           return if the binary variable negated
         * @return              binary variable / NULL: other formula
         */
        OptVar* asSingleBin(bool& neg) override;

        /**
         * get whether this formula is suitable for optimization row (linear or non-linear)
         * @param obj			true: as objective / false: as constraint
         * @return
         */
        bool canOptRow(bool obj) const override		{ return !obj; }

        /**
         * get count of direct parts of the formula
         */
        unsigned partCount() const override         { return 2; }

        /**
         * get direct part
         * @param i     number of part
         * @return
         */
        CmplVal *getPart(unsigned i) override       { return (i == 0 ? &_leftSide : (i == 1 ? &_rightSide : NULL)); }

        /**
         * write contents of the object to a stream
         * @param modp			calling module
         * @param mode			mode for output: 0=direct; 1=part of other value
         */
        void write(ostream& ostr, ModuleBase *modp, int mode = 0) const override    { ostr << "<f-cmp: "; _leftSide.write(ostr, modp, 1); ostr << (_compNeg ? (_compGe ? (_compLe ? " <> " : " < ") : " > ") : (_compGe ? (_compLe ? " = " : " >= ") : " <= ")); _rightSide.write(ostr, modp, 1); ostr << '>'; }

    private:
        /**
         * swap sides to ensure that a simple value stands on the right side
         */
        void checkSwapSides();

        /************** filling linear model **********/
    public:
        /**
         * fills coefficients from this constraint for linear model per column
         * @param row			identity number of this row
         * @param coeffs		array to fill with vector of coefficients per column
         */
        void fillCoeffInLinearModelCol(unsigned long row, vector<LinearModel::Coefficient> *coeffs) override;

        /**
         * fills coefficients from this constraint for linear model per row
         * @param row			identity number of this row
         * @param coeffs		vector to fill of coefficients for this row
         */
        void fillCoeffInLinearModelRow(unsigned long row, vector<LinearModel::Coefficient> *coeffs) override;

        /**
         * fills mode and right hand side of this constraint for linear model
         * @param row			identity number of this row
         * @param mode			mode to fill (valid are: 'N', 'L', 'G', 'E': like in MPS; or '+': maximize, or '-': minimize)
         * @param rhs			right hand side to fill
         */
        void fillModeRhsInLinearModel(unsigned long row, char *mode, LinearModel::Coefficient *rhs) override;

    public:
        /**
         * get left or right side of compare
         * @param left          true: left side / false: right side
         * @param res           return of result value
         */
        inline void getSide(bool left, CmplVal& res)      { res.copyFrom((left ? _leftSide : _rightSide), true, false); }

        /**
         * get whether compare is greater or equal
         */
        inline bool isCompGe() const                { return _compGe; }

        /**
         * get whether compare is lesser or equal
         */
        inline bool isCompLe() const                { return _compLe; }

        /**
         * get whether compare is negated
         */
        inline bool isNeg() const                   { return _compNeg; }

    };


    /**
     * formula with operation for optimization direction
     */
    class ValFormulaObjective : public ValFormula
    {
    protected:
        CmplVal _formula;					///< formula to minimize or to maximize, should be TP_FORMULA
        bool _maximize;						///< true: maximize; false: minimize

    public:
        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f         formula to minimize or to maximize, should be TP_FORMULA
         * @param ma        true: maximize; false: minimize
         */
        ValFormulaObjective(unsigned se, CmplVal *f, bool ma);

        /**
         * destructor
         */
        virtual ~ValFormulaObjective()				{ _formula.dispose(); }

        /**
         * get whether this formula is suitable for linear constraint or objective
         */
        bool linearConstraint() const override		{ return (_formula.t == TP_FORMULA && _formula.valFormula()->linearConstraint()); }

        /**
         * get whether this formula is suitable for optimization row (linear or non-linear)
         * @param obj			true: as objective / false: as constraint
         * @return
         */
        bool canOptRow(bool obj) const override		{ return obj; }

        /**
         * get count of direct parts of the formula
         */
        unsigned partCount() const override         { return 1; }

        /**
         * get direct part
         * @param i     number of part
         * @return
         */
        CmplVal *getPart(unsigned i) override       { return (i == 0 ? &_formula : NULL); }

        /**
         * get formula to minimize or to maximize
         */
        inline CmplVal& formula()                   { return _formula; }

        /**
         * write contents of the object to a stream
         * @param modp			calling module
         * @param mode			mode for output: 0=direct; 1=part of other value
         */
        void write(ostream& ostr, ModuleBase *modp, int mode = 0) const override    { ostr << "<f-obj: "; _formula.write(ostr, modp, 1); ostr << " -> " << (_maximize ? "max" : "min") << '>'; }


        /************** filling linear model **********/
    public:
        /**
         * fills coefficients from this constraint for linear model per column
         * @param row			identity number of this row
         * @param coeffs		array to fill with vector of coefficients per column
         */
        void fillCoeffInLinearModelCol(unsigned long row, vector<LinearModel::Coefficient> *coeffs) override;

        /**
         * fills coefficients from this constraint for linear model per row
         * @param row			identity number of this row
         * @param coeffs		vector to fill of coefficients for this row
         */
        void fillCoeffInLinearModelRow(unsigned long row, vector<LinearModel::Coefficient> *coeffs) override;

        /**
         * fills mode and right hand side of this constraint for linear model
         * @param row			identity number of this row
         * @param mode			mode to fill (valid are: 'N', 'L', 'G', 'E': like in MPS; or '+': maximize, or '-': minimize)
         * @param rhs			right hand side to fill
         */
        void fillModeRhsInLinearModel(unsigned long row, char *mode, LinearModel::Coefficient *rhs) override;
    };


    /**
     * formula of values connected by logical operations
     */
    class ValFormulaLogCon : public ValFormula
    {
    protected:
        bool _logNeg;                       ///< logical negation of the whole expression
        bool _logOr;                        ///< true: connection by logical Or / false: connection by logical And
        vector<CmplVal> _formulas;			///< connected formulas

    public:
        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaLogCon(ValFormulaLogCon *f): ValFormula(f->syntaxElem()), _logNeg(f->_logNeg), _logOr(f->_logOr), _formulas(f->_formulas)		{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param neg       logical negation
         * @param logOr		true: connect formula by logical Or / false: by logical And
         */
        inline ValFormulaLogCon(unsigned se, bool neg, bool logOr): ValFormula(se), _logNeg(neg), _logOr(logOr), _formulas()         { }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param neg       logical negation
         * @param f			source formula
         */
        inline ValFormulaLogCon(unsigned se, bool neg, ValFormula *f): ValFormula(se), _logNeg(neg), _logOr(false), _formulas()		{ _formulas.push_back(CmplVal(TP_FORMULA, f, true)); }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f1		first source formula
         * @param f2		second source formula
         * @param logOr		true: connect formula by logical Or / false: by logical And
         */
        inline ValFormulaLogCon(unsigned se, ValFormula *f1, ValFormula *f2, bool logOr): ValFormula(se), _logNeg(false), _logOr(logOr), _formulas()		{ _formulas.push_back(CmplVal(TP_FORMULA, f1, true)); _formulas.push_back(CmplVal(TP_FORMULA, f2, true)); }

        /**
         * destructor
         */
        virtual ~ValFormulaLogCon()                 { for (unsigned i = 0; i < _formulas.size(); i++) { _formulas[i].dispose(); } }

        /**
         * get whether logical negation of the whole expression
         */
        inline bool logNeg()                        { return _logNeg; }

        /**
         * get whether connection by logical Or or by logical And
         */
        inline bool logOr()                         { return _logOr; }

        /**
         * get connected formulas
         */
        inline vector<CmplVal>& formulas()          { return _formulas; }

        /**
         * get whether this formula is suitable for optimization row (linear or non-linear)
         * @param obj			true: as objective / false: as constraint
         * @return
         */
        bool canOptRow(bool obj) const override		{ return !obj; }

        /**
         * get whether this formula is an expression with boolean value
         */
        bool isBool() const override                { return true; }

        /**
         * return whether this formula can be expressed by a single binary variable (only implemented for formulas with isBool() == true)
         * @param neg           return if the binary variable negated
         * @return              binary variable / NULL: other formula
         */
        OptVar* asSingleBin(bool& neg) override;

        /**
         * get count of direct parts of the formula
         */
        unsigned partCount() const override         { return _formulas.size(); }

        /**
         * get direct part
         * @param i     number of part
         * @return
         */
        CmplVal *getPart(unsigned i) override       { return (i < _formulas.size() ? &(_formulas[i]) : NULL); }
    };

}

#endif // VALFORMULA_HH

