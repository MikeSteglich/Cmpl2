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


#ifndef OUTMODELMATRIX_HH
#define OUTMODELMATRIX_HH

#include <string>
#include <iostream>

#include "../../Control/ModuleBase.hh"
#include "../../CommonData/OptModel.hh"
#include "../../CommonData/SyntaxElements.hh"


using namespace std;



namespace cmpl
{
	class OptModel;


    /**
     * <code>OutModelMatrix</code> is used to write the model generated by the Interpreter module to a file in the MPS format.
	 */
    class OutModelMatrix : public ModuleBase
	{

		/************** command line options **********/

	private:
        FileOutput *_outMatrix;				///< write model as standard MPS to this file / NULL: no standard MPS output
        bool _exportOnly;
        string _objName;



	public:
		/**
		 * destructor
		 */
        ~OutModelMatrix();


		/************** overwritten methods of <code>ModuleBase</code> **********/

	public:
		/**
		 * initialize modul, to call immediately after the constructor.
		 * @param ctrl			main object
		 * @param data			data object
		 * @param name			module name (or alias)
		 */
		virtual void init(MainControl *ctrl, MainData *data, const char *name);

		/**
		 * run module function
		 */
		virtual void run();



        /**
         * write generated model to stream
         * @param om			generated model
         * @param ostr			output to this stream
         */
        void writeMatrix(OptModel *om, ostream& ostr);

	protected:
		/**
		 * register command line options options for delivery to this module
		 * @param modOptReg		vector to register in
		 */
		virtual void regModOptions(vector<CmdLineOptList::RegOption> &modOptReg);

		/**
		 * parse single option from command line options, this function is called for every delivered option
		 * @param ref			reference number of option registration, should be used for discriminate the options
		 * @param prio			priority value of option
		 * @param opt			option
		 * @return				true if option is used by the module
		 */
		virtual bool parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt);

		/**
		 * writes usage info for the module to stream
		 * @param s				stream to write to
		 */
		virtual void usage(ostream& s);


		/************** module functionality **********/

	private:
		/**
         * write generated matrix to file
		 * @param om			generated model
		 * @param file			output to this file
         */
        void writeMatrix(OptModel *om, FileOutput *file);


        /**
         * write column coefficients for one column
         * @param ostr			output to this stream
         * @param fm			use free MPS format
         * @param cn			column name
         * @param rns			row names
         * @param coeffs		coefficients for the column
         */
        void writeColCoeffs(ostream& ostr, const vector<LinearModel::Coefficient> &coeffs, unsigned long colCnt);

        /**
         * write bounds for one column
         * @param ostr			output to this stream
         * @param fm			use free MPS format
         * @param cn			column name
         * @param bt			MPS type of bound
         * @param bv			value of bound or NULL if the bound type doesn't have one
         */
        string colBound(CmplVal& bv, string type);


    };
}

#endif // OUTMODELMATRIX_HH

