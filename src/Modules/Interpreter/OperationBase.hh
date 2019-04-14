
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


#ifndef VALFORMULABASE_HH
#define VALFORMULABASE_HH

#include <vector>
#include <map>

#include "../../CommonData/ValFormula.hh"
#include "ExecContext.hh"



using namespace std;



namespace cmpl
{
	/**
     * base class for execution of operations, especially when using formula values
	 */
    class OperationBase
	{
    private:
        /**
         * mode for matrix multiplication
         */
        enum MatrixMultMode {
            matrixMultNone,					///< no matrix multiplication
            matrixMultRowCol,				///< row [m] times column [m], results to a scalar
            matrixMultColRow,				///< column [m] times row [n], results to a matrix [n,m]
            matrixMultMtxCol,				///< matrix [m,n] times column [n], results to a column [m]
            matrixMultRowMtx,				///< row [m] times matrix [m,n], results to a row [n]
            matrixMultMtxMtx,				///< matrix [m,n] times matrix [n,o], results to a matrix [m,o]
        };


		/************** static utility functions **********/
	public:
		/**
		 * executes operation
		 * @param ctx			execution context
		 * @param res			store for result value
         * @param tp			mark result as transposed
         * @param se			syntax element id of operation
         * @param op			operation code (one of the minor codes for INTCODE_OPERATION)
         * @param cmpFollow		other compare operation follows immediately as continuation of this compare operation (only used for compare operation)
         * @param ac			count of arguments for the operation
		 * @param a1			argument one
		 * @param a2			argument two
		 * @return				true if operation is handled here
		 */
        static bool execOper(ExecContext *ctx, CmplVal& res, bool& tp, unsigned se, unsigned short op, bool cmpFollow, unsigned short ac, StackValue *a1 = NULL, StackValue *a2 = NULL);
		
		/**
		 * computes definition set of the result array of an operation
		 * @param ctx			execution context
         * @param res			store for result definition set
         * @param mm			return mode for matrix multiplication
         * @param se			syntax element id of operation
         * @param op			operation code (one of the minor codes for INTCODE_OPERATION)
		 * @param ac			count of arguments for the operation
		 * @param a1			argument one
		 * @param a2			argument two
         * @return				false if error
		 */
        static bool resultSet(ExecContext *ctx, CmplVal& res, MatrixMultMode &mm, unsigned se, unsigned short op, unsigned short ac, StackValue *a1 = NULL, StackValue *a2 = NULL);

        /**
         * get mode and result definition set for matrix multiplication
         * @param ctx			execution context
         * @param res			store for result definition set
         * @param se			syntax element id of operation
         * @param df1			definition set of argument one
         * @param df2			definition set of argument two
         * @param mm			return mode for matrix multiplication
         * @return				false if error
         */
        static bool resultSetMatrixMult(ExecContext *ctx, CmplVal& res, MatrixMultMode &mm, unsigned se, StackValue *a1, StackValue *a2, CmplVal& df1, CmplVal& df2);

        /**
         * executes unary operation (not for array)
         * @param ctx			execution context
         * @param res			store for result value
         * @param se			syntax element id of operation
         * @param op			operation code (one of the minor codes for INTCODE_OPERATION)
         * @param ac			count of arguments for the operation
         * @param a1			argument (must not be an array)
         */
        static void execUnaryOper(ExecContext *ctx, CmplVal *res, unsigned se, unsigned short op, CmplVal *a1);

        /**
         * executes binary operation (not for array)
         * @param ctx			execution context
         * @param res			store for result value
         * @param se			syntax element id of operation
         * @param op			operation code (one of the minor codes for INTCODE_OPERATION)
         * @param cmpFollow		other compare operation follows immediately as continuation of this compare operation (only used for compare operation)
         * @param ac			count of arguments for the operation
         * @param a1			argument one (must not be an array)
         * @param a2			argument two (must not be an array)
         */
        static void execBinaryOper(ExecContext *ctx, CmplVal *res, unsigned se, unsigned short op, bool cmpFollow, CmplVal *a1, CmplVal *a2);

        /**
         * executes matrix multiplication
         * @param ctx			execution context
         * @param res			result array store
         * @param mm			mode for matrix multiplication
         * @param se			syntax element id of operation
         * @param a1			argument one array
         * @param a2			argument two array
         */
        static void execMatrixMult(ExecContext *ctx, CmplVal *res, MatrixMultMode mm, unsigned se, CmplArray *a1, CmplArray *a2);

