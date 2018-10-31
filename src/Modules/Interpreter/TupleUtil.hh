
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


#ifndef TUPLEUTIL_HH
#define TUPLEUTIL_HH

#include <vector>

#include "../../CommonData/CmplVal.hh"
#include "../../CommonData/Tuple.hh"


using namespace std;



namespace cmpl
{
	class ExecContext;
	class StackValue;
    class CBAssignInfoComplex;
    class CBAssignInfoBasis;


	/**
	 * class for static utility functions for tuples
	 */
	class TupleUtil
	{
		/****** tuple construction ****/
	public:
		/**
		 * construct a tuple from stack values
		 * @param ctx			execution context
		 * @param res			store for result tuple
         * @param resPush       return whether res is to push to the stack
		 * @param cnt			count of components for tuple on stack
         * @param listTuple		if tuple is an index tuple than keep it on the stack as TP_LIST_TUPLE
		 * @param top			topmost component for tuple on stack / NULL: if cnt==0
		 * @return				stack element to pop to before pushing result tuple / NULL: no element to pop
		 */
        static StackValue *construct(ExecContext *ctx, CmplVal &res, bool &resPush, unsigned cnt, bool listTuple, StackValue *top);

		/**
		 * construct an index tuple from a TP_LIST_TUPLE value on the stack
		 * @param ctx			execution context
		 * @param res			store for result tuple
		 * @param lst			TP_LIST_TUPLE value on stack
		 */
		static void constructFromList(ExecContext *ctx, CmplVal &res, StackValue *lst);

        /**
         * convert tuple src to index tuple or to tuple set
         * @param ctx			execution context
         * @param res			store for result tuple or set
         * @param src			value to convert
         * @param listTuple		accept tuple as list
         */
        static void toIndexTuple(ExecContext *ctx, CmplVal &res, StackValue *src, bool listTuple);

        /**
         * convert tuple tpl to index tuple or to tuple set
         * @param ctx			execution context
         * @param res			store for result tuple or set
         * @param tpl			tuple to convert
         * @return              true if conversion is successful
         */
        static bool toIndexTuple(ExecContext *ctx, CmplVal &res, Tuple *tpl);


        /**
         * convert tuple or value to its canonical tuple form
         * @param ctx			execution context
         * @param res           store for result tuple
         * @param src           source tuple or value
         */
        static void canonicalTuple(ExecContext *ctx, CmplVal& res, CmplVal& src);

        /**
         * check if the tuple only contains simple index values, sets, or elements with type TP_DEF_CB_SYM (for other elements converting in set is tried)
         * @param ctx			execution context
         * @param res           store for result tuple
         * @param src           source tuple
         * @return              true if tuple only contains simple index values, sets, or elements with type TP_DEF_CB_SYM
         */
        static bool asTupleIndexOrSet(ExecContext *ctx, CmplVal& res, CmplVal& src);

        /**
         * try to match first tuple with a second tuple
         * @param ctx			execution context
         * @param se			syntax element id of operation
         * @param t1            first tuple (can contain TP_DEF_CB_SYM, which can match with any part of the second tuple, also with no part or more than one part)
         * @param t2            second tuple
         * @param ait           if given then for every part of the first tuple is registered in this array how many parts of the second tuple it is assigned in the matching result
         * @return              true if the tuples match
         */
        static bool matchTuple(ExecContext *ctx, unsigned se, CmplVal& t1, CmplVal& t2, unsigned *ait);

    private:
        /**
         * try to match range in first tuple with a range in second tuple
         * @param ctx			execution context
         * @param se			syntax element id of operation
         * @param t1            first tuple (can contain TP_DEF_CB_SYM, which can match with any part of the second tuple, also with no part or more than one part)
         * @param t2            second tuple
         * @param ait           if given then for every part of the first tuple is registered in this array how many parts of the second tuple it is assigned in the matching result
         * @param t1f           considered range in tuple t1 from
         * @param t1t           considered range in tuple t1 to
         * @param t2f           considered range in tuple t2 from
         * @param t2t           considered range in tuple t2 to
         * @return              true if considered range of the tuples match
         */
        static bool matchTupleRec(ExecContext *ctx, unsigned se, Tuple *t1, Tuple *t2, unsigned *ait, unsigned t1f, unsigned t1t, unsigned t2f, unsigned t2t);

        /**
         * inserts match info for tuple parts, with default assignment
         * @param ait           array for registering how many parts of the second tuple are assigned to a part of the first tuple in the matching result
         * @param tf            considered range of the first tuple from
         * @param tt            considered range of the first tuple to
         * @param rrank         remaining rank of second tuple to assign here
         */
        static void setTupleMatchCountDefault(unsigned *ait, unsigned tf, unsigned tt, unsigned rrank);
    };


    /**
     * utility class for matching tupels against a set, for executing a function as described in <code>TupleMatching::Mode</code>
     */
    class TupleMatching
    {
    public:
        enum Mode {
            matchIn,            ///< matching for operator "in" as boolean operator (_set is right operand and _tpl is left operand in this operation)
            matchIter,          ///< matching for operator "in" as iteration operator (_set is right operand and _tpl is left operand in this operation)
            matchReduce,		///< matching for operator "*>" (_set is left operand and _tpl is right operand in this operation)
            matchIndex,         ///< matching for indexation (_set is definition set of the array and _tpl is the indexing tuple in this operation)
        };

