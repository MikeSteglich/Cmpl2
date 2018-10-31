
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


#include "LinearVarProdMod.hh"
#include "LinearVarProd.hh"
#include "../../Control/MainControl.hh"


namespace cmpl
{
    /*********** module definition **********/

    // defines the module "linearVarProd" that is implemented in class "LinearVarProdMod".
    // to register this module you have to insert "MODULE_CLASS_REG(1, linearVarProd)" to file "modules.reg"
    MODULE_CLASS( linearVarProd, LinearVarProdMod )



    /*********** handling of command line options **********/

#define OPTION_EXT_USEBIGMBOUND             70

#define OPTION_EXT_PRODREALERR              80
#define OPTION_EXT_PRODREALWARN             81
#define OPTION_EXT_PRODREALWARNONCE         82

#define OPTION_EXT_ATTACHNAMEVARDECOMP      90
#define OPTION_EXT_ATTACHNAMEVARNORM        91


    /**
     * initialize modul, to call immediately after the constructor.
     * @param ctrl			main object
     * @param data			data object
     * @param name			module name (or alias)
     */
    void LinearVarProdMod::init(MainControl *ctrl, MainData *data, const char *name)
    {
        RemodelBaseMod::init(ctrl, data, name);

        _useBigMBound = true;

        _prodRealErr = false;
        _prodRealWarn = true;
        _warnOnlyOnceProdReal = true;

        _attachNameVarDecomp = data->globStrings()->storeInd("b");
        _attachNameVarNorm = data->globStrings()->storeInd("n");
    }

    /**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
    void LinearVarProdMod::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
    {
        RemodelBaseMod::regModOptions(modOptReg);

        REG_CMDL_OPTION( OPTION_EXT_USEBIGMBOUND, "bigM-bound", 0, 0, CMDL_OPTION_NEG_NO_ARG, true );

        REG_CMDL_OPTION( OPTION_EXT_PRODREALERR, "real-prod-error", 0, 0, CMDL_OPTION_NEG_NO_ARG, true );
        REG_CMDL_OPTION( OPTION_EXT_PRODREALWARN, "real-prod-warning", 0, 0, CMDL_OPTION_NEG_NO_ARG, true );
        REG_CMDL_OPTION( OPTION_EXT_PRODREALWARNONCE, "real-prod-warn-once", 0, 0, CMDL_OPTION_NEG_NO_ARG, true );

        REG_CMDL_OPTION( OPTION_EXT_ATTACHNAMEVARDECOMP, "an-var-bin-decomp", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );
        REG_CMDL_OPTION( OPTION_EXT_ATTACHNAMEVARNORM, "an-var-norm-real", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );
    }

    /**
     * parse single option from command line options, this function is called for every delivered option
     * @param ref			reference number of option registration, should be used for discriminate the options
     * @param prio			priority value of option
     * @param opt			option
     * @return				true if option is used by the module
     */
    bool LinearVarProdMod::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
    {
        if (RemodelBaseMod::parseOption(ref, prio, opt))
            return true;

        switch (ref) {
            case OPTION_EXT_USEBIGMBOUND:
                _useBigMBound = !(opt->neg());
                return true;

            case OPTION_EXT_PRODREALERR:
                _prodRealErr = !(opt->neg());
                return true;

            case OPTION_EXT_PRODREALWARN:
                _prodRealWarn = !(opt->neg());
                return true;

            case OPTION_EXT_PRODREALWARNONCE:
                _warnOnlyOnceProdReal = !(opt->neg());
                return true;

            case OPTION_EXT_ATTACHNAMEVARDECOMP:
                _attachNameVarDecomp = parseOptString(opt);
                return true;

            case OPTION_EXT_ATTACHNAMEVARNORM:
                _attachNameVarNorm = parseOptString(opt);
                return true;
        }

        return false;
    }

    /**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
    void LinearVarProdMod::usage(ostream& s)
    {
        RemodelBaseMod::usage(s);

        s << "  -bigM-bound                   allow variables without bounds in products using big-M as replacement bound (default is " << (_useBigMBound ? "true" : "false") << ")" << endl;

        s << "  -real-prod-error              don't approximate product of real variables but throw an error (default is " << (_prodRealErr ? "true" : "false") << ")" << endl;
        s << "  -real-prod-warning            show warning if approximating a product of real variables (default is " << (_prodRealWarn ? "true" : "false") << ")" << endl;
        s << "  -real-prod-warn-once          show only one warning for products of real variables (default is " << (_warnOnlyOnceProdReal ? "true" : "false") << ")" << endl;

        s << "  -an-var-bin-decomp <string>   string attached to name for binary variable name for decomposition of an integer variable (default is '" << data()->globStrings()->at(_attachNameVarDecomp) << "')" << endl;
        s << "  -an-var-norm-real <string>    string attached to name for variable name for normalization of a real variable (default is '" << data()->globStrings()->at(_attachNameVarNorm) << "')" << endl;
    }


    /**
     * create derived class object for execution of the remodeling
     */
    RemodelBase *LinearVarProdMod::create(RemodelBaseMod *mod)
    {
        return new LinearVarProd((LinearVarProdMod *)mod);
    }
}


