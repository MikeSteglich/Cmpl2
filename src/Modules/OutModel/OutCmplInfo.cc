
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


#include <iomanip>

#include "OutCmplInfo.hh"
#include "OutModelExtData.hh"
#include "../../Control/MainControl.hh"
#include "../../Control/ModulesConf.hh"

#include "OutModelMatrix.hh"


namespace cmpl
{
/*********** module definition **********/

MODULE_CLASS( writeCmplInfo, OutCmplInfo )



/*********** initialization **********/

/**
     * initialize modul, to call immediately after the constructor.
     * @param ctrl			main object
     * @param data			data object
     * @param name			module name (or alias)
     */
void OutCmplInfo::init(MainControl *ctrl, MainData *data, const char *name)
{
    ModuleBase::init(ctrl, data, name);

    _ctrl=ctrl;
    _data=data;

    _outCmplInfo = NULL;
    _matrixOut=false;
    _statOut = false;
    _varProdStatOut = false;;

    _matrixFileName="";
    _statFileName="";
    _varProdFileName="";
}

/**
     * destructor
     */
OutCmplInfo::~OutCmplInfo()
{
    if (_outCmplInfo)
        delete _outCmplInfo;

}


/*********** handling of command line options **********/

#define OPTION_OUT_MODEL_MATRIX           10



/**
     * register command line options options for delivery to this module
     * @param modOptReg		vector to register in
     */
void OutCmplInfo::regModOptions(vector<CmdLineOptList::RegOption> &modOptReg)
{
    ModuleBase::regModOptions(modOptReg);

    REG_CMDL_OPTION( OPTION_OUT_MODEL_MATRIX , "matrix", 0, 1, CMDL_OPTION_NEG_NO_ARG, true );

}

/**
     * parse single option from command line options, this function is called for every delivered option
     * @param ref			reference number of option registration, should be used for discriminate the options
     * @param prio			priority value of option
     * @param opt			option
     * @return				true if option is used by the module
     */
bool OutCmplInfo::parseOption(int ref, int prio, CmdLineOptList::SingleOption *opt)
{
    if (ModuleBase::parseOption(ref, prio, opt))
        return true;

    switch (ref) {
    case OPTION_OUT_MODEL_MATRIX:
        if (_outCmplInfo) {
            delete _outCmplInfo;
            _outCmplInfo = NULL;
        }
        if (!(opt->neg())) {
            //                _outCmplInfo = new FileOutput();
            //                _outCmplInfo->setFile(_data, IO_MODE_FILE, (opt->size() > 0 ? &((*opt)[0]) : NULL), IO_FILE_STANDARD_CMPLINFO, true);
            //                _outCmplInfo->setLocSrc(opt->loc(true));

            if (opt->size() > 0)
                _matrixFileName = (*opt)[0];
        }
        _matrixOut=true;
        return true;
    }

    return false;
}

/**
     * writes usage info for the module to stream
     * @param s				stream to write to
     */
void OutCmplInfo::usage(ostream& s)
{
    ModuleBase::usage(s);

    s << "  -matrix [<file>]              export model as matrix in a file or stdout" << endl;
}


/**
     * run module function
     */
void OutCmplInfo::run()
{
    _ctrl->errHandler().setExecStep("run");

    PROTO_OUTL("Start run module " << moduleName());

    _outCmplInfo = new FileOutput();

    string fName= modp()->data()->cmplFileBase() ;
    fName+=".cinf";
    _outCmplInfo->setFile(_data, IO_MODE_FILE, &fName , IO_FILE_STANDARD_CMPLINFO, true);


     //  if (_matrixOut || _statOut || _varProdStatOut) {

    if (_outCmplInfo) {
        // get model data
        _ctrl->errHandler().setExecStep("get model data");
        GET_DATA(OptModel, om);

        if (om->cols().size()==0 )
            _ctrl->errHandler().internalError("Cannot write CmplInfo file because no model has been generated");

        om->setExportOnly(false);

        if (om) {
            writeCmplInfo(om,_outCmplInfo);

        }
        else {
            _ctrl->errHandler().error(ERROR_LVL_WARN, "no generated model to write as CmplInfo" , _outCmplInfo->locSrc());
        }
    }
    //  }

    PROTO_OUTL("End run module " << moduleName());
}


/**
     * write generated model to file
     * @param om			generated model
     * @param file			output to this file
     * @param fm			use free MPS format
     */
void OutCmplInfo::writeCmplInfo(OptModel *om, FileOutput *file)
{
    try {
        PROTO_OUTL("writing CmplInfo file" << file->fileNameReplaced()) ;

        CmplOutput(cout, "Writing model instance as CmplInfo to file > " + file->fileNameReplaced());
        ostream *ostr = file->open();
        writeCmplInfo(om, *ostr);
        file->close();
    }

    catch (FileException& e) {
        _ctrl->errHandler().error(ERROR_LVL_NORMAL, _ctrl->printBuffer("%s: write model to file '%s'", e.what(), e.filename().c_str()), file->locSrc());
    }
    catch (exception& ex) {
        _ctrl->errHandler().error(ERROR_LVL_NORMAL, "write model as Matrix file error", file->locSrc(), &ex);
    }
}

/**
     * write generated model to stream
     * @param om			generated model
     * @param ostr			output to this stream
     * @param fm			use free MPS format
     */
void OutCmplInfo::writeCmplInfo(OptModel *om, ostream& ostr)
{

    PROTO_OUTL("write cmplInfo");

    ostr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?> " << endl ;
    ostr << "<CmplInfo version=\"1.0\">" << endl ;

    ostr << "\t<general>" << endl ;
    ostr << "\t\t<instancename>" << modp()->data()->cmplFileBase() << ".cmpl</instancename>" << endl ;
    ostr << "\t<general>" << endl ;

    //ToDo statistics
    if (_statOut) {
        ostr << "\t<statistics file=\"" ;
        if (_statFileName.empty())
            ostr <<  modp()->data()->cmplFileBase() << ".stat";
        else
            ostr << _statFileName ;
        ostr << "\">" << endl ;

        // here the statistics

        ostr << "\t</statistics>" << endl ;
    }

    //ToDo variable products statistics
    if (_varProdStatOut) {
        ostr << "\t<variableProducts file=\"" ;
        if (_varProdFileName.empty())
            ostr <<  modp()->data()->cmplFileBase() << ".vstat";
        else
            ostr << _varProdFileName ;
        ostr << "\">" << endl ;

        // here the statistics

        ostr << "\t</variableProducts>" << endl ;
    }


    if (_matrixOut) {
        ostr << "\t<matrix file=\"" ;
        if (_matrixFileName.empty())
            ostr <<  modp()->data()->cmplFileBase() << ".mat" ;
        else
            ostr << _matrixFileName;
        ostr << "\">" << endl ;

        if (om->isLinearModel()) {
            OutModelMatrix oMat = OutModelMatrix();
            oMat.init(_ctrl, _data, "writeMatrix");
            oMat.writeMatrix(om, ostr);
        } else {
            _ctrl->errHandler().error(ERROR_LVL_WARN, "only linear models can be written as matrix in CmplInfo" , _outCmplInfo->locSrc());
        }

        ostr << "\t</matrix>" << endl ;

    }

    ostr << "</CmplInfo>" << endl ;

    ostr <<endl;


}



}

