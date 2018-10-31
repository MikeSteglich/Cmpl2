
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


#ifndef LINEARCONSTANTROW_HH
#define LINEARCONSTANTROW_HH


#include "RemodelBase.hh"


using namespace std;



namespace cmpl
{
    class Interpreter;
    class OptModel;
    class OptCon;
    class CmplVal;
    class LinearConstantRowMod;


    /**
     * the <code>LinearConstantRow</code> class replace constant values
     * used as constraint or objective by a dummy matrix row
     */
    class LinearConstantRow : public RemodelBase
	{
    private:
        bool _delConstRow;          ///< don't replace by a dummy matrix row, but just remove a constant objective or fulfilled constraint
        bool _falseAsError;         ///< if a constant constraint is not fulfilled then output a warning or an error message (when together with _delConstRow)

        unsigned _attachNameVar;          ///< postfix used for generated optimization variables / 0: no name

	public:
        /**
         * constructor
         * @param mod			module creating this extension object
         */
        LinearConstantRow(LinearConstantRowMod *mod);



		/************** overwritten methods of <code>ExtensionBase</code> **********/

	public:
#if PROTO
        /**
         * get name of the extension, only used for protocol output
         */
        virtual const char *extName()				{ return "linearConstantRow"; }
#endif //PROTO

		/**
		 * write data object to output stream
		 * @param si        serialization info
		 * @param data      main data object
		 */
		virtual void serializeTo(MainData::SerializeInfo& si, const MainData *data);

		/**
		 * fill data object from input stream
		 * @param si        serialization info
		 * @param data      main data object
		 * @param subCnt    count of sub data objects
		 * @param lc		line count per element or 0 if elements are len coded
		 * @param rline		remaining section start line
		 */
		virtual void deserializeFrom(MainData::SerializeInfo& si, const MainData *data, int subCnt, int lc, string &rline);


        /************** linearization **********/
    protected:
        /**
         * remodel one constraint and objective
         * @param modp      intepreter module calling the extension
         * @param om		optimization model
         * @param oc        constraint and objective
         * @return          count of executed remodelations
         */
        virtual unsigned remodelCon(Interpreter *modp, OptModel *om, OptCon *oc);

        /**
         * linearize objective with constant value
         * @param modp      intepreter module calling the extension
         * @param om		optimization model
         * @param oc        matrix row
         * @param rv        constant number
         */
        void linearizeObj(Interpreter *modp, OptModel *om, OptCon *oc, CmplVal& rv);

        /**
         * linearize constraint with constant value of fulfilling
         * @param modp      intepreter module calling the extension
         * @param om		optimization model
         * @param oc        matrix row
         * @param cf        flag whether constraint is fulfilled
         */
        void linearizeCon(Interpreter *modp, OptModel *om, OptCon *oc, bool cf);

        /**
         * generate new optimization variable with constant value
         * @param modp      intepreter module calling the extension
         * @param om		optimization model
         * @param oc        matrix row
         * @param bound     lower and upper bound for optimization variable
         * @param res       value to store result formula of type ValFormulaVar
         */
        void newConstOptVar(Interpreter *modp, OptModel *om, OptCon *oc, CmplVal& bound, CmplVal& res);
    };

}

#endif // LINEARCONSTANTROW_HH