    private:
        // source values
        ExecContext *_ctx;          ///< execution context
        Mode _mode;                 ///< matching mode
        CmplVal _set;				///< source tuple set (must be a finite set, save for _mode == matchIn)
        CmplVal _tpl;				///< tuple to match against <code>_set</code> (must contain only simple index values, sets, or elements with type TP_DEF_CB_SYM (which can match with any part of a tuple from the source tuple set, also with no part or more than one part))
        bool _useOrder;				///< use user order

        // result values
        CBAssignInfoComplex *_assInfo;		///< only for _mode == matchIter: assign info of codeblock symbols for match tuples
        vector<unsigned long> *_resIndex;	///< only for _mode == matchIndex: indexes of matched tupels within _set

        // temporary values used in match()
        vector<unsigned> _freePos;	///< positions of elements marked as free within <code>_tpl</code>
        unsigned *_minRank;			///< array with minimal rank of elements within <code>_tpl</code>
        unsigned *_maxRank;			///< array with maximal rank of elements within <code>_tpl</code>

        bool _oneRank;				///< true if _minRank == _maxRank for all its entries
        bool _indexTuple;			///< <code>_tpl</code> is index tuple (doesn't contain any set)
        bool _infTpl;				///< <code>_tpl</code> contains an infinite set
        unsigned long _tplCnt;		///< count of tupel elements in <code>_tpl</code> (only if !_infSet)
        unsigned _tplRank;			///< rank of tuple <code>_tpl</code>

        unsigned _minRankSum;		///< sum over <code>_minRank</code>
        unsigned _maxRankSum;		///< sum over <code>_maxRank</code>
        unsigned _firstDiffRank;	///< index of first element within <code>_tpl</code> with minimal rank unequal to maximal rank
        unsigned _afterDiffRank;	///< index after last element within <code>_tpl</code> with minimal rank unequal to maximal rank

    public:
        /**
         * constructor
         * @param mode          matching mode
         * @param set           source tuple set (must be a finite set, save for mode == matchIn)
         * @param tpl           tuple to match against <code>set</code>
         * @param uo            use user order
         */
        TupleMatching(ExecContext *ctx, Mode mode, CmplVal& set, CmplVal& tpl, bool uo): _ctx(ctx), _mode(mode), _set(set), _tpl(tpl), _useOrder(uo),
                    _assInfo(NULL), _resIndex(NULL)		{ }

        /**
         * destructor
         */
        ~TupleMatching()                                { _set.dispose(); _tpl.dispose(); releaseResult(); }

        /**
         * try to match the tuple with the elements of the tuple set and make a result set of all matching tuples
         * @param res           store for result set
         * @return              true if any matching tuples, then result set is filled
         */
        bool match(CmplVal& res);

        /**
         * take assign info result of tuple matching for iteration
         * @return              assign info object for codeblock symbols in iteration
         */
        CBAssignInfoBasis *takeAssignInfo();

    private:
        /**
         * release result values
         */
        void releaseResult();

        /**
         * prepare <code>_tpl</code> for matching, and fills temporary instance variables
         */
        void prepareTuple();

        /**
         * matches single index tuple against <code>_tpl</code>
         * @param it            index tuple
         * @param am            return of matching rank per element in <code>_tpl</code>
         * @return              true if successfully matched
         */
        bool singleMatch(const CmplVal& it, unsigned *am);

        /**
         * try to match range in first tuple with a range in second tuple
         * @param t1            first tuple (can contain sets and index values)
         * @param t2            second tuple (contains only index values)
         * @param am            for every part of the first tuple is registered in this array how many parts of the second tuple it is assigned in the matching result
         * @param t1f           considered range in tuple t1 from
         * @param t1t           considered range in tuple t1 to
         * @param t2f           considered range in tuple t2 from
         * @param t2t           considered range in tuple t2 to
         * @return              true if considered range of the tuples match
         */
        bool singleMatchRec(Tuple *t1, Tuple *t2, unsigned *am, unsigned t1f, unsigned t1t, unsigned t2f, unsigned t2t);

        /**
         * try to match part of iteration tuple
         * @param set           set or simple index value to match tuple part against
         * @param mr            minimal rank of <code>set</code>
         * @param itpl          iteration tuple
         * @param rf            first element number of regarding part of the iteration tuple
         * @param rc            count of elements in regarding part of the iteration tuple
         * @return              true if iteration tuple part matches
         */
        bool matchPart(CmplVal *set, unsigned mr, Tuple *itpl, unsigned rf, unsigned rc);

        /**
         * reduce given tuple according to positions in <code>_freePos</code>, then add it to result set
         * @param res           result set
         * @param tpl           source tuple
         * @param ranks         rank per element in match tuple <code>_tpl</code>
         * @param uo            add to result set with user order
         * @param srcInd        index of tuple in source set
         * @return              true if tuple is added to result set / false if tuple was already in result set
         */
        bool reduceAddTuple(CmplVal& res, const CmplVal& tpl, unsigned *ranks, bool uo, unsigned long srcInd);
    };


    /**
     * exception thrown in <code>TupleMatching</code> if a source value is invalid
     */
    class TupleMatchingValueException : public runtime_error
    {
    private:
        int _invSet;            ///< true: set is invalid / false: tuple is invalid

    public:
        /**
         * constructor
         * @param txt       error message
         * @param invSet    true: set is invalid / false: tuple is invalid
         */
        TupleMatchingValueException(const string& txt, bool invSet) noexcept : runtime_error(txt), _invSet(invSet)      { }

        /**
         * get whether set or tuple is invalid
         */
        int invSet() const noexcept                 { return _invSet; }
    };

}

#endif // TUPLEUTIL_HH

