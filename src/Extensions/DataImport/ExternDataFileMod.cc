
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


#include "ExternDataFileMod.hh"
#include "ExternDataFile.hh"
#include "../../Control/MainControl.hh"


namespace cmpl
{
	/*********** module definition **********/

	// defines the module "externDataFile" that is implemented in class "ExternDataFileMod".
	// to register this module you have to insert "MODULE_CLASS_REG(1, externDataFile)" to file "modules.reg"
	MODULE_CLASS( externDataFile, ExternDataFileMod )



    /*********** handling of command line options **********/

    /**
     * register command line options for the extension
     * @param ext           extension object
     * @param id			extension identificator
     */
    void ExternDataFileMod::regExtOptions(ExtensionBase *ext, int id)
    {
        if (_regPrecompiler) {
            const char *m = (_registerMods.size() > 0 ? _registerMods[0].c_str() : "precompile");
            REG_CMDL_OPTION_EXT(OPTION_EXT_EXEC_PRECOMP_DATFILE, "cdat", 1, 1, CMDL_OPTION_NEG_NO_ARG, true, id, m, EXT_CMDLOPT_PRECOMP_SIMPLE, ext);
            REG_CMDL_OPTION_EXT(OPTION_EXT_EXEC_PRECOMP_ASSARRSUB, "assert-array-sub", 0, 0, CMDL_OPTION_NEG_DELIV, true, id, m, EXT_CMDLOPT_PRECOMP_SIMPLE, ext);

            REG_CMDL_OPTION_EXT(OPTION_EXT_EXEC_PRECOMP_DATA, "data", 0, -1, CMDL_OPTION_NEG_ERROR, false, id, m, EXT_CMDLOPT_PRECOMP_PROC_DATA, ext);
        }

        if (_regInterpreter) {
            const char *m = (_registerMods.size() > 1 ? _registerMods[1].c_str() : "interpret");
            REG_CMDL_OPTION_EXT(OPTION_EXT_EXEC_INTERPRET_READALL, "read-all", 0, 0, CMDL_OPTION_NEG_DELIV, true, id, m, EXT_CMDLOPT_INTERPRET_SIMPLE, ext);
        }
    }

    /**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
    void ExternDataFileMod::usage(ostream& s)
    {
        DataImportBaseMod::usage(s);

        s << "  -cdat <file>                  set name for default data file" << endl;
        s << "  -data <string>                string with data declaration, mainly for use in cmpl header" << endl;
        s << "  -read-all                     read values for all symbols from a data file at once (default: false)" << endl;
        s << "  -assert-array-sub             check for a given array assertion of an extern data symbol only that the definition set is a subset (default: true)" << endl;
    }


}


