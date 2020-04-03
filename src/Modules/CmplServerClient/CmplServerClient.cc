
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


#include "CmplServerClient.hh"
#include "../../Control/MainControl.hh"


namespace cmpl
{
	/*********** module definition **********/

	// defines the module "test" that is implemented in class "TestModule".
	// to register this module you have to insert "MODULE_CLASS_REG(1, test)" to file "modules.reg"
	MODULE_CLASS( runOnServer, CmplServerClient )



	/*********** initialization **********/

	/**
	 * initialize modul, to call immediately after the constructor.
	 * @param ctrl			main object
	 * @param data			data object
	 * @param name			module name (or alias)
	 */
	void CmplServerClient::init(MainControl *ctrl, MainData *data, const char *name)
	{
		ModuleBase::init(ctrl, data, name);

        _mode=-1;
        _serverUrl="nn";
        _optFileName = "cmpl.opt";
        _runOnServerScript="";
        _maxServerTries=10;
        _maxServerQueuingTime=300;
	}


	/*********** handling of command line options **********/

#define OPTION_SERVERCLIENT_URL	10
#define OPTION_SERVERCLIENT_SEND	    20
#define OPTION_SERVERCLIENT_KNOCK	    30
#define OPTION_SERVERCLIENT_RETRIEVE	    40
#define OPTION_SERVERCLIENT_CANCEL  	    50

#define OPTION_SERVERCLIENT_MAXTRIES  	    60
#define OPTION_SERVERCLIENT_MAXTIME  	    70

	/**
	 * register command line options options for delivery to this module
	 * @param modOptReg		vector to register in
	 */
	void CmplServerClient::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
	{
		ModuleBase::regModOptions(modOptReg);

		REG_CMDL_OPTION( OPTION_SERVERCLIENT_URL, "url", 1, 1, CMDL_OPTION_NEG_NO_ARG, false );
		REG_CMDL_OPTION( OPTION_SERVERCLIENT_SEND, "send", 0, 0, CMDL_OPTION_NEG_DELIV, false );
		REG_CMDL_OPTION( OPTION_SERVERCLIENT_KNOCK, "knock", 0, 0, CMDL_OPTION_NEG_DELIV, false );
        REG_CMDL_OPTION( OPTION_SERVERCLIENT_RETRIEVE, "retrieve", 0, 0, CMDL_OPTION_NEG_DELIV, false );
        REG_CMDL_OPTION( OPTION_SERVERCLIENT_CANCEL, "cancel", 0, 0, CMDL_OPTION_NEG_DELIV, false );

        REG_CMDL_OPTION( OPTION_SERVERCLIENT_MAXTRIES, "maxservertries", 1, 1, CMDL_OPTION_NEG_NO_ARG, false );
        REG_CMDL_OPTION( OPTION_SERVERCLIENT_MAXTIME, "maxqueuingtime", 1, 1, CMDL_OPTION_NEG_NO_ARG, false );

	}

	/**
	 * parse single option from command line options, this function is called for every delivered option
	 * @param ref			reference number of option registration, should be used for discriminate the options
	 * @param prio			priority value of option
	 * @param opt			option
	 * @return				true if option is used by the module
	 */
    bool CmplServerClient::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
    {

        if (ModuleBase::parseOption(ref, prio, opt))
            return true;

        string tmpArg;

        switch (ref) {
        case OPTION_SERVERCLIENT_URL:
            if (_mode == -1)
                _mode=SYNC_SOLVE;

            _serverUrl=(*opt)[0];
            return true;

        case OPTION_SERVERCLIENT_SEND:
            _mode=ASYNC_SEND;
            return true;

        case OPTION_SERVERCLIENT_KNOCK:
            _mode=ASYNC_KNOCK;
            return true;

        case OPTION_SERVERCLIENT_RETRIEVE:
            _mode=ASYNC_RETRIEVE;
            return true;

        case OPTION_SERVERCLIENT_CANCEL:
            _mode=ASYNC_CANCEL;
            return true;

        case OPTION_SERVERCLIENT_MAXTRIES:
            tmpArg = (*opt)[0];
            if (!StringStore::toInt(tmpArg,_maxServerTries))
                _ctrl->errHandler().error(ERROR_LVL_NORMAL, _ctrl->printBuffer("Wrong argument maxServerTries '%s' ", tmpArg.c_str()), opt->loc(true) );
            return true;

        case OPTION_SERVERCLIENT_MAXTIME:
            tmpArg = (*opt)[0];
            if (!StringStore::toInt(tmpArg,_maxServerQueuingTime))
                _ctrl->errHandler().error(ERROR_LVL_NORMAL, _ctrl->printBuffer("Wrong argument maxQueuingTime '%s' ", tmpArg.c_str()), opt->loc(true) );
            return true;
        }

        return false;
    }

