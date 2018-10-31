
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


#include "RemodelBaseMod.hh"
#include "RemodelBase.hh"
#include "../../Control/MainControl.hh"


namespace cmpl
{
    /**
     * run module function
     */
    void RemodelBaseMod::run()
    {
        PROTO_OUTL("Start run module " << moduleName());

        // register for module "interpret"
        RemodelBase *ext = create(this);
        _ctrl->registerExtension((_registerMods.size() > 0 ? _registerMods[0].c_str() : "interpret"), EXT_STEP_INTERPRET_REMODEL, ext);

        PROTO_OUTL("End run module " << moduleName());
    }


    /*********** handling of command line options **********/

#define OPTION_EXT_THREADS          20
#define OPTION_EXT_REMODEL_BIGM     21
#define OPTION_EXT_NAMESEP          30


    /**
     * initialize modul, to call immediately after the constructor.
     * @param ctrl			main object
     * @param data			data object
     * @param name			module name (or alias)
     */
    void RemodelBaseMod::init(MainControl *ctrl, MainData *data, const char *name)
    {
        ExtensionModule::init(ctrl, data, name);

        _maxThreads = 0;
        _bigM = 1e+10;
        _nameSep = data->globStrings()->storeInd("_");
    }

    /**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
    void RemodelBaseMod::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
    {
        ExtensionModule::regModOptions(modOptReg);

        REG_CMDL_OPTION( OPTION_EXT_THREADS, "threads", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );

        if (useBigM()) {
            REG_CMDL_OPTION( OPTION_EXT_REMODEL_BIGM, "big-M", 1, 1, CMDL_OPTION_NEG_ERROR, true );
        }

        if (useNameSep()) {
            REG_CMDL_OPTION( OPTION_EXT_NAMESEP, "namesep", 1, 1, CMDL_OPTION_NEG_NO_ARG, true );
        }
    }

    /**
     * parse single option from command line options, this function is called for every delivered option
     * @param ref			reference number of option registration, should be used for discriminate the options
     * @param prio			priority value of option
     * @param opt			option
     * @return				true if option is used by the module
     */
    bool RemodelBaseMod::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
    {
        if (ExtensionModule::parseOption(ref, prio, opt))
            return true;

        switch (ref) {
            case OPTION_EXT_THREADS:
                _maxThreads = (unsigned)(opt->neg() ? 0 : opt->argAsInt(0, _ctrl));
                return true;

            case OPTION_EXT_REMODEL_BIGM:
                if (useBigM()) {
                    _bigM = STR_TO_CMPLREAL((*opt)[0].c_str());
                    return true;
                }
                break;

            case OPTION_EXT_NAMESEP:
                if (useNameSep()) {
                    _nameSep = parseOptString(opt);
                    return true;
                }
                break;
        }

        return false;
    }

    /**
     * parse single command line option containing a string
     * @param opt           option
     */
    unsigned RemodelBaseMod::parseOptString(CmdLineOptList::SingleOption *opt)
    {
        if (opt->neg())
            return 0;
        else
            return data()->globStrings()->storeInd((*opt)[0]);
    }

    /**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
    void RemodelBaseMod::usage(ostream& s)
    {
        ExtensionModule::usage(s);

        s << "  -threads <n>                  use maximal n concurrently running worker threads (0: no threading)" << endl;
        if (useBigM()) {
            s << "  -big-M <number>               huge number used for linearization (default is " << _bigM << ")" << endl;
        }
        if (useNameSep()) {
            s << "  -namesep <string>             separator string between original constraint or variable name and postfix (default is '" << data()->globStrings()->at(_nameSep) << "')" << endl;
        }
    }


	/**
	 * create the extension object from serialization
	 * @param si        serialization info
	 * @param data      main data object
	 * @param subCnt    count of sub data objects
	 * @param lc		line count per element or 0 if elements are len coded
	 * @param rline		remaining section start line
	 */
	ExtensionBase *RemodelBaseMod::createFromSerialization(MainData::SerializeInfo& si, const MainData *data, int subCnt, int lc, string &rline)
	{
        RemodelBase *ext = create(this);
		ext->deserializeFrom(si, data, subCnt, lc, rline);
        return ext;
	}
}


