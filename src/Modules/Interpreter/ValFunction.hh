
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


#ifndef VALFUNCTION_HH
#define VALFUNCTION_HH

#include <math.h>

#include "../../CommonData/CmplVal.hh"
#include "../../Control/ThreadHandler.hh"
#include "ExecContext.hh"



using namespace std;



namespace cmpl
{
	class ExecContext;


    /**
	 * the <code>ValFunctionBase</code> is the base class for cmpl values
	 * with a function-like behaviour.
	 */
	class ValFunctionBase : public CmplObjBase
	{
    public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true if this has handled the operation
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg)				{ return false; }

		/**
		 * calls the cmpl index operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true if this has handled the operation
		 */
		virtual bool operIndex(ExecContext *ctx, StackValue *arg)				{ return false; }


        /****** utility functions, only used for internal cmpl functions or types ****/
    protected:
        /**
         * get name of the function
         */
        virtual const char *funcName() const                                    { return NULL; }

        /**
         * calls the function for a simple source value (no array or list)
         * @param ctx			execution context
         * @param res			store for result value
         * @param src			source value
         * @param se			syntax element id of source value
         */
        virtual void operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, unsigned se)      { }

    private:
        /**
         * recursive call for aggregating the elements of an array or a list
         * @param ctx			execution context
         * @param res           return of result value
         * @param arg			pointer to argument value
         */
        void callForArrayAggrRek(ExecContext *ctx, CmplVal &res, StackValue *arg);

    protected:
        /**
         * calls function for aggregating the elements of an array or a list (result is a simple value, even if src is an array)
         * @param ctx			execution context
         * @param res           return of result value
         * @param arg			pointer to argument value
         */
        void callForArrayAggr(ExecContext *ctx, CmplVal &res, StackValue *arg)            { res.set(TP_NULL); callForArrayAggrRek(ctx, res, arg); }

        /**
         * calls function for every single element of an array or a list (result is array over the same definition set as argument value)
         * @param ctx			execution context
         * @param res           return of result value
         * @param arg			pointer to argument value
         */
        void callForArrayElements(ExecContext *ctx, CmplVal &res, StackValue *arg);
    };


	/**
	 * base class for internal and for user defined functions in cmpl
	 */
	class ValFunction : public ValFunctionBase
	{
	protected:
		virtual bool userDef() const = 0;					///< function is an user defined function (written as cmpl code)

	public:
		/**
		 * write contents of the object to a stream
		 * @param modp			calling module
		 * @param mode			mode for output: 0=direct; 1=part of other value
		 */
		virtual void write(ostream& ostr, ModuleBase *modp, int mode = 0) const     { ostr << "<function object>"; }

        /**
         * get whether function has special meaning for optimization direction
         * @return				0:no / 1:max / -1:min
         */
        virtual int optDir() const													{ return 0; }
	};


    /**
	 * the <code>ValFunctionIntern</code> class is for a cmpl value
	 * that represents an user defined function.
	 */
	class ValFunctionUser : public ValFunction
	{
    private:
        unsigned _startPos;                                 ///< start position of function within the intermediary code

        //TODO: Subsymbolalias-Tabelle

    public:
        /**
         * constructor
         * @param startPos      start position within the intermediary code
         */
        ValFunctionUser(unsigned startPos): _startPos(startPos)         { }

        /**
         * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
         * @param ctx			execution context
         * @param arg			pointer to argument value
         * @return				true if this has handled the operation
         */
        virtual bool operCall(ExecContext *ctx, StackValue *arg);

    protected:
		virtual bool userDef() const	{ return true; }	///< function is an user defined function (written as cmpl code)

	public:
		/**
		 * write contents of the object to a stream
		 * @param modp			calling module
		 * @param mode			mode for output: 0=direct; 1=part of other value
		 */
		virtual void write(ostream& ostr, ModuleBase *modp, int mode = 0) const     { ostr << "<user defined function>"; }	//TODO: Hier auch Syntaxelement mit rein, das die Funktion darstellt
	};


    /**
	 * the <code>ValFunctionInternal</code> class is the base class for the internal cmpl functions
	 */
	class ValFunctionInternal : public ValFunction
	{
	protected:
		virtual bool userDef() const	{ return false; }	///< function is an user defined function (written as cmpl code)


    public:
		/**
		 * write contents of the object to a stream
		 * @param modp			calling module
		 * @param mode			mode for output: 0=direct; 1=part of other value
		 */
		virtual void write(ostream& ostr, ModuleBase *modp, int mode = 0) const     { ostr << "<predefined function '" << funcName() << "'>"; }
	};


	/****** aggregat functions ****/

    /**
	 * base class for internal cmpl functions for aggregating an array of values
	 */
	class ValFunctionAggregat : public ValFunctionInternal
	{
    public:
        /**
         * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
         * @param ctx			execution context
         * @param arg			pointer to argument value
         * @return				true
         */
        virtual bool operCall(ExecContext *ctx, StackValue *arg)                { callForArrayAggr(ctx, ctx->opResult(), arg); return true; }
    };

    /**
	 * internal function "sum"
	 */
	class ValFunctionInternSum : public ValFunctionAggregat
	{
	protected:
		virtual const char *funcName() const 		{ return "sum"; }			///< name of the internal function

	public:
        /**
         * calls the function for a simple source value (no array or list)
         * @param ctx			execution context
         * @param res			store for result value
         * @param src			source value
         * @param se			syntax element id of source value
         */
        virtual void operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, unsigned se);
	};

    /**
	 * internal function "max"
	 */
	class ValFunctionInternMax : public ValFunctionAggregat
	{
	protected:
		virtual const char *funcName() const 		{ return "max"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);

        /**
         * get whether function has special meaning for optimization direction
         * @return				0:no / 1:max / -1:min
         */
        virtual int optDir() const													{ return 1; }
    };

    /**
	 * internal function "min"
	 */
	class ValFunctionInternMin : public ValFunctionAggregat
	{
	protected:
		virtual const char *funcName() const 		{ return "min"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);

        /**
         * get whether function has special meaning for optimization direction
         * @return				0:no / 1:max / -1:min
         */
        virtual int optDir() const													{ return -1; }
    };

    /**
     * internal function "and"
     */
    class ValFunctionInternAnd : public ValFunctionAggregat
    {
    protected:
        virtual const char *funcName() const 		{ return "and"; }			///< name of the internal function

    public:
        /**
         * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
         * @param ctx			execution context
         * @param arg			pointer to argument value
         * @return				true
         */
        virtual bool operCall(ExecContext *ctx, StackValue *arg);
    };

    /**
     * internal function "or"
     */
    class ValFunctionInternOr : public ValFunctionAggregat
    {
    protected:
        virtual const char *funcName() const 		{ return "or"; }			///< name of the internal function

    public:
        /**
         * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
         * @param ctx			execution context
         * @param arg			pointer to argument value
         * @return				true
         */
        virtual bool operCall(ExecContext *ctx, StackValue *arg);
    };


	/****** array info functions ****/

    /**
	 * base class for internal cmpl functions for getting an info over an array of values
	 */
	class ValFunctionArrayInfo : public ValFunctionInternal
	{
	};

    /**
	 * internal function "count"
	 */
	class ValFunctionInternCount : public ValFunctionArrayInfo
	{
	protected:
		virtual const char *funcName() const 		{ return "count"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "def"
	 */
	class ValFunctionInternDef : public ValFunctionArrayInfo
	{
	protected:
		virtual const char *funcName() const 		{ return "def"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "valid"
	 */
	class ValFunctionInternValid : public ValFunctionArrayInfo
	{
	protected:
		virtual const char *funcName() const 		{ return "valid"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "dim"
	 */
	class ValFunctionInternDim : public ValFunctionArrayInfo
	{
	protected:
		virtual const char *funcName() const 		{ return "dim"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "defset"
	 */
	class ValFunctionInternDefset : public ValFunctionArrayInfo
	{
	protected:
		virtual const char *funcName() const 		{ return "defset"; }		///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "validset"
	 */
	class ValFunctionInternValidset : public ValFunctionArrayInfo
	{
	protected:
		virtual const char *funcName() const 		{ return "validset"; }		///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "len"
	 */
	class ValFunctionInternLen : public ValFunctionArrayInfo
	{
	protected:
		virtual const char *funcName() const 		{ return "len"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "rank"
	 */
	class ValFunctionInternRank : public ValFunctionArrayInfo
	{
	protected:
		virtual const char *funcName() const 		{ return "rank"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};


	/****** output functions ****/

    /**
	 * base class for internal cmpl functions for output of values
	 */
	class ValFunctionOutput : public ValFunctionInternal
	{
	};

    /**
	 * internal function "echo"
	 */
	class ValFunctionInternEcho : public ValFunctionOutput
	{
	protected:
		virtual const char *funcName() const 		{ return "echo"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
        virtual bool operCall(ExecContext *ctx, StackValue *arg)            { LockGlobalGuard(true, LockGlobalGuard::coutLock); callForArrayAggr(ctx, ctx->opResult(), arg); cout << endl; ctx->opResult().set(TP_NULL); return true; }

        /**
         * calls the function for a simple source value (no array or list)
         * @param ctx			execution context
         * @param res			store for result value
         * @param src			source value
         * @param se			syntax element id of source value
         */
        virtual void operCallSimple(ExecContext *ctx, CmplVal& res, CmplVal& src, unsigned se);

//    private:
//        /**
//         * simple array output
//         * @param ctx			execution context
//         * @param arr			array
//         */
//        void echoArraySimple(ExecContext *ctx, CmplArray *arr);
	};

    /**
	 * internal function "error"
	 */
	class ValFunctionInternError : public ValFunctionOutput
	{
	protected:
		virtual const char *funcName() const 		{ return "error"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "format"
	 */
	class ValFunctionInternFormat : public ValFunctionOutput
	{
	protected:
		virtual const char *funcName() const 		{ return "format"; }		///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};


	/****** integer division functions ****/

    /**
	 * base class for internal cmpl functions for division operation for integer numbers
	 */
	class ValFunctionDivInteger : public ValFunctionInternal
	{
    public:
        /**
         * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
         * @param ctx			execution context
         * @param arg			pointer to argument value
         * @return				true
         */
        virtual bool operCall(ExecContext *ctx, StackValue *arg);

        /**
         * executes the division operation for integer numbers
         * @param a1            first argument value
         * @param a2            second argument value
         * @return              result value
         */
        virtual intType execDiv(intType a1, intType a2) = 0;
    };

    /**
	 * internal function "div"
	 */
	class ValFunctionInternDiv : public ValFunctionDivInteger
	{
	protected:
		virtual const char *funcName() const 		{ return "div"; }			///< name of the internal function

	public:
        /**
         * executes the division operation for integer numbers
         * @param a1            first argument value
         * @param a2            second argument value
         * @return              result value
         */
        virtual intType execDiv(intType a1, intType a2)     { return a1 / a2; }
	};

    /**
	 * internal function "mod"
	 */
	class ValFunctionInternMod : public ValFunctionDivInteger
	{
	protected:
		virtual const char *funcName() const 		{ return "mod"; }			///< name of the internal function

	public:
        /**
         * executes the division operation for integer numbers
         * @param a1            first argument value
         * @param a2            second argument value
         * @return              result value
         */
        virtual intType execDiv(intType a1, intType a2)     { return a1 % a2; }
	};


	/****** random number functions ****/

    /**
	 * base class for internal cmpl functions for random number generation
	 */
	class ValFunctionGenerRand : public ValFunctionInternal
	{
	};

    /**
	 * internal function "srand"
	 */
	class ValFunctionInternSrand : public ValFunctionGenerRand
	{
	protected:
		virtual const char *funcName() const 		{ return "srand"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

    /**
	 * internal function "rand"
	 */
	class ValFunctionInternRand : public ValFunctionGenerRand
	{
	protected:
		virtual const char *funcName() const 		{ return "rand"; }			///< name of the internal function

	public:
		/**
		 * calls the cmpl function call operation and store result in execution context, if this value has a special handling for it
		 * @param ctx			execution context
		 * @param arg			pointer to argument value
		 * @return				true
		 */
		virtual bool operCall(ExecContext *ctx, StackValue *arg);
	};

}

#endif // VALFUNCTION_HH

