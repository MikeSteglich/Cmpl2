#include "Solver.hh"

#include "../../Control/MainControl.hh"
#include "../../Control/FileBase.hh"

#include "../../Control/MainData.hh"
#include "../../CommonData/OptModel.hh"

#include <cstdlib>
#include <iomanip>


namespace cmpl
{


void Solver::init(MainControl *ctrl, MainData *data, const char *name)
{
    ModuleBase::init(ctrl, data, name);

    _solverName="CBC";
    _solverBinName = "";

    _instanceBaseName = FileBase::getTmpPath()+FileBase::getTmpFileName("cmpl",10000);
    _instanceFileName = _instanceBaseName+".mps";
    _instanceSolName = _instanceBaseName+".sol";
    _instanceCmdName = _instanceBaseName+".cmd";

    _solverCmdLine="";

    _objName="";
    _objSense="";

    _optFileName = "cmpl.opt";

    _solutionPool=false;

    readOptFile();



}


#define OPTION_SOLVER_SOLVERNAME	10
#define OPTION_SOLVER_OPTION        20
#define OPTION_SOLVER_DISPLAY       30



    /**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
    void Solver::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
    {
        ModuleBase::regModOptions(modOptReg);



        REG_CMDL_OPTION( OPTION_SOLVER_SOLVERNAME, "solver", 1, 1, CMDL_OPTION_NEG_NO_ARG, false );

        REG_CMDL_OPTION( OPTION_SOLVER_OPTION, "opt", 2, 200, CMDL_OPTION_NEG_NO_ARG, false );

        REG_CMDL_OPTION( OPTION_SOLVER_DISPLAY, "display", 1, 200, CMDL_OPTION_NEG_NO_ARG, false );



    }

    /**
     * parse single option from command line options, this function is called for every delivered option
     * @param ref			reference number of option registration, should be used for discriminate the options
     * @param prio			priority value of option
     * @param opt			option
     * @return				true if option is used by the module
     */
    bool Solver::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
    {
        if (ModuleBase::parseOption(ref, prio, opt))
            return true;

        switch (ref) {

        case OPTION_SOLVER_DISPLAY:
            if (!opt->neg()) {
                string dispOpt = (*opt)[0];
                if (StringStore::upperCase(dispOpt)=="SOLUTIONPOOL")
                    _solutionPool=true;
            }

            return true;

        case OPTION_SOLVER_SOLVERNAME:
            if (!opt->neg()) {
                string solverName = (*opt)[0];
                _solverName=StringStore::upperCase(solverName);
                if (!isImplemented(_solverName))
                    _ctrl->errHandler().error(ERROR_LVL_NORMAL, _ctrl->printBuffer("Solver '%s' is not supported", solverName.c_str()), opt->loc(true) );
            }

            return true;

        case  OPTION_SOLVER_OPTION:
            if (!opt->neg()) {
                string solverName = (*opt)[0];
                solverName = StringStore::lrTrim(StringStore::upperCase(solverName));

                if (solverName==_solverModule) {

                    for (size_t i=1; i<opt->size();i++) {
                        string option=(*opt)[i];
                        vector <string> optList;
                        StringStore::split(option,optList,"=");
                        solverOption solOpt;
                        solOpt.key=optList[0];
                        if (optList.size()>1)
                            solOpt.value=optList[1];
                        else
                            solOpt.value="";

                        _solverOpts.push_back(solOpt);
                    }

                }
            }

            return true;


        }

        return false;
    }

