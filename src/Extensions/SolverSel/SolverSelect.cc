
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


#include "SolverSelect.hh"
#include "SolverSelectMod.hh"
#include "../../Control/MainControl.hh"
#include "../../Modules/Interpreter/Interpreter.hh"



namespace cmpl
{
    /**
     * constructor
     * @param mod			module creating this extension object
     */
    SolverSelect::SolverSelect(SolverSelectMod *mod): ExtensionBase(mod)
    {
        _configFile = mod->data()->globStrings()->storeInd(SolverSelectMod::defaultConfigFile());
        _configFileLoc = LocationInfo(PositionInfo(POSITION_TYPE_DESCR, "default for solver selection config file"));
    }

    /**
     * run the extension function for processing a command line option
     * @param mod			module calling the extension
     * @param step			execution step within the module
     * @param id			additional identificator
     * @param ref           reference number of option registration, should be used for discriminate the options
     * @param prio          priority value of option
     * @param opt           command line option
     * @param par			additional parameter
     * @return              true if option is used by the extension
     */
    bool SolverSelect::run(ModuleBase *mod, int step, int id, int ref, int prio, CmdLineOptList::SingleOption *opt, void *par)
    {
        switch (ref) {
            case OPTION_EXT_EXEC_SOLVERSEL_CONFIG_FILE:
                _configFile = 0;
                if (!opt->neg() && opt->size() == 1) {
                    _configFile = mod->data()->globStrings()->storeInd((*opt)[0]);
                    _configFileLoc = opt->loc(true);
                }
                return true;

            case OPTION_EXT_EXEC_SOLVERSEL_SOLVERNAME:
                _solver.clear();
                if (!opt->neg() && opt->size() == 1) {
                    _solver = StringStore::upperCase((*opt)[0]);
                }
                return true;
        }

        return false;
    }

    /**
	 * run the extension function
	 * @param mod			module calling the extension
	 * @param step			execution step within the module
	 * @param id			additional identificator
	 * @param par			additional parameter
	 */
	void SolverSelect::run(ModuleBase *mod, int step, int id, void *par)
	{
		if (step == EXT_STEP_INTERPRET_SOLVERSEL) {
			PROTO_MOD_OUTL(mod, " extension SolverSelect: " << step << " " << id);

            if (_configFile) {
                exec((Interpreter *)mod, (OptModel *)par);
            }
            else {
                PROTO_MOD_OUTL(mod, " no config file -> no solver selection");
            }
		}
		else {
			mod->ctrl()->errHandler().internalError(mod->ctrl()->printBuffer("invalid execution step for extension SolverSelect, called for '%s' %d %d", mod->moduleName(), step, id));
		}

		PROTO_MOD_OUTL(mod, " extension SolverSelect: end");
	}

	/**
	 * write data object to output stream
	 * @param si        serialization info
	 * @param data      main data object
	 */
	void SolverSelect::serializeTo(MainData::SerializeInfo& si, const MainData *data)
	{
		// extension has no own data
		//TODO: config file name
		(*si.ostr) << endl;
	}

	/**
	 * fill data object from input stream
	 * @param si        serialization info
	 * @param data      main data object
	 * @param subCnt    count of sub data objects
	 * @param lc		line count per element or 0 if elements are len coded
	 * @param rline		remaining section start line
	 */
	void SolverSelect::deserializeFrom(MainData::SerializeInfo& si, const MainData *data, int subCnt, int lc, string &rline)
	{
		// extension has no own data
		//TODO: config file name
		si.pos->addLines();
	}


    /**
     * execute solver selection by reading config file
     * @param modp      intepreter module calling the extension
     * @param om        optimization model
     */
    void SolverSelect::exec(Interpreter *modp, OptModel *om)
    {
        string filename = modp->data()->globStrings()->at(_configFile);

        try {
            FileInput inFile;
            istream *inStr = NULL;
            char dirSepChar = (modp->ctrl()->binFullName() ? FileBase::getDirSepChar(modp->ctrl()->binFullName()->c_str()) : '\0');
            bool secTry = (dirSepChar && filename.find(dirSepChar) == string::npos);

            // first try: search filename in working directory
            try {
                inFile.setFile(modp->data(), IO_MODE_FILE, &filename, NULL);
                inStr = inFile.open();
            }
            catch (FileException& e) {
                if (!secTry)
                    throw;
            }

            // second try: search filename in the directory of the executing binary
            if (!inStr) {
                try {
                    inFile.close();
                }
                catch(...) {}

                string file2(FileBase::replFileInPath(modp->ctrl()->binFullName(), &filename, dirSepChar));
                inFile.setFile(modp->data(), IO_MODE_FILE, &file2, NULL, true);
                inStr = inFile.open();
            }

            // execute using open config file
            exec(modp, om, inStr);

            inFile.close();
        }
        catch (FileException& e) {
            modp->ctrl()->errHandler().error(ERROR_LVL_NORMAL, modp->ctrl()->printBuffer("%s: solver selection config file '%s'", e.what(), filename.c_str()), _configFileLoc);
        }
    }

