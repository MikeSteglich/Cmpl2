#ifndef SOLUTION_HH
#define SOLUTION_HH

#include "../Control/MainData.hh"
#include "OptModel.hh"

using namespace std;



namespace cmpl
{

class Solution;

/**
 * class for storing a model element (variable or constraint) to the solution
 */
class ModelElement {
private:

    string _name;                       ///< name of the variable or constraint
    string _type;                       ///< type of the variable or constraint

    double _lowerBound;                 ///< lower bound of the variable or constraint
    double _upperBound;                 ///< upper bound of the variable or constraint

public:

    /**
     * constructor
     */
    ModelElement();

    /**
     * gets the name of the variable or constraint
     */
    inline string name() { return _name;}

    /**
     * sets the name of the variable or constraint
     * @param name        name of the variable or constraint
     */
    inline void setName(string name) { _name=name;}

    /**
     * gets the type of the variable or constraint
     */
    inline string type() { return _type;}

    /**
     * sets the type of the variable or constraint
     * @param type        type of the variable or constraint
     */
    inline void setType(string type) { _type=type;}

    /**
     * gets the lower bound of the variable or constraint
     */
    inline double lowerBound() {return _lowerBound; }

    /**
     * sets the lower bound of the variable or constraint
     * @param lowerBound        lower bound of the variable or constraint
     */
    inline void setLowerBound(double lowerBound) { _lowerBound=lowerBound;}

    /**
     * gets the upper bound of the variable or constraint
     */
    inline double upperBound() {return _upperBound; }

    /**
     * sets the upper bound of the variable or constraint
     * @param upperBound        upper bound of the variable or constraint
     */
    inline void setUpperBound(double upperBound) { _upperBound=upperBound;}

};

/**
 * class for storing a solution element (variable or constraint)
 */
class SolutionElement {

private:
    double _activity;                ///< activity of the variable or constraint
    double _marginal;                ///< marginal of the variable or constraint

    ModelElement *_modElement;      ///< model element of the variable or constraint


public:

    /**
     * constructor
     */
    SolutionElement();

    /**
     * sets the corresponding model element for the variable or constraint
     * @param modElement        model element
     */
    inline void setModelElement(ModelElement *modElement) { _modElement=modElement;}

    /**
     * gets the name of the variable or constraint
     */
    inline string name() { return _modElement->name();}

    /**
     * gets the type of the variable or constraint
     */
    inline string type() { return _modElement->type();}

    /**
     * gets the activity of the variable or constraint
     */
    inline double activity() { return _activity;}

    /**
     * sets the activity bound of the variable or constraint
     * @param activity        activity  of the variable or constraint
     */
    inline void setActivity(double activity) { _activity=activity;}

    /**
     * gets the lower bound of the variable or constraint
     */
    inline double lowerBound() {return _modElement->lowerBound(); }

    /**
     * gets the upper bound of the variable or constraint
     */
    inline double upperBound() {return _modElement->upperBound(); }

    /**
     * gets the marginal of the variable or constraint
     */
    inline double marginal() { return _marginal;}

    /**
     * sets the marginal bound of the variable or constraint
     * @param marginal        marginal  of the variable or constraint
     */
    inline void setMarginal(double marginal) { _marginal=marginal;}

};


/**
 * class for storing a single solution
 */
class SingleSolution {

private:

    string _status;
    double _value;
    vector<SolutionElement> _variables;
    vector<SolutionElement> _constraints;


public:

    SingleSolution();

    inline string status() { return _status;}
    inline void setStatus(string status) { _status=status;}

    inline double value() { return _value;}
    inline void setValue(double value) { _value=value;}

    inline vector<SolutionElement>* variables() { return &_variables;}
    inline void setVariable(SolutionElement& variable) {_variables.push_back(variable);}

    inline SolutionElement* variable(unsigned long idx) {return &_variables[idx]; }

    inline vector<SolutionElement>* constraints() { return &_constraints;}
    inline void setConstraint(SolutionElement& constraint) {_constraints.push_back(constraint);}

    inline SolutionElement* constraint(unsigned long idx) {return &_constraints[idx]; }

    double calculateConActivity(OptModel *om, Solution* sol, const vector<LinearModel::Coefficient>& coeffs);

};




class Solution : public MainData::DataBase
{

private:

    map<string,unsigned long>   _colNameMap;
    map<string,unsigned long>   _rowNameMap;

