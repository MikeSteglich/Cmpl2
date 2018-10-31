
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


#include "BoundRowMod.hh"
#include "BoundRow.hh"
#include "../../Control/MainControl.hh"


namespace cmpl
{
    /*********** module definition **********/

    // defines the module "boundRow" that is implemented in class "BoundRowMod".
    // to register this module you have to insert "MODULE_CLASS_REG(1, boundRow)" to file "modules.reg"
    MODULE_CLASS( boundRow, BoundRowMod )




    /*********** handling of command line options **********/

#define OPTION_EXT_DELALLBOUNDROW		70
#define OPTION_EXT_DELUNMBOUNDROW		71


    /**
     * initialize modul, to call immediately after the constructor.
     * @param ctrl			main object
     * @param data			data object
     * @param name			module name (or alias)
     */
    void BoundRowMod::init(MainControl *ctrl, MainData *data, const char *name)
    {
        RemodelBaseMod::init(ctrl, data, name);

        _delAllBoundRow = false;
        _delUnnamedBoundRow = true;
    }

    /**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
    void BoundRowMod::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
    {
        RemodelBaseMod::regModOptions(modOptReg);

        REG_CMDL_OPTION( OPTION_EXT_DELALLBOUNDROW, "del-bound-row", 0, 0, CMDL_OPTION_NEG_DELIV, true );
        REG_CMDL_OPTION( OPTION_EXT_DELUNMBOUNDROW, "del-unnamed-bound-row", 0, 0, CMDL_OPTION_NEG_DELIV, true );
    }

    /**
     * parse single option from command line options, this function is called for every delivered option
     * @param ref			reference number of option registration, should be used for discriminate the options
     * @param prio			priority value of option
     * @param opt			option
     * @return				true if option is used by the module
     */
    bool BoundRowMod::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
    {
        if (RemodelBaseMod::parseOption(ref, prio, opt))
            return true;

        switch (ref) {
            case OPTION_EXT_DELALLBOUNDROW:
                _delAllBoundRow = !opt->neg();
                return true;

            case OPTION_EXT_DELUNMBOUNDROW:
                _delUnnamedBoundRow = !opt->neg();
                return true;
        }

        return false;
    }

    /**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
    void BoundRowMod::usage(ostream& s)
    {
        RemodelBaseMod::usage(s);

        s << "  -del-bound-row                remove all rows which are replaced by bounds(default is " << (_delAllBoundRow ? "true" : "false") << ")" << endl;
        s << "  -del-unnamed-bound-row        remove only unnamed rows which are replaced by bounds(default is " << (_delUnnamedBoundRow ? "true" : "false") << ")" << endl;
    }


    /**
     * create derived class object for execution of the remodeling
     */
    RemodelBase *BoundRowMod::create(RemodelBaseMod *mod)
    {
        return new BoundRow((BoundRowMod *)mod);
    }
}