    protected:
        /**
         * get priority of calling the binary operation at this formula object
         * @param op			operation code (binary operation)
         * @param fa			this is the first argument of the operation
         * @param oa			other argument of the operation
         * @return				priority level to call execution of the operation at this instead of the other argument (at least 2), or 0 if the formula doesn't implement the operation
         */
        virtual unsigned formulaOperPrio(unsigned short op, bool fa, CmplVal *oa) = 0;


        /************** basic operations **********/

        // unary plus
        static void pos(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1);							///< unary plus of arbitrary value
        static void posN(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1) { res->copyFrom(a1); }	///< unary plus of number (a1 must be TP_INT, TP_REAL or TP_INFINITE)
        virtual void posF(ExecContext *ctx, CmplVal *res, unsigned se) { res->set(TP_FORMULA, dynamic_cast<ValFormula *>(this)); }		///< unary plus of formula

        // negation (unary minus)
        static void neg(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1);							///< negation of arbitrary value
        static void negN(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1);							///< negation of number (a1 must be TP_INT, TP_REAL or TP_INFINITE)
        virtual void negF(ExecContext *ctx, CmplVal *res, unsigned se) { }									///< negation of formula

        virtual void notF(ExecContext *ctx, CmplVal *res, unsigned se);                                     ///< logical Not for formula

        // binary operation plus
    public:
        static void plus(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);			///< addition of two arbitrary values
    protected:
        static void plusN(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);			///< addition of numbers (a1 and a2 must be TP_INT, TP_REAL or TP_INFINITE)
        virtual void plusF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2) { }					///< addition for formula