	/**
	 * writes usage info for the module to stream
	 * @param s				stream to write to
	 */
	void CmplServerClient::usage(ostream& s)
	{
		ModuleBase::usage(s);

		s << "  -url <url>                   synchronious mode: sets the url of a CmplServer and runs the problem on it and waits for the results" << endl;
		s << "  -url <url> -send             asynchronious mode: sets the url of a CmplServer and sends the problem to it" << endl;
		s << "  -knock			             asynchronious mode: retrieves the status and the output of the problem running on a CmplServer " << endl;
		s << "  -retrieve                    asynchronious mode: retrieves the results of the problem " << endl;
        s << "  -cancel                      asynchronious mode: cancels a problem running on a CmplServer" << endl;

        s << "  -maxServerTries <tries>      defines the maximum number of failed accesses to a CmplServer" << endl;
        s << "  -maxQueuingTime <time>       defines the maximum queuing time of failed accesses to a CmplServer" << endl;
	}

	/**
	 * run module function
	 */
	void CmplServerClient::run()
	{
		_ctrl->errHandler().setExecStep("run");


        if ( (_mode==-1) || (_mode==1 && _serverUrl=="nn" ))
            _ctrl->errHandler().internalError("CmplServerCient error: no URL defined");


        string probName = string( modp()->data()->cmplFileBase() );
        probName+=".cmpl";


		PROTO_OUTL("Start run CmplServerClient module " << moduleName());

        readOptFile();

        string _serverCmdLine = _runOnServerScript + " " + probName + " " + _serverUrl  + " " + to_string(_maxServerTries) + " " + to_string(_maxServerQueuingTime) + " " + to_string(_mode) + " 2>&1";



        try {
           system(_serverCmdLine.c_str());


        } catch (exception const& e) {
            _ctrl->errHandler().internalError(_ctrl->printBuffer("CmplServerCient finished with failures: %s",  e.what()));
        }




	

		PROTO_OUTL("End run CmplServerClient module " << moduleName());
	}


    void CmplServerClient::readOptFile() {


        char dirSepChar = (_ctrl->binFullName() ? FileBase::getDirSepChar(_ctrl->binFullName()->c_str()) : '\0');
        string fileName(FileBase::replFileInPath(_ctrl->binFullName(), &_optFileName, dirSepChar));

        try {
            FileInput inFile;
            istream *inStr = NULL;
            bool scriptEntryFound = false;

            inFile.setFile(_data, IO_MODE_FILE, &fileName, NULL, true);
            inStr = inFile.open();

            int line = 0;
            string lineStr, s;

            while (getline(*inStr, lineStr)) {
                line++;

                if (!StringStore::startsWith(StringStore::lTrim(lineStr),"#") && (!StringStore::lrTrim(lineStr).empty())) {

                    string solver, solverPath;
                    StringStore::getOptionValue(lineStr, solver ,solverPath);

                    solver=StringStore::upperCase((StringStore::lrTrim(solver)));
                    solverPath=StringStore::lrTrim(solverPath);

                    if (solver=="CMPLSERVERCLIENT") {
                        _runOnServerScript=solverPath;
                        scriptEntryFound=true;
                    }
                }

            }

            inFile.close();

            if (!scriptEntryFound)
                _ctrl->errHandler().internalError("No entry for CmplServerClient script found in cmpl.opt");

        }
        catch (FileException& e) {
            _ctrl->errHandler().internalError(_ctrl->printBuffer("%s: option file '%s'", e.what(), fileName.c_str()) ,&e);
        }


    }

}

