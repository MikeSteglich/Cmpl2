#include "Solution.hh"

#include "../Control/MainData.hh"
#include "OptModel.hh"
#include "../Control/MainControl.hh"



using namespace std;


namespace cmpl
{



DATA_CLASS( Solution );



ModelElement::ModelElement() {
    _type="";
    _name="";
    _lowerBound=0;
    _upperBound=0;
}


SolutionElement::SolutionElement() {
    _activity=0;
    _marginal=0;
    _modElement=NULL;
}



SingleSolution::SingleSolution() {
    _status="";
    _value=0;
}


double SingleSolution::calculateConActivity(OptModel *om, Solution* sol, const vector<LinearModel::Coefficient>& coeffs)  {

    double conAct=0;
    unsigned long itIdx;
    unsigned long idx;

    for (vector<LinearModel::Coefficient>::const_iterator it = coeffs.begin(); it != coeffs.end(); it++) {
        itIdx=it->idRC - 1;
        idx = sol->varMpsIdxByIdx(itIdx);

        if (om->isInteger())
            conAct +=  it->iCoeff * _variables[idx].activity();
        else
            conAct +=  it->rCoeff * _variables[idx].activity();

    }

    return conAct;
}




void Solution::getVarBounds(OptVar *ov,double &lowerBound, double &upperBound ) {

    CmplVal& lb = ov->lowBound();
    CmplVal& ub = ov->uppBound();

    double inf = std::numeric_limits<double>::infinity();

    double lBound;
    double uBound;

    switch (ov->lowBound().t) {
    case TP_REAL:
        lBound = ov->lowBound().v.r;
        uBound = ov->uppBound().v.r;
        break;

    default:
        lBound = ov->lowBound().v.i;
        uBound = ov->uppBound().v.i;
        break;
    }

    if (lb || ub) {
        if (lb)
          lowerBound=lBound;
        else
          lowerBound=-inf;

        if (ub)
          upperBound=uBound;
        else
          upperBound=inf;
    }
    else {
        lowerBound=-inf;
        upperBound=inf;
    }
}



void Solution::prepareSolutionData(string probName, string solver,  bool intRelaxation, MainData *md, ModuleBase *mb) {

    #define GET_DATA_2(n,d)		n *d = (n *)(md->data(string(#n)))
    GET_DATA_2( OptModel , om);

    _probName=probName;
    _om = om;
    _solver=solver;
    _hasMarginal=true;

    bool integerRelaxation = intRelaxation;

    unsigned long colCnt = om->cols().size();
    unsigned long rowCnt = om->rows().size();
    LinearModel *lm = om->getColModel();
    const char *mode;

    unsigned long conIdx=0;

    StringStore *sstore = mb->modp()->data()->globStrings();
    string *colNames = om->colNames(sstore, 0, '_', 100);
    string *rowNames = om->rowNames(sstore, 0, '_', 100);

    mode = lm->mode();

    const LinearModel::Coefficient *rhs;
    rhs = lm->rhs();


    _nrOfVariables=colCnt;
    _nrOfIntegerVariables=0;

    mode = lm->mode();

    double inf = std::numeric_limits<double>::infinity();

    _objName=om->objName();
    _objSense=om->objSense();

    for (unsigned long i = 0; i < rowCnt; i++, mode++, rhs++) {
        char m = *mode;
        if (m) {
            if (i != om->objIdx()) {
                ModelElement modElem;

                double bound;
                if (rhs->iCoeff!=0 || rhs->rCoeff == 0)  {

                    bound = double(rhs->iCoeff);

                } else {
                    bound = rhs->rCoeff;

                }

                if (m == 'E') {
                    modElem.setLowerBound(bound);
                    modElem.setUpperBound(bound);
                } else if (m == 'G') {
                    modElem.setLowerBound(bound);
                    modElem.setUpperBound(inf);
                } else if (m == 'L') {
                    modElem.setLowerBound(-inf);
                    modElem.setUpperBound(bound);
                } else  {
                    m='N';
                    modElem.setLowerBound(-inf);
                    modElem.setUpperBound(inf);
                }

                modElem.setName(rowNames[i]);

                string type;
                type.push_back(m);
                modElem.setType(type);

                _modConstraints.push_back(modElem);
                _rowNameMap[rowNames[i] ] = conIdx;
                _rowIdxMap[i]=conIdx;
                conIdx++;
            }
        }
    }
    _nrOfConstraints=conIdx;

    bool hasInt = false;
    unsigned long mpsIdx=0;


    for (unsigned long i = 0; i < colCnt; i++) {
        OptVar *ov = dynamic_cast<OptVar *>(om->cols()[i]);
        if (ov) {
            ModelElement modElem;
            if (ov->intVar() ) {
                hasInt = true;
                _hasMarginal=false;
                _nrOfIntegerVariables++;
            }
            else {
                modElem.setName(colNames[i]);
                modElem.setType("C");

                double lowerBound=0;
                double upperBound=0;

                getVarBounds(ov,lowerBound,upperBound);

                modElem.setLowerBound( lowerBound);
                modElem.setUpperBound( upperBound );

                _colNameMap[colNames[i] ] = mpsIdx;
                _colIdxMap[i]=mpsIdx;
               //_colSolIdxMap[mpsIdx]=i;
                mpsIdx++;
                _modVariables.push_back(modElem);
            }
        }
    }

    if (hasInt) {

        //om->setIsInteger(true);

        for (unsigned long i = 0; i < colCnt; i++) {
            OptVar *ov = dynamic_cast<OptVar *>(om->cols()[i]);
            if (ov && ov->intVar()) {
                ModelElement modElem;
                modElem.setName(colNames[i]);

                if (!integerRelaxation) {
                    if (ov->binVar())
                        modElem.setType("B");
                    else
                        modElem.setType("I");
                } else {
                    modElem.setType("C");
                }

                double lowerBound=0;
                double upperBound=0;

                getVarBounds(ov,lowerBound,upperBound);

                modElem.setLowerBound( lowerBound);
                modElem.setUpperBound( upperBound );

                _colNameMap[colNames[i] ] = mpsIdx;
                _colIdxMap[i]=mpsIdx;
               // _colSolIdxMap[mpsIdx]=i;
                mpsIdx++;
                _modVariables.push_back(modElem);
            }
        }
   }
    if (integerRelaxation) {
        hasInt = false;
        _hasMarginal=true;
        _nrOfIntegerVariables=0;
    }

}





/**
 * delete all data
 */
void Solution::cleanUp()
{
    //TODO


}


/**
 * check if serialization to or from stream should be done for the data object
 * @param si		serialization info
 * @param data		main data object
 * @return			true if serialization should be done
 */
bool Solution::checkSerialize(MainData::SerializeInfo& si, const MainData *data)
{
    //TODO
    return false;
}


/**
 * write data object to output stream
 * @param si		serialization info
 * @param data		main data object
 */
void Solution::serializeTo(MainData::SerializeInfo& si, const MainData *data)
{
    //TODO
}


/**
 * fill data object from input stream
 * @param si		serialization info
 * @param data		main data object
 * @param pos		position of input string, returns iterated position
 * @param subCnt	count of sub data objects
 * @param lc		line count per element or 0 if elements are len coded
 * @param rline		remaining section start line
 */
void Solution::deserializeFrom(MainData::SerializeInfo& si, const MainData *data, int subCnt, int lc, string &rline)
{
    //TODO
}



}
