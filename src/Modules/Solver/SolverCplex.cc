#include "SolverCplex.hh"
#include "../../Control/MainControl.hh"
#include "../../CommonData/Solution.hh"


namespace cmpl
{
/*********** module definition **********/

// defines the module "SolveCbc" that is implemented in class "SolveCbc".
// to register this module you have to insert "MODULE_CLASS_REG(1, SolverCbc)" to file "modules.reg"
MODULE_CLASS( solverCplex, SolverCplex )



/*********** initialization **********/

/**
     * initialize modul, to call immediately after the constructor.
     * @param ctrl			main object
     * @param data			data object
     * @param name			module name (or alias)
     */
void SolverCplex::init(MainControl *ctrl, MainData *data, const char *name)
{
    _solverModule="CPLEX";
    Solver::init(ctrl, data, name);
 }


/*********** handling of command line options **********/




/**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
void SolverCplex::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
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
bool SolverCplex::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
{
    if (Solver::parseOption(ref, prio, opt))
        return true;

    return false;
}

/**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
void SolverCplex::usage(ostream& s)
{
    Solver::usage(s);

}

/**
     * run module function
     */
void SolverCplex::run()
{
    GET_DATA(OptModel,om);

    if (_solverName=="CPLEX" && !om->exportOnly()) {
        _ctrl->errHandler().setExecStep("run");

        if (!om->isLinearModel())
            _ctrl->errHandler().internalError("CPLEX cannot solve a nonlinear model within CMPL"  );


        PROTO_OUTL("Start SolverCplex module " << moduleName());

        setBinFullName();

        PROTO_OUTL("SolverCplex: writing instance file " << moduleName());
        writeInstanceFile();

        PROTO_OUTL("SolverCplex: solving instance" << moduleName());

        GET_DATA(Solution,sol);
        if (!sol)
            GET_NEW_DATA(Solution,sol);

        string probName = string( modp()->data()->cmplFileBase() )+".cmpl";
        sol->prepareSolutionData(probName, _solverName,_data,this);

        generateCmdLine(sol,om);

        cout << _solverCmdLine << endl;

        int ret = solve();

        PROTO_OUTL("SolverCplex: finished solving  and reading solution" << moduleName());

        if (ret==0)
           readSolFile(sol,om);

        deleteTmpFiles();
        PROTO_OUTL("End SolverCplex module " << moduleName());
    }
}


void SolverCplex::writeCommandFile( OptModel* om){

    try {

       // time_t now = time(0);
       // char* currtime = ctime(&now);

        ofstream  cmdFile( _instanceCmdName.c_str() ) ;

        cmdFile <<  " read " << _instanceFileName << endl;

        for (size_t i=0; i<_solverOpts.size(); i++) {
            cmdFile << "set ";
            cmdFile << StringStore::replaceAll(_solverOpts[i].key,"/"," ");
            cmdFile <<  " " + _solverOpts[i].value << endl;
        }

        cmdFile << ( om->isInteger() ? "mipopt" : "opt") << endl;

        cmdFile << "write " << _instanceSolName   ;
        cmdFile << ( _solutionPool ? " all" :"");
        cmdFile << endl;

        //cmdFile << "quit" << endl;

        cmdFile.close();


    }
    catch (exception& ex) {
        _ctrl->errHandler().internalError( _ctrl->printBuffer("Internal error while writing cplex command file >> '%s'", string(ex.what()).c_str() ) ,NULL);
    }
}

void SolverCplex::generateCmdLine(Solution* sol, OptModel* om ) {

    writeCommandFile(om);
    _solverCmdLine=_solverBinName+" -f " + _instanceCmdName + " 2>&1";
}


string SolverCplex::readXmlVal(string valString) {
    string ret;
    vector <string> valList;
    StringStore::split(StringStore::lrTrim(valString),valList,"=");
    if (valList.size()==0)
        _ctrl->errHandler().internalError( _ctrl->printBuffer("internal error while reading Cplex solution file: %s", valString.c_str()) ,NULL);
    ret = valList[1];
    StringStore::cleanDoubleQuotes(ret);
    return ret;

}

void SolverCplex::readSolFile(Solution* sol,  OptModel* om) {

    string line;

    double inf = std::numeric_limits<double>::infinity();

    unsigned long varIdx;
    unsigned long conIdx;

    unsigned long lineNr=0;
    bool headerSection=false;
    bool conSection=false;
    bool varSection=false;

    bool continueReading=true;

    int nrOfSolutions=0;

    SingleSolution* solution;

    try {

        ifstream  solFile( _instanceSolName, ifstream::binary) ;

        if (!solFile.is_open())
            _ctrl->errHandler().internalError(_ctrl->printBuffer("Cannot read solution file '%s'", _instanceSolName.c_str() )  ,NULL);


        while ( getline( solFile, line) && continueReading ) {

            line=StringStore::lrTrim(line);

            lineNr++;
            if (lineNr==1) {
                if (!StringStore::startsWith(line,"<?xml"))
                    _ctrl->errHandler().internalError(_ctrl->printBuffer("Wrong file type for file '%s'", _instanceSolName.c_str() )  ,NULL);
                continue;
            }

            if (lineNr==2 && !StringStore::startsWith(line,"<CPLEXSolution"))
                _ctrl->errHandler().internalError(_ctrl->printBuffer("Wrong file type for file '%s'", _instanceSolName.c_str() )  ,NULL);


            if (StringStore::startsWith(line,"<CPLEXSolutions"))
                continue;


            if (StringStore::startsWith(line,"<CPLEXSolution")) {
                solution = new SingleSolution();

                varIdx=0;
                conIdx=0;

                headerSection=false;
                conSection=false;
                varSection=false;

                continue;
            }


            if (StringStore::startsWith(line,"</CPLEXSolution") && !StringStore::startsWith(line,"</CPLEXSolutions")) {
                sol->setSolution(*solution);
                delete solution;

                headerSection=false;
                conSection=false;
                varSection=false;
            }

            if (StringStore::startsWith(line,"<header")) {

                headerSection=true;
                conSection=false;
                varSection=false;
                continue;
            }

            if (StringStore::startsWith(line,"<linearConstraints")) {

                headerSection=false;
                conSection=true;
                varSection=false;
                continue;
            }

            if (StringStore::startsWith(line,"</linearConstraints")) {

                headerSection=false;
                conSection=false;
                varSection=false;
                continue;
            }

            if (StringStore::startsWith(line,"<variables")) {
                headerSection=false;
                conSection=false;
                varSection=true;
                continue;
            }

            if (StringStore::startsWith(line,"</variables")) {
                headerSection=false;
                conSection=false;
                varSection=false;
                continue;
            }

            if (headerSection) {

                if (StringStore::startsWith(line, "objectiveValue")) {
                    string objValStr=readXmlVal(line);
                    double objVal;
                    if (!StringStore::toDouble(objValStr,objVal))
                        _ctrl->errHandler().internalError("Internal error while reading objective function value from Cplex solution file" ,NULL);

                    nrOfSolutions++;
                    solution->setValue(objVal);
                    continue;
                }

                if (StringStore::startsWith(line, "solutionStatusString")) {
                    string objStatus=readXmlVal(line);
                    solution->setStatus(objStatus);

                    if (StringStore::contains(objStatus,"infeasible") ||  StringStore::contains(objStatus,"undefined")) {
                        sol->setNrOfSolutions(0);
                        continueReading=false;
                        continue;
                    }
                    continue;
                }

            }

            if (varSection) {

                SolutionElement solElem;
                solElem.setMarginal(0);

                double activity=0;
                double marginal=0;

                int actPos=-1;
                int margPos=-1;

                vector<string> varXmlVals;
                StringStore::split(line,varXmlVals);

                for (int i=0; i<varXmlVals.size();i++) {
                    if (StringStore::startsWith(varXmlVals[i],"value"))
                        actPos=i;
                    if (StringStore::startsWith(varXmlVals[i],"reducedCost"))
                        margPos=i;
                }

                string valStr=readXmlVal(varXmlVals[actPos]);
                if (!StringStore::toDouble(valStr,activity))
                    _ctrl->errHandler().internalError("Internal error while reading activity from Cplex solution file" ,NULL);
                solElem.setActivity(activity);

                if (!om->isInteger() || margPos>-1) {
                    string valStr=readXmlVal(varXmlVals[margPos]);
                    if (!StringStore::toDouble(valStr,marginal))
                        _ctrl->errHandler().internalError("Internal error while reading marginal from Cplex solution file" ,NULL);
                    solElem.setMarginal(marginal);
                }

                solElem.setModelElement(sol->modelVariable(varIdx));
                solution->setVariable(solElem);
                varIdx++;

                continue;
            }

            if (conSection) {

                SolutionElement solElem;
                solElem.setMarginal(0);
                solElem.setModelElement(sol->modelConstraint(conIdx));

                double activity=0;
                double slack=0;
                double marginal=0;

                int actPos=-1;
                int margPos=-1;

                vector<string> conXmlVals;
                StringStore::split(line,conXmlVals);

                for (int i=0; i<conXmlVals.size();i++) {
                    if (StringStore::startsWith(conXmlVals[i],"slack"))
                        actPos=i;
                    if (StringStore::startsWith(conXmlVals[i],"dual"))
                        margPos=i;
                }

                string valStr=readXmlVal(conXmlVals[actPos]);
                if (!StringStore::toDouble(valStr,slack))
                    _ctrl->errHandler().internalError("Internal error while reading activity from Cplex solution file" ,NULL);

                if (slack>0) {
                    activity=solElem.upperBound()-slack;
                } else if (slack<0) {
                    if (solElem.type()=="N")
                        activity=slack * -1;
                    else
                        activity=solElem.lowerBound()+slack * -1;
                } else {
                    if (solElem.upperBound()!=inf) {
                        activity=solElem.upperBound();
                    } else  if (solElem.lowerBound()!=-inf) {
                        activity=solElem.lowerBound();
                    }

                }

                solElem.setActivity(activity);

                if (!om->isInteger()|| margPos>-1) {
                    string valStr=readXmlVal(conXmlVals[margPos]);
                    if (!StringStore::toDouble(valStr,marginal))
                        _ctrl->errHandler().internalError("Internal error while reading marginal from Cplex solution file" ,NULL);
                    solElem.setMarginal(marginal);
                }

                solution->setConstraint(solElem);
                conIdx++;
                continue;
            }

        }


    }catch (FileException& e) {
        _ctrl->errHandler().internalError(_ctrl->printBuffer("%s: solution file '%s'", e.what(), _instanceSolName.c_str()) ,&e);
    }

    sol->setStatus("normal");
    sol->setNrOfSolutions(nrOfSolutions);
}



}