    /**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
    void Solver::usage(ostream& s)
    {
        ModuleBase::usage(s);

        s << "  -solver <solverName>                       specifies the Solver to be invoked" << endl;
        s << "  -opt <solverName> [<option>[=<val>] ...]   specifies the Solver to be invoked" << endl;
    }



void Solver::readOptFile() {

    //bool solverFileNameFound=false;

    char dirSepChar = (_ctrl->binFullName() ? FileBase::getDirSepChar(_ctrl->binFullName()->c_str()) : '\0');
    string fileName(FileBase::replFileInPath(_ctrl->binFullName(), &_optFileName, dirSepChar));

    try {
        FileInput inFile;
        istream *inStr = NULL;

        inFile.setFile(_data, IO_MODE_FILE, &fileName, NULL, true);
        inStr = inFile.open();

        int col, line = 0;
        string lineStr, s;

        while (getline(*inStr, lineStr)) {
            line++;

            if (!StringStore::startsWith(StringStore::lTrim(lineStr),"#") && (!StringStore::lrTrim(lineStr).empty())) {

                string solver, solverPath;
                StringStore::getOptionValue(lineStr, solver ,solverPath);

                solver=StringStore::upperCase((StringStore::lrTrim(solver)));
                solverPath=StringStore::lrTrim(solverPath);

                _implementedSolvers.push_back(solver);
                _solverBinNames[solver]=solverPath;

            }

        }

        inFile.close();
    }
    catch (FileException& e) {
        _ctrl->errHandler().internalError(_ctrl->printBuffer("%s: option file '%s'", e.what(), fileName.c_str()) ,&e);
    }

}

void Solver::setBinFullName(){

    if (!isImplemented(_solverName))
        _ctrl->errHandler().internalError( _ctrl->printBuffer("Solver '%s' is not supported", _solverName.c_str()) );

    _solverBinName=_solverBinNames[_solverName];
    replaceFullBinName();



}

bool Solver::isImplemented(string solverName){

    return (find(_implementedSolvers.begin(), _implementedSolvers.end(), solverName) != _implementedSolvers.end() );
}


void Solver::writeInstanceFile(string opts) {
    deleteTmpFiles();

    CmdLineOptList clOpts;
    PositionInfo pos(POSITION_TYPE_DESCR, "(internal)");

    if (!_isSilent)
        opts += _ctrl->printBuffer(" -fms %s", _instanceFileName.c_str());
    else
        opts += _ctrl->printBuffer(" -fms %s -silent", _instanceFileName.c_str());

    clOpts.addOption(opts, pos);
    _ctrl->runModuleFunc("writeMps", &clOpts);

    if (!FileBase::exists(_instanceFileName)) {
        _ctrl->errHandler().internalError( _ctrl->printBuffer("MPS file %s does not exist", _instanceFileName.c_str())  );
    }


}


void Solver::deleteTmpFiles() {
    if (FileBase::exists(_instanceFileName))
        remove(_instanceFileName.c_str());

    if (FileBase::exists(_instanceSolName))
        remove(_instanceFileName.c_str());

    if (FileBase::exists(_instanceCmdName))
        remove(_instanceCmdName.c_str());


}


void Solver::replaceFullBinName() {
    char dirSepChar = (_ctrl->binFullName() ? FileBase::getDirSepChar(_ctrl->binFullName()->c_str()) : '\0');

    string sep;
    sep.push_back(dirSepChar);

    if (!StringStore::startsWith(_solverBinName,sep))
        _solverBinName= FileBase::replFileInPath(_ctrl->binFullName(), &_solverBinName, dirSepChar);
}

int Solver::solve() {

    int buffSize = 128;
    char buffer[buffSize];
    int ret;

    if (!FileBase::exists(_solverBinName)) {
        _ctrl->errHandler().internalError( _ctrl->printBuffer("Binary for solver %s does not exist: '%s'", _solverName.c_str(), _solverBinName.c_str()) );
    }

    if (_solverCmdLine.empty()) {
        _ctrl->errHandler().internalError(_ctrl->printBuffer("Internal error, no cmd line for solver '%s' specified", _solverName.c_str())  );
    }

    CmplOutput(cout, "Solving instance using " + _solverName   );

    try {
        FILE* pipe = popen(_solverCmdLine.c_str(), "r");

        if (!pipe)
        {
            _ctrl->errHandler().internalError(_ctrl->printBuffer("Cannot execute solver '%s'", _solverName.c_str()) );
        }

        while (fgets(buffer, 128, pipe) != NULL) {
            if (!_isSilent)
                cout << buffer;
        }

        if (!_isSilent)
            cout << endl <<endl;;

        ret=pclose(pipe);

        if (ret==-1) {
            _ctrl->errHandler().internalError(_ctrl->printBuffer("Solver '%s' finished with failures", _solverName.c_str()));
        }

    } catch (exception const& e) {
        _ctrl->errHandler().internalError(_ctrl->printBuffer("Solver '%s' finished with failures: %s", _solverName.c_str(), e.what()));
    }

    return ret;

}


}
