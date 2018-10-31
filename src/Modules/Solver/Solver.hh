#ifndef SOLVER_HH
#define SOLVER_HH


#include "../../Control/ModuleBase.hh"
#include "../../CommonData/OptModel.hh"


namespace cmpl
{



#define SOLVER_UNDEFINED 99

#define OPT_FILE_OK 100;
#define OPT_FILE_FAIL 101;

#define SOLVER_OK 102;
#define SOLVER_FAIL 103;


#if defined(_WIN32) || defined(WIN32)
    #define POPEN(f,a) = _popen(f,a)
    #define PCLOSE(f,a) = _popen(p)
#else
    #define POPEN(f,a) = popen(f,a)
    #define PCLOSE(f,a) = popen(p)
#endif



class Solver  : public ModuleBase
{


public:
    //Solver() {};

    /**
     * initialize modul, to call immediately after the constructor.
     * @param ctrl			main object
     * @param data			data object
     * @param name			module name (or alias)
     */
    virtual void init(MainControl *ctrl, MainData *data, const char *name);


public:

    bool isImplemented(string SolverName);

protected:
    /**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
    virtual void regModOptions(vector<CmdLineOptList::RegOption> &modOptReg);

    /**
     * parse single option from command line options, this function is called for every delivered option
     * @param ref			reference number of option registration, should be used for discriminate the options
     * @param prio			priority value of option
     * @param opt			option
     * @return				true if option is used by the module
     */
    virtual bool parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt);

    /**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
    virtual void usage(ostream& s);


protected:
    //bool _isActive;

    string _solverModule;

    string _solverName;
    map<string,string>   _solverBinNames;
    string _solverBinName;
    //int _solverStatus;

    vector <string> _implementedSolvers;

    string _instanceBaseName;
    string _instanceFileName;
    string _instanceSolName;
    string _instanceCmdName;

    string _optFileName;

    string _objName;
    string _objSense;

    struct solverOption {
        string key;
        string value;
    };

    bool _solutionPool;

    vector <solverOption> _solverOpts;

    string _solverCmdLine;


    void readOptFile();
    void setBinFullName();

    void writeInstanceFile();

    int solve();

    void deleteTmpFiles();

    void replaceFullBinName();



private:



};

}

#endif // SOLVER_HH