    map<unsigned long,unsigned long>   _colIdxMap;
    map<unsigned long,unsigned long>   _rowIdxMap;

    map<unsigned long,unsigned long>   _colSolIdxMap;

    string _probName;
    string _objName;
    string _objSense;

    unsigned long _nrOfVariables;
    unsigned long _nrOfIntegerVariables;
    unsigned long _nrOfConstraints;

    string _solver;
    string _solverLocation;

    int _nrOfSolutions;

    string _status;

    vector<SingleSolution> _solutions;

    OptModel *_om;

    bool _hasMarginal;

    vector<ModelElement> _modVariables;
    vector<ModelElement> _modConstraints;

    void getVarBounds(OptVar *ov, double &lowerBound, double &upperBound );
    //double getVarUpperBound(OptVar *ov );

public:
    Solution (const char *m, MainData *data): MainData::DataBase(m, data)		{ _nrOfSolutions=0; }

    inline ~Solution()	{ cleanUp(); }

    void prepareSolutionData(string probName, string solver, bool intRelaxation, MainData *md, ModuleBase *mb);

    inline string problemName() {return _probName;}
    inline void setProblemName(string name) {_probName=name;}

    inline string objSense() { return _objSense;}
    inline string objName() { return _objName;}
    inline unsigned long nrOfVariables() {return _nrOfVariables;}
    inline unsigned long nrOfIntegerVariables() {return _nrOfIntegerVariables;}
    inline unsigned long nrOfConstraints() {return _nrOfConstraints;}

    inline string solver() { return _solver;}
    inline void setSolver(string& solver) { _solver=solver;}

    inline string solverLocation() { return _solverLocation;}
    inline void solverLocation(string& solverLocation) { _solverLocation=solverLocation;}

    inline int nrOfSolutions() {return _nrOfSolutions;}
    inline void setNrOfSolutions(int nr) {_nrOfSolutions=nr;}

    inline string status() {return _status;}
    inline void setStatus(string status) {_status=status;}

    inline vector<SingleSolution> solutions() {return _solutions;}
    inline void setSolution(SingleSolution& sol) { _solutions.push_back(sol);}

    inline SingleSolution solution() {return _solutions[0];}

    inline SingleSolution* solution(int idx) {return &_solutions[idx];}

    inline map<unsigned long,unsigned long>* varIndicesByIdx() {return &_colIdxMap; }

    inline unsigned long varMpsIdxByName(string& name) { return _colNameMap[name];}
    inline unsigned long varMpsIdxByIdx(unsigned long idx) { return _colIdxMap[idx];}

    inline unsigned long conMpsIdxByName(string& name) { return _rowNameMap[name];}
    inline unsigned long conMpsIdxByIdx(unsigned long idx) { return _rowIdxMap[idx];}

    inline bool hasMarginal() { return _hasMarginal;}
    inline void setHasMarginal(bool marginal) {_hasMarginal=marginal;}

    inline ModelElement *modelVariable(unsigned long idx) {return &_modVariables[idx]; }
    inline ModelElement *modelConstraint(unsigned long idx) {return &_modConstraints[idx]; }



    /**
     * delete all data
     */
    virtual void cleanUp();

    /**
     * get count of sub data objects
     */
    virtual int subCnt()																		{ return 0; }

    /**
     * if sub data is splitted up to different parts for serialization then get count of these parts, otherwise 0
     */
    virtual int subPartCount()																	{ return 0; }

    /**
     * check if serialization to or from stream should be done for the data object
     * @param si		serialization info
     * @param data		main data object
     * @return			true if serialization should be done
     */
    virtual bool checkSerialize(MainData::SerializeInfo& si, const MainData *data);

    /**
     * write data object to output stream
     * @param si		serialization info
     * @param data		main data object
     */
    virtual void serializeTo(MainData::SerializeInfo& si, const MainData *data);

    /**
     * fill data object from input stream
     * @param si		serialization info
     * @param data		main data object
     * @param pos		position of input string, returns iterated position
     * @param subCnt	count of sub data objects
     * @param lc		line count per element or 0 if elements are len coded
     * @param rline		remaining section start line
     */
    virtual void deserializeFrom(MainData::SerializeInfo& si, const MainData *data, int subCnt, int lc, string &rline);






};


}

#endif // SOLUTION_HH