    /**
     * execute solver selection using open config file
     * @param modp      intepreter module calling the extension
     * @param om        optimization model
     * @param conf      input stream for reading open config file
     */
    void SolverSelect::exec(Interpreter *modp, OptModel *om, istream *conf)
    {
        string sect;
        sect.append("[").append(_solver).append("]");

        string l, s;
        int line = 0;
        //size_t i;
        bool inSect = false;
        PositionInfo pos(&_configFileLoc, POSITION_TYPE_FILE, modp->data()->globStrings()->at(_configFile));

        while (getline(*conf, l)) {
            line++;
            s = StringStore::rTrim(StringStore::lTrim(l));

            // skip empty lines and comment lines (starting with "#" or "//")
            if (!s.empty() && s[0] != '#' && (s.size() < 2 || s[0] != '/' || s[1] != '/')) {
                if (!inSect) {
                    // check for section
                    if (s[0] == '[' && StringStore::upperCase(s) == sect)
                        inSect = true;
                }
                else {
                    if (s[0] == '[')
                        return;

                    pos.set(line);
                    execLine(modp, om, s, pos);
                }
            }
        }
    }

    /**
     * execute for a line within the solver section of the config file
     * @param modp      intepreter module calling the extension
     * @param om        optimization model
     * @param line      line from config file
     * @param pos       position within config file
     */
    void SolverSelect::execLine(Interpreter *modp, OptModel *om, string line, PositionInfo& pos)
    {
        // separate condition
        size_t i = line.find(':');
        if (i == string::npos) {
            LocationInfo lce(pos);
            modp->ctrl()->errHandler().error(ERROR_LVL_EASY, "wrong line format in solver selection config file", lce);
            return;
        }

        // eval condition
        PositionInfo pp = pos + i;
        LocationInfo lcc(pos, pp);
        if (evalCondition(StringStore::lrTrim(line.substr(0, i)), modp, om, lcc)) {
            pp += 1;
            string opts = line.substr(i + 1);
            i = opts.find_first_not_of(StringStore::whiteSpaces());
            if (i != string::npos) {
                if (i > 0) {
                    pp += i;
                    opts = opts.substr(i);
                }

                // check type of line
                size_t w = opts.find_first_of(StringStore::whiteSpaces());
                if ((w == 5 && StringStore::startsWith(opts, "ERROR")) || w == 7 && StringStore::startsWith(opts, "WARNING")) {
                    // display error or warning
                    LocationInfo lce(pos);
                    string msg = StringStore::lTrim(opts.substr(w + 1));
                    modp->ctrl()->errHandler().error((w == 5 ? ERROR_LVL_NORMAL : ERROR_LVL_WARN), msg.c_str(), lce);
                }
                else {
                    // add command line options
                    addCmdLineOpts(modp, opts, pp);
                }
            }
        }
    }

    /**
     * evaluate boolean condition about optimization model
     * @param cond      condition string
     * @param modp      intepreter module calling the extension
     * @param om        optimization model
     * @param lc        location within config file
     */
    bool SolverSelect::evalCondition(string cond, Interpreter *modp, OptModel *om, LocationInfo& lc)
    {
        if (cond.empty())
            return true;

        // check for negation
        bool neg = false;
        if (StringStore::startsWith(cond, "no-")) {
            neg = true;
            cond = cond.substr(3);
        }

        bool res = false;

        // check whether model is linear
        if (cond == "linear") {
            res = om->isLinearModel();
        }

        //TODO: other conditions

        else {
            modp->ctrl()->errHandler().error(ERROR_LVL_EASY, modp->ctrl()->printBuffer("unknown condition '%s' in solver selection config file", cond.c_str()), lc);
            neg = false;
        }

        return (neg ? !res : res);
    }

    /**
     * add command line options
     * @param modp      intepreter module calling the extension
     * @param opts      command line options to add
     * @param pos       position info within config file
     */
    void SolverSelect::addCmdLineOpts(Interpreter *modp, string& opts, PositionInfo &pos)
    {
        // construct command line option list
        CmdLineOptList cmdOptList;
        cmdOptList.addOption(opts, pos);

        // store command line option list, and use it also for this module
        modp->ctrl()->appendCmdLineOpts(&cmdOptList, CMDLINE_OPT_PARSE_HEADER, true, true);
    }

}


