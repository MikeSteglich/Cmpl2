
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


#include "LinearLogConMod.hh"
#include "LinearLogCon.hh"
#include "../../Control/MainControl.hh"


namespace cmpl
{
    /*********** module definition **********/

    // defines the module "linearLogCon" that is implemented in class "LinearLogConMod".
    // to register this module you have to insert "MODULE_CLASS_REG(1, linearLogCon)" to file "modules.reg"
    MODULE_CLASS( linearLogCon, LinearLogConMod )




    /*********** handling of command line options **********/

#define OPTION_EXT_ATTACHNAMECONAND         80

#define OPTION_EXT_ATTACHNAMECONOR          82
#define OPTION_EXT_ATTACHNAMEVAROR          83

#define OPTION_EXT_ATTACHNAMECONDLTNEG      84
#define OPTION_EXT_ATTACHNAMEVARDLTNEG      85


    /**
     * initialize modul, to call immediately after the constructor.
     * @param ctrl			main object
     * @param data			data object
     * @param name			module name (or alias)
     */
    void LinearLogConMod::init(MainControl *ctrl, MainData *data, const char *name)
    {
        RemodelBaseMod::init(ctrl, data, name);

        _attachNameConAnd = data->globStrings()->storeInd("a");
        _attachNameConOr = data->globStrings()->storeInd("o");
        _attachNameVarOr = data->globStrings()->storeInd("b");
        _attachNameConDltNeg = data->globStrings()->storeInd("n");
        _attachNameVarDltNeg = data->globStrings()->storeInd("d");
    }

    /**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
    void LinearLogConMod::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
    {
        RemodelBaseMod::regModOptions(modOptReg);

        REG_CMDL_OPTION( OPTION_EXT_ATTACHNAMECONAND, "an-con-and", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );

        REG_CMDL_OPTION( OPTION_EXT_ATTACHNAMECONOR, "an-con-or", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );
        REG_CMDL_OPTION( OPTION_EXT_ATTACHNAMEVAROR, "an-var-or", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );

        REG_CMDL_OPTION( OPTION_EXT_ATTACHNAMECONDLTNEG, "an-con-neg", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );
        REG_CMDL_OPTION( OPTION_EXT_ATTACHNAMEVARDLTNEG, "an-var-neg", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );
    }

    /**
     * parse single option from command line options, this function is called for every delivered option
     * @param ref			reference number of option registration, should be used for discriminate the options
     * @param prio			priority value of option
     * @param opt			option
     * @return				true if option is used by the module
     */
    bool LinearLogConMod::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
    {
        if (RemodelBaseMod::parseOption(ref, prio, opt))
            return true;

        switch (ref) {
            case OPTION_EXT_ATTACHNAMECONAND:
                _attachNameConAnd = parseOptString(opt);
                return true;

            case OPTION_EXT_ATTACHNAMECONOR:
                _attachNameConOr = parseOptString(opt);
                return true;

            case OPTION_EXT_ATTACHNAMEVAROR:
                _attachNameVarOr = parseOptString(opt);
                return true;

            case OPTION_EXT_ATTACHNAMECONDLTNEG:
                _attachNameConDltNeg = parseOptString(opt);
                return true;

            case OPTION_EXT_ATTACHNAMEVARDLTNEG:
                _attachNameVarDltNeg = parseOptString(opt);
                return true;
        }

        return false;
    }

    /**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
    void LinearLogConMod::usage(ostream& s)
    {
        RemodelBaseMod::usage(s);

        s << "  -an-con-and <string>          string attached to name for part of constraint connected by logical And  (default is '" << data()->globStrings()->at(_attachNameConAnd) << "')" << endl;
        s << "  -an-con-or <string>           string attached to name for part of constraint connected by logical Or  (default is '" << data()->globStrings()->at(_attachNameConOr) << "')" << endl;
        s << "  -an-var-or <string>           string attached to name for variable for linearization of logical Or  (default is '" << data()->globStrings()->at(_attachNameVarOr) << "')" << endl;
        s << "  -an-con-neg <string>          string attached to name for constraint for linearization of logical negation (default is '" << data()->globStrings()->at(_attachNameConDltNeg) << "')" << endl;
        s << "  -an-var-neg <string>          string attached to name for variable for linearization of logical negation (default is '" << data()->globStrings()->at(_attachNameVarDltNeg) << "')" << endl;
    }


    /**
     * create derived class object for execution of the remodeling
     */
    RemodelBase *LinearLogConMod::create(RemodelBaseMod *mod)
    {
        return new LinearLogCon((LinearLogConMod *)mod);
    }
}


