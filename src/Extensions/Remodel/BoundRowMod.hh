
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


#ifndef BOUNDROWMOD_HH
#define BOUNDROWMOD_HH


#include "RemodelBaseMod.hh"


using namespace std;



namespace cmpl
{
	class BoundRow;

	
    /**
     * <code>BoundRowMod</code> is the extension Module for replacing
	 * matrix rows with only one variable by bounds
	 */
    class BoundRowMod : public RemodelBaseMod
	{
        friend class BoundRow;


        /************** command line options **********/

    private:
        bool _delAllBoundRow;           ///< remove all rows which are replaced by bounds
        bool _delUnnamedBoundRow;       ///< remove only unnamed rows which are replaced by bounds (only when !_delAllBoundRow)


        /************** overwritten methods of <code>ModuleBase</code> **********/

    protected:
        /**
         * initialize modul, to call immediately after the constructor.
         * @param ctrl			main object
         * @param data			data object
         * @param name			module name (or alias)
         */
        void init(MainControl *ctrl, MainData *data, const char *name) override;

        /**
         * register command line options options for delivery to this module
         * @param modOptReg		vector to register in
         */
        void regModOptions(vector<CmdLineOptList::RegOption> &modOptReg) override;

        /**
         * parse single option from command line options, this function is called for every delivered option
         * @param ref			reference number of option registration, should be used for discriminate the options
         * @param prio			priority value of option
         * @param opt			option
         * @return				true if option is used by the module
         */
        bool parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt) override;

        /**
         * writes usage info for the module to stream
         * @param s				stream to write to
         */
        void usage(ostream& s) override;



        /************** internal methods **********/

    protected:
        /**
         * create derived class object for execution of the remodeling
         */
        RemodelBase *create(RemodelBaseMod *mod) override;

        /**
         * flag whether _nameSep is used for remodeling
         */
        bool useNameSep() override                   { return false; }
    };
}

#endif // BOUNDROWMOD_HH

