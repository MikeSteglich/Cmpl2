#include "SolverScip.hh"
#include "../../Control/MainControl.hh"
#include "../../CommonData/Solution.hh"


namespace cmpl
{
/*********** module definition **********/

// defines the module "SolveCbc" that is implemented in class "SolveCbc".
// to register this module you have to insert "MODULE_CLASS_REG(1, SolverCbc)" to file "modules.reg"
MODULE_CLASS( solverScip, SolverScip )



/*********** initialization **********/

/**
     * initialize modul, to call immediately after the constructor.
     * @param ctrl			main object
     * @param data			data object
     * @param name			module name (or alias)
     */
void SolverScip::init(MainControl *ctrl, MainData *data, const char *name)
{
    _solverModule="SCIP";
    Solver::init(ctrl, data, name);
}


/*********** handling of command line options **********/




/**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
void SolverScip::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
{
    Solver::regModOptions(modOptReg);

}

/**
     * parse single option from command line options, this function is called for every delivered option
     * @param ref			reference number of option registration, should be used for discriminate the options
     * @param prio			priority value of option
     * @param opt			option
     * @return				true if option is used by the module
     */
bool SolverScip::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
{
    if (Solver::parseOption(ref, prio, opt))
        return true;

    return false;
}

/**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
void SolverScip::usage(ostream& s)
{
    Solver::usage(s);

}

/**
     * run module function
     */
void SolverScip::run()
{

    if (_solverName=="SCIP") {
        _ctrl->errHandler().setExecStep("run");

        GET_DATA(OptModel,om);
        if (!om->isLinearModel())
            _ctrl->errHandler().internalError("SCIP cannot solve a nonlinear model"  );


        PROTO_OUTL("Start SolverScip module " << moduleName());

        setBinFullName();

        PROTO_OUTL("SolverScip: writing instance file " << moduleName());
        writeInstanceFile();

        PROTO_OUTL("SolverScip: solving instance" << moduleName());

        GET_DATA(Solution,sol);
        if (!sol)
            GET_NEW_DATA(Solution,sol);

        string probName = string( modp()->data()->cmplFileBase() )+".cmpl";
        sol->prepareSolutionData(probName, _solverName,_data,this);

        generateCmdLine();

        cout << _solverCmdLine << endl;

        int ret = solve();

        PROTO_OUTL("SolverScip: finished solving  and reading solution" << moduleName());

        if (ret==0)
            readSolFile(sol,om);

        deleteTmpFiles();
        PROTO_OUTL("End SolverScip module " << moduleName());
    }
}


void SolverScip::writeOptFile(){

    try {

        ofstream  optFile( _instanceCmdName.c_str() ) ;

        for (size_t i=0; i<_solverOpts.size(); i++) {
            optFile << _solverOpts[i].key << " = " << _solverOpts[i].value << endl;
        }

        optFile.close();
    }
    catch (exception& ex) {
        _ctrl->errHandler().internalError( _ctrl->printBuffer("Internal error while writing scip option file >> '%s'", string(ex.what()).c_str() ) ,NULL);
    }
}

void SolverScip::generateCmdLine() {
    writeOptFile();
    _solverCmdLine=_solverBinName+" -c \"set load " + _instanceCmdName + "\" ";
    _solverCmdLine+=" -c \"read "+_instanceFileName+"\"";
    _solverCmdLine+=" -c optimize";
    _solverCmdLine+=" -c \"write solu "+_instanceSolName+"\"";
    _solverCmdLine+=" -c quit  2>&1";
}


void SolverScip::readSolFile(Solution* sol,  OptModel* om) {

    int nrOfSolutions=0;
    unsigned long lineNr=0;

    string line;

    sol->setStatus("normal");
    sol->setNrOfSolutions(nrOfSolutions);

    SingleSolution solution;

    unsigned long rowCnt = om->rows().size();
    LinearModel *lm = om->getRowModel();
    const vector<LinearModel::Coefficient> *coeffs = lm->coeffs();

    for (unsigned long j=0; j<sol->nrOfVariables(); j++) {
        SolutionElement solElem;
        solElem.setModelElement(sol->modelVariable(j));
        solution.setVariable(solElem);
    }

    try {
        ifstream  solFile( _instanceSolName, ifstream::binary) ;

        if (!solFile.is_open())
            _ctrl->errHandler().internalError(_ctrl->printBuffer("Cannot read solution file '%s'", _instanceSolName.c_str() )  ,NULL);


        while ( getline( solFile, line)  ) {

            line=StringStore::lrTrim(line);
            vector<string> solList;


            lineNr++;
            if (lineNr==1) {
                StringStore::split(line,solList,":");
                solution.setStatus(solList[1]);
                if (  StringStore::contains(StringStore::lrTrim(solList[1]),"optimal"  )) {
                    nrOfSolutions=1;
                } else {
                    nrOfSolutions=0;
                    break;
                }
                continue;
            }

            if (lineNr==2) {
                StringStore::split(line,solList, ":");
                double objVal;
                if (!StringStore::toDouble(solList[1],objVal))
                    _ctrl->errHandler().internalError("Internal error while reading objective function value from Scip solution file");
                solution.setValue(objVal);
                continue;
            }

            if (lineNr>2) {
                StringStore::split(line,solList);
                string varName=StringStore::lrTrim(solList[0]);
                double activity;
                if (!StringStore::toDouble(solList[1],activity))
                    _ctrl->errHandler().internalError("Internal error while reading var activity value from Scip solution file");

                unsigned long idx=sol->varMpsIdxByName(varName);
                solution.variable(idx)->setActivity(activity);
            }
        }


        for(unsigned long i=1; i<=sol->nrOfConstraints(); i++) {
            double conAct = solution.calculateConActivity(om, sol, coeffs[i] );

            SolutionElement solElem;
            solElem.setActivity(conAct);
            solElem.setModelElement(sol->modelConstraint(i));
            solution.setConstraint(solElem);
        }


        sol->setSolution(solution);

        if (FileBase::exists(_instanceSolName))
            remove(_instanceSolName.c_str());


    }catch (FileException& e) {
        _ctrl->errHandler().internalError(_ctrl->printBuffer("%s: solution file '%s'", e.what(), _instanceSolName.c_str()) ,&e);
    }

    sol->setStatus("normal");
    sol->setNrOfSolutions(nrOfSolutions);
}


}