        // binary operation minus
        static void minus(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);			///< minus of two arbitrary values
        static void minusN(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);			///< minus of numbers (a1 and a2 must be TP_INT, TP_REAL or TP_INFINITE)
        virtual void minusF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool rev) { }			///< minus for formula

    public:
        static void addTo(ExecContext *ctx, CmplVal *dst, unsigned se, CmplVal *a2, bool neg = false);      ///< addition to a destination value

        // multiplication
    public:
        static void mult(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2, bool noReuseArg = false);	///< multiplication of two arbitrary values
        static void multN(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);			///< multiplication of numbers (a1 and a2 must be TP_INT, TP_REAL or TP_INFINITE)
    protected:
        virtual void multF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool noReuseArg = false) { }	///< multiplication for formula

    public:
        static void multTo(ExecContext *ctx, CmplVal *dst, unsigned se, CmplVal *a2);                       ///< multiplication to a destination value

        // division
    protected:
        static void div(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);             ///< division of two arbitrary values
    public:
        static void divN(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);			///< division of numbers (a1 and a2 must be TP_INT, TP_REAL or TP_INFINITE)
    protected:
        virtual void divF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool rev) { }           ///< division for formula

        // compare
        static void comp(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2, bool ge, bool le, bool neg, bool cont);	///< compare of two arbitrary values
        static void compN(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2, bool ge, bool le, bool neg);	///< compare of two values (a1 and a2 must not be or contain optimization variables)
        static void compNRec(ExecContext *ctx, unsigned se, CmplVal *a1, CmplVal *a2, bool eq, bool& bge, bool& ble);           ///< utility function for comparison of two values
        virtual void compF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool ge, bool le, bool neg);	///< compare for formula

    public:
        static bool compEq2(ExecContext *ctx, unsigned se, const CmplVal *a1, const CmplVal *a2);           ///< compare with "==" (or "!=") of two arbitrary values

    protected:
        // optimization objective
        static void objTo(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);			///< operation for optimization direction

        // logical operation
        static void logAndOr(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2, unsigned short op);    ///< logical And or Or
        virtual void logAndOrF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool logOr);       ///< logical And or Or for formula

    protected:
        // set operations
        static void tplInSet(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2, bool opIn);         ///< check whether tuple is in set
        static void tplMatch(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, CmplVal *a2);                    ///< tuple matching operation
        static void setMarkNF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a1, bool mnf);                         ///< mark set as non-free or free

        //TODO
    };



    /**
     * class for formula of single optimization variable with optional factor
     */
    class ValFormulaVarOp : public ValFormulaVar, public OperationBase
    {
    public:
        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaVarOp(ValFormulaVar *f): ValFormulaVar(f)					{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         */
        inline ValFormulaVarOp(unsigned se, OptVar *ov): ValFormulaVar(se, ov)		{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         * @param f			factor
         */
        inline ValFormulaVarOp(unsigned se, OptVar *ov, CmplVal& f): ValFormulaVar(se, ov, f)		{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         * @param r			factor
         */
        inline ValFormulaVarOp(unsigned se, OptVar *ov, realType r): ValFormulaVar(se, ov, r)		{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         * @param i			factor
         */
        inline ValFormulaVarOp(unsigned se, OptVar *ov, intType i): ValFormulaVar(se, ov, i)		{ }


        /************** operations **********/
    public:
        /**
         * get priority of calling the binary operation at this formula object
         * @param op			operation code (binary operation)
         * @param fa			this is the first argument of the operation
         * @param oa			other argument of the operation
         * @return				priority level to call execution of the operation at this instead of the other argument (at least 2), or 0 if the formula doesn't implement the operation
         */
        virtual unsigned formulaOperPrio(unsigned short op, bool fa, CmplVal *oa);

        virtual void negF(ExecContext *ctx, CmplVal *res, unsigned se);									///< negation of formula
        virtual void plusF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2);					///< addition for formula
        virtual void minusF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool rev);		///< minus for formula
        virtual void multF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool noReuseArg = false);	///< multiplication for formula

    };


    /**
     * class for formula of single optimization variable with optional factor
     */
    class ValFormulaVarProdOp : public ValFormulaVarProd, public OperationBase
    {
    public:
        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaVarProdOp(ValFormulaVarProd *f): ValFormulaVarProd(f)		{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f			formula for variable
         */
        inline ValFormulaVarProdOp(unsigned se, ValFormulaVar *f): ValFormulaVarProd(se, f)      	{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         */
        inline ValFormulaVarProdOp(unsigned se, OptVar *v1, OptVar *v2): ValFormulaVarProd(se)      { setNewVarProd(v1, v2, true); }

        /**
         * removes variables from product and replace by product of the two given variables
         * @param v1        first variable
         * @param v2        second variable
         * @param keepF     true: keep factor unchanged / false: remove factor
         */
        void setNewVarProd(OptVar *v1, OptVar *v2, bool keepF);

        /**
         * append variable product to terms of ValFormulaLinearComb
         * @param terms     terms of ValFormulaLinearComb
         * @param neg       negate term
         */
        void pushToLinearCombTerms(vector<CmplVal> &terms, bool neg = false);

        /************** operations **********/
    public:
        /**
         * get priority of calling the binary operation at this formula object
         * @param op			operation code (binary operation)
         * @param fa			this is the first argument of the operation
         * @param oa			other argument of the operation
         * @return				priority level to call execution of the operation at this instead of the other argument (at least 2), or 0 if the formula doesn't implement the operation
         */
        virtual unsigned formulaOperPrio(unsigned short op, bool fa, CmplVal *oa);

        virtual void negF(ExecContext *ctx, CmplVal *res, unsigned se);									///< negation of formula
        virtual void plusF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2);					///< addition for formula
        virtual void minusF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool rev);		///< minus for formula
        virtual void multF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool noReuseArg = false);	///< multiplication for formula

    };


    /**
	 * formula for linear combination of optimization variables
	 */
    class ValFormulaLinearCombOp : public ValFormulaLinearComb, public OperationBase
	{
    public:
        /**
         * empty constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         */
        inline ValFormulaLinearCombOp(unsigned se): ValFormulaLinearComb(se)                            { }

        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaLinearCombOp(ValFormulaLinearComb *f): ValFormulaLinearComb(f)                 { }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f			formula for variable
         */
        inline ValFormulaLinearCombOp(unsigned se, ValFormulaVar *f): ValFormulaLinearComb(se, f)		{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param ov		optimization variable
         */
        inline ValFormulaLinearCombOp(unsigned se, OptVar *ov): ValFormulaLinearComb(se, ov)			{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f			formula for product of variables
         */
        inline ValFormulaLinearCombOp(unsigned se, ValFormulaVarProdOp *f): ValFormulaLinearComb(se)    { _linear = false; f->pushToLinearCombTerms(_terms); }


        /************** operations **********/
    public:
        /**
         * get priority of calling the binary operation at this formula object
         * @param op			operation code (binary operation)
         * @param fa			this is the first argument of the operation
         * @param oa			other argument of the operation
         * @return				priority level to call execution of the operation at this instead of the other argument (at least 2), or 0 if the formula doesn't implement the operation
         */
        virtual unsigned formulaOperPrio(unsigned short op, bool fa, CmplVal *oa);

        virtual void negF(ExecContext *ctx, CmplVal *res, unsigned se);									///< negation of formula
        virtual void plusF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2);					///< addition for formula
        virtual void minusF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool rev);		///< minus for formula
        virtual void multF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool noReuseArg = false);	///< multiplication for formula

        /**
         * add or substract of formulas
         * @param ctx			execution context
         * @param res			store for result definition set
         * @param newres        true: fill res with new result object
         * @param se			syntax element id of operation
         * @param a2			argument two
         * @param minus			add or substract
         */
        void plusMinusF(ExecContext *ctx, CmplVal *res, bool newres, unsigned se, CmplVal *a2, bool minus);

        /**
         * multiplication with a number
         * @param ctx			execution context
         * @param res			store for result definition set
         * @param se			syntax element id of operation
         * @param a2			argument two (must be TP_INT, TP_REAL or TP_INFINITE)
         * @param noReuseArg    don't reuse argument even if it has only one reference
         */
        void multWithN(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool noReuseArg);

        /**
         * multiplication of the terms in this with optimization variables and appending resulting terms
         * @param ctx			execution context
         * @param se			syntax element id of operation
         * @param resTerms		append resulting terms to this vector
         * @param v2			optimization variable (must be TP_OPT_VAR or TP_FORMULA containing ValFormulaVar or ValFormulaVarProd)
         * @param f2            additional numeric factor (must be TP_INT or TP_REAL) or NULL if no such factor
         */
        void multTermsVarAdd(ExecContext *ctx, unsigned se, vector<CmplVal> &resTerms, CmplVal *v2, CmplVal *f2);

        /**
         * check whether formula is linear and set flag for it, change also terms from ValFormulaVar to TP_OPT_VAR
         * @param ctx			execution context
         */
        void checkLinear(ExecContext *ctx);
    };


    /**
	 * formula for compare operation
	 */
    class ValFormulaCompareOp : public ValFormulaCompare, public OperationBase
    {
	public:
        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaCompareOp(ValFormulaCompare *f): ValFormulaCompare(f)					{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f			source formula
         */
        inline ValFormulaCompareOp(unsigned se, ValFormulaCompare *f, bool ge, bool le, bool neg): ValFormulaCompare(se, f, ge, le, neg)                { }

        /**
         * constructor
         */
        inline ValFormulaCompareOp(unsigned se, CmplVal *ls, CmplVal *rs, bool ge, bool le, bool neg): ValFormulaCompare(se, ls, rs, ge, le, neg)		{ }

        /**
         * constructor
         */
        inline ValFormulaCompareOp(unsigned se, ValFormula *ls, CmplVal *rs, bool ge, bool le, bool neg): ValFormulaCompare(se, ls, rs, ge, le, neg)	{ }


        /************** operations **********/
    public:
        /**
         * logical Not for formula
         * @param ctx			execution context
         * @param res			store for result value
         * @param se			syntax element id of operation
         */
        virtual void notF(ExecContext *ctx, CmplVal *res, unsigned se);

        /**
         * get priority of calling the binary operation at this formula object
         * @param op			operation code (binary operation)
         * @param fa			this is the first argument of the operation
         * @param oa			other argument of the operation
         * @return				priority level to call execution of the operation at this instead of the other argument (at least 2), or 0 if the formula doesn't implement the operation
         */
        virtual unsigned formulaOperPrio(unsigned short op, bool fa, CmplVal *oa);
    };


    /**
     * formula for result of compare operation which is continued by another compare operation
     */
    class ValFormulaCompContinueOp : public ValFormula, public OperationBase
    {
    protected:
        CmplVal _cmpRes;					///< result of compare operation, can be TP_FORMULA or TP_BIN
        CmplVal _rightSide;					///< right side of compare; used as left side for the following compare operation

    public:
        /**
         * constructor
         */
        inline ValFormulaCompContinueOp(unsigned se, CmplVal *res, CmplVal *a2): ValFormula(se), _cmpRes(res), _rightSide(a2)		{ }

        /**
         * destructor
         */
        virtual inline ~ValFormulaCompContinueOp()						{ _cmpRes.dispose(); _rightSide.dispose(); }

        /**
         * write contents of the object to a stream
         * @param modp			calling module
         * @param mode			mode for output: 0=direct; 1=part of other value
         */
        virtual void write(ostream& ostr, ModuleBase *modp, int mode = 0) const     { ostr << "<f-cmp: (continue)>"; }


        /************** operations **********/

        /**
         * get priority of calling the binary operation at this formula object
         * @param op			operation code (binary operation)
         * @param fa			this is the first argument of the operation
         * @param oa			other argument of the operation
         * @return				priority level to call execution of the operation at this instead of the other argument (at least 2), or 0 if the formula doesn't implement the operation
         */
        virtual unsigned formulaOperPrio(unsigned short op, bool fa, CmplVal *oa);

        virtual void compF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool ge, bool le, bool neg);	///< compare for formula

        //TODO
    };


	/**
	 * formula with operation for optimization direction
	 */
    class ValFormulaObjectiveOp : public ValFormulaObjective, public OperationBase
	{
    public:
        /**
         * constructor
         */
        inline ValFormulaObjectiveOp(unsigned se, CmplVal *f, bool ma): ValFormulaObjective(se, f, ma)		{ }


        /************** operations **********/

        /**
         * get priority of calling the binary operation at this formula object
         * @param op			operation code (binary operation)
         * @param fa			this is the first argument of the operation
         * @param oa			other argument of the operation
         * @return				priority level to call execution of the operation at this instead of the other argument (at least 2), or 0 if the formula doesn't implement the operation
         */
        virtual unsigned formulaOperPrio(unsigned short op, bool fa, CmplVal *oa);

        //TODO
    };


    /**
     * formula of values connected by logical operations
     */
    class ValFormulaLogConOp : public ValFormulaLogCon, public OperationBase
    {
    public:
        /**
         * copy constructor
         * @param f			source formula
         */
        inline ValFormulaLogConOp(ValFormulaLogCon *f): ValFormulaLogCon(f)			{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param neg       logical negation
         * @param logOr		true: connect formula by logical Or / false: by logical And
         */
        inline ValFormulaLogConOp(unsigned se, bool neg, bool logOr): ValFormulaLogCon(se, neg, logOr)	{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param neg       logical negation
         * @param f			source formula
         */
        inline ValFormulaLogConOp(unsigned se, bool neg, ValFormula *f): ValFormulaLogCon(se, neg, f)	{ }

        /**
         * constructor
         * @param se        id of syntax element in the cmpl text creating this formula value
         * @param f1		first source formula
         * @param f2		second source formula
         * @param logOr		true: connect formula by logical Or / false: by logical And
         */
        inline ValFormulaLogConOp(unsigned se, ValFormula *f1, ValFormula *f2, bool logOr): ValFormulaLogCon(se, f1, f2, logOr)  { }


        /************** operations **********/
    public:
        /**
         * logical Not for formula
         * @param ctx			execution context
         * @param res			store for result value
         * @param se			syntax element id of operation
         */
        virtual void notF(ExecContext *ctx, CmplVal *res, unsigned se);

        /**
         * logical And or Or for formula
         * @param ctx			execution context
         * @param res			store for result value
         * @param se			syntax element id of operation
         * @param a2			argument two
         * @param logOr			logical Or or logical And
         */
        virtual void logAndOrF(ExecContext *ctx, CmplVal *res, unsigned se, CmplVal *a2, bool logOr);

        /**
         * get priority of calling the binary operation at this formula object
         * @param op			operation code (binary operation)
         * @param fa			this is the first argument of the operation
         * @param oa			other argument of the operation
         * @return				priority level to call execution of the operation at this instead of the other argument (at least 2), or 0 if the formula doesn't implement the operation
         */
        virtual unsigned formulaOperPrio(unsigned short op, bool fa, CmplVal *oa);
    };
}

#endif // VALFORMULABASE_HH

