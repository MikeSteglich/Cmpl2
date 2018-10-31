
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


#ifndef STACKVALUE_HH
#define STACKVALUE_HH

#include "../../CommonData/CmplVal.hh"
#include "ValueStore.hh"



using namespace std;



namespace cmpl
{
	class ExecContext;


	/**
	 * the <code>StackValue</code> is used as the representation of a cmpl value on the computation stack.
	 */
	class StackValue
	{
		friend class ExecContext;

	private:
		CmplVal _val;				///< value (can be also TP_SYMBOL_VAL, TP_ARRAY, TP_LIST_* or TP_REF_LIST)

        CmplVal _addVal;			///< additional value (if _val is TP_SYMBOL_VAL, it can be a set to apply at the value as indexation; if _val is a list, it contains the total count of stack values for the list; else it can be a superordinate container value if _val results from a subsymbol fetch)
		bool _transpose;			///< value array is treated as transposed

		unsigned _syntaxElem;		///< id of syntax element in the cmpl text creating this stack value


	public:
		/**
		 * get value
		 */
		inline CmplVal& val()								{ return _val; }

        /**
         * get id of syntax element in the cmpl text creating this stack value
         */
        inline unsigned syntaxElem() const					{ return _syntaxElem; }

        /**
		 * set value to empty or null
		 */
		inline void unsetValue(bool empty = true)			{ _val.dispose(); _addVal.dispose(); _val.set(empty ? TP_EMPTY : TP_NULL); _transpose = false; }

		/**
		 * initialize a stack value
		 * @param se		id of syntax element in the cmpl text creating this stack value
		 */
		inline void init(unsigned se = 0)					{ _val.unset(); _addVal.unset(); _transpose = false; _syntaxElem = se; }

		/**
		 * get pointer to simple value (no array or list) or NULL if values is an array or a list
		 * @return				pointer to value or NULL
		 */
        inline CmplVal *simpleValue()						{ return (isSimple() ? &_val : (_val.isArray() ? _val.array()->simpleValue() : (_val.t == TP_SYMBOL_VAL ? ((SymbolValue *)(_val.v.p))->simpleValue() : NULL))); }

		/**
		 * get whether this value is a simple value (no array or list)
		 */
        inline bool isSimple()								{ return (!_val.isSpecial() || _val.isCbhVal()); }

		/**
		 * get whether this value is a list of values
		 */
		inline bool isList()								{ return _val.isList(); }

		/**
		 * get whether this value is an lvalue
		 */
        inline bool lvalue()								{ return (_val.t == TP_SYMBOL_VAL || (_val.t == TP_SPECIALSYM && specialSymLval())); }

        /**
         * get whether TP_SPECIALSYM value can be an lvalue
         */
        bool specialSymLval();

		/**
		 * get whether this value is an lvalue with indexation
		 */
        inline bool hasIndex()								{ return (lvalue() && (_addVal.isSet() || _addVal.isITuple())); }

        /**
         * get whether value array is treated as transposed
         */
        inline bool isTransposed()							{ return _transpose; }

		/**
		 * check if this stack value is TP_STRINGP (only value direct in _val can be it) and change it then to TP_STR
		 * @param ctx			execution context
		 */
		void ifStringPChangeToStr(ExecContext *ctx);

        /**
         * perform indexation operation
         * @param ctx			execution context
         * @param ind			index value
         * @return				true: result stored in execution context / false: this changed to result
         */
        bool indexation(ExecContext *ctx, StackValue *ind);

    private:
        /**
         * perform indexation operation
         * @param ctx			execution context
         * @param ind			index value (must be index tuple or tuple set)
         * @param orgInd        original index value
         * @return				true: result stored in execution context / false: this changed to result
         */
        bool indexation(ExecContext *ctx, CmplVal& ind, StackValue *orgInd);

        /**
         * perform indexation operation on list, this must contain a list (not TP_REF_LIST)
         * @param ctx			execution context
         * @param ind			index value (must be index tuple or tuple set, and not TP_LIST_TUPLE)
         * @param orgInd        original index value
         * @return				true: result stored in execution context / false: this changed to result
         */
        bool indexationList(ExecContext *ctx, CmplVal& ind, StackValue *orgInd);

    public:
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
        void doAssign(ExecContext *ctx, char op, bool ref, bool cnst, bool init, bool ord, bool srn);

        /**
         * perform assignment with this (being a TP_SPECIALSYM value) as assign destination
         * @param ctx			execution context
         * @param op			assign operation (+,-,*,/) or '\0'
         * @param init          only initial assignment
         * @param ord			ordered assignment
         */
        void doAssignSpecial(ExecContext *ctx, char op, bool init, bool ord);

        /**
         * set data type as fixed for optimization variables
         */
        void fixDataTypeVar();

    private:
        /**
         * fill array to assign with scalar values
         * @param ctx			execution context
         * @param ds			definition set of the array
         * @param frhs			first value to fill in
         * @param se			syntax element id for result value
         * @param ord			ordered assignment
         * @return 				array on the stack
         */
        StackValue *fillAssignArray(ExecContext *ctx, CmplVal& ds, CmplVal *frhs, unsigned se, bool ord);

        /**
         * assign one scalar value within the array of an already defined symbol
         * @param ctx			execution context
         * @param sym			symbol to assign the value in
         * @param tpl			indexing tuple within the value array of the symbol / NULL: no index tuple
         * @param rhs			right hand side value
         * @param se            syntax element id of right hand side value
         * @param op			assign operation (+,-,*,/) or '\0'
         * @param srn			set row/col name for result matrix
         */
        void doAssignScalar(ExecContext *ctx, SymbolValue *sym, CmplVal *tpl, CmplVal *rhs, unsigned se, char op, bool srn);

        /**
         * check assertion for this
         * @param ctx			execution context
         * @param cnst			mark destination as const
         * @param dt            data type for assertion / NULL: no such assertion
         * @param ot            object type for assertion / NULL: no such assertion
         * @param se            syntax element id
         */
        void checkAssert(ExecContext *ctx, bool cnst, ValType *dt, intType ot, unsigned se);

        /**
         * import extern values to this
         * @param ctx			execution context
         * @param cnst			mark destination as const
         * @param se            syntax element id
         */
        void importExtern(ExecContext *ctx, bool cnst, unsigned se);

    public:
        /**
         * make iteration step over first index part of array or list in this
         * @param ctx           execution context
         * @param nprv          index value of iteration step / 0: start iteration
         * @param prev          previous iteration step result / NULL: not known or start iteration
         * @param nth           iterate to the element nprv + nth
         * @return              pointer to array or list part (existing element on stack or element new pushed on stack) / NULL: no such element or iteration ended
         */
        StackValue *iterArray(ExecContext *ctx, unsigned& iter, StackValue *prev = NULL, unsigned nth = 1);

		/**
		 * construct a list on the stack from stack values
		 * @param ctx			execution context
		 * @param res			store for resulting list header
         * @param cnt			count of components for list on stack
         * @param lst			topmost component for list on stack / NULL: if cnt==0
         * @return				stack element to pop to before pushing result list / NULL: no element to pop
		 */
		static StackValue *constructList(ExecContext *ctx, CmplVal &res, unsigned long cnt, StackValue *top);

		/**
		 * construct an array from a list on the stack
		 * @param ctx			execution context
		 * @param res			store for resulting array
		 * @param top			topmost component for tuple on stack, must be the list header
		 * @return				stack element to pop to before pushing result tuple
		 */
		static StackValue *arrayFromList(ExecContext *ctx, CmplVal &res, StackValue *lst);

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
		static unsigned long checkListRec(StackValue *lst, unsigned long& cnt, unsigned& rank, bool& hasNull, bool& allValid, bool& hasInvalid);

    private:
        /**
		 * construct an array from a hierachical list on the stack
		 * @param ctx			execution context
		 * @param dstp			pointer to current pointer to store array elements, decrement to next element
		 * @param defset		store for resulting definition set
		 * @param lst			topmost component for tuple on stack, must be the list header of a list
		 * @param rec			recursion counter
		 * @return				start element on the stack of the list
		 */
		static StackValue *arrayFromListRec(ExecContext *ctx, CmplVal **dstp, CmplVal &defset, StackValue *lst, unsigned rec);

    public:
        /**
         * convert compound Array (TP_ARRAY_COMP) to regular Array (TP_ARRAY)
         * @param ctx			execution context
         * @param src           source array (can contain TP_NULL and subarrays)
         * @return              src converted to regular array without other arrays as element / NULL: src is already a regular array
         */
        static CmplArray *arrayFromArrayComp(ExecContext *ctx, CmplArray *src);
    };

}

#endif // STACKVALUE_HH

