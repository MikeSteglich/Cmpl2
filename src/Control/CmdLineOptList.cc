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


#include "CmdLineOptList.hh"
#include "MainControl.hh"
#include "ModulesConf.hh"
#include "MainData.hh"


namespace cmpl
{
	/***********************************************************************
	 *  Usage example:
	 *
	 *  {
	 *  	cmpl::CmdLineOptList *cl = cmpl::Start::getNewEmptyCmdLineOptList();
	 *  	cmpl::PositionInfo p1(...), p2(...);
	 *		cl->addOption("i", p1)->arg("abc.cmpl", p2);
	 *
	 * 		...
	 *
	 * 		cmpl::Start::dispose(cl);
	 *	}
	 ***********************************************************************/


	/* **************** SingleOption ************* */

	/**
	 * set option name
	 * @param n			option name, can be "[module.][no-]option[!...][=arg1,...]"
	 * @param pos		start position of the option, only for error messages
	 */
	void CmdLineOptList::SingleOption::setOpt(string& n, PositionInfo& pos)
	{
		size_t p;
		int pe = (pos.useCharCount() ? n.size() : (pos.useWordCount() ? 1 : 0));
		int pc = pe;
		string o = (!n.empty() && n[0] == '-' ? n.substr(1) : n);

		// test module specification
		if ((p = o.find(".")) != string::npos) {
			_module = o.substr(0, p);
			o = o.substr(p+1);
		}
		else {
			_module.clear();
		}

		// test negation
		_neg = false;
		if (o.size() > 3 && o.substr(0, 3) == "no-") {
			_neg = true;
			o = o.substr(3);
		}

		// test arguments
		if ((p = o.find("=")) != string::npos) {
			if (pos.useCharCount())
				pc -= (o.size() - p);

			PositionInfo posA = (pos.useCharCount() ? pos + (pc + 1) : pos);

			_opt = o.substr(0, p);
			string a = o.substr(p+1);

			_sepArgStart = 1;

			while ((p = a.find(",")) != string::npos) {
				string b = a.substr(0, p);
				arg(b, posA);

				a = a.substr(p+1);
				_sepArgStart++;

				if (pos.useCharCount())
					posA += (p + 1);
			}

			arg(a, posA);
		}
		else {
			_opt = o;
		}
		
		// test explicit priority
		_prio = 0;
		while (_opt.size() > 1 && _opt[_opt.size() - 1] == '!') {
			_prio++;
			_opt.erase(_opt.size() - 1);
		}

		// set location
		_locName = LocationInfo(pos, pos+pc);
		_locOpt = (pc==pe ? _locName : LocationInfo(pos, pos+pe));
	}


	/**
	 * check whether this option is equal to another option
	 * @param o			other option
	 * @return			true if options are equal
	 */
	bool CmdLineOptList::SingleOption::isEqual(CmdLineOptList::SingleOption& o)
	{
		// compare all instance variables, but not _useCount
		if (_opt != o._opt || _module != o._module
				|| _neg != o._neg || _prio != o._prio || _sepArgStart != o._sepArgStart
				|| _args.size() != o._args.size()
				|| _locName != o._locName || _locOpt != o._locOpt)
			return false;

		if (_args.size() > 0) {
			vector<string>::iterator it = _args.begin();
			vector<string>::iterator it2 = o._args.begin();
			for (; it != _args.end(); it++, it2++) {
				if (*it != *it2)
					return false;
			}
		}

		return true;
	}


	/**
	 * add an arg for an option
	 * @param a			argument (can also contain spaces)
	 * @param pos		start position of the arg, only for error messages
	 * @return			this
	 */
	CmdLineOptList::SingleOption* CmdLineOptList::SingleOption::arg(string& a, PositionInfo& pos)
	{
		_args.push_back(a);
		_argPos.push_back(pos);

		//_locOpt = _locOpt + LocationInfo(pos + (pos.useCharCount() ? a.size() : (pos.useWordCount() ? 1 : 0)));
		_locOpt += (pos + (pos.useCharCount() ? a.size() : (pos.useWordCount() ? 1 : 0)));
		return this;
	}

	/**
	 * get an argument as int number, error if arg is not an int.
	 * @param i			index
	 */
	int CmdLineOptList::SingleOption::argAsInt(size_t i, MainControl *ctrl)
	{
		int res = 1;

		try {
			res = stoi(_args[i]);
		}
		catch (exception) {
			ctrl->errHandler().error(ERROR_LVL_NORMAL, ctrl->printBuffer("argument '%s' for option '%s' is not an int number", _args[i].c_str(), _opt.c_str()), _locOpt);
		}	

		return res;
	}

	/**
	 * test whether option is valid for names in <code>modNames</code>
	 * @param modNames  relevant names for module specification in command line options
	 * @return          option is valid with this level of module specification / -1: not valid for the module
	 */
	int CmdLineOptList::SingleOption::testModName(vector<const char *> &modNames)
	{
		if (_module.empty())
			return 0;

		int lvl = 1;
		for (vector<const char *>::iterator it = modNames.begin(); it != modNames.end(); it++, lvl++) {
			if (_module == *it)
				return lvl;
		}

		return -1;
	}



	/* **************** CmdLineOptList ************* */

	/**
	 * clean up this object
	 */
	void CmdLineOptList::cleanUp()
	{
		for (size_t i = 0; i < _opts.size(); i++)
			delete _opts[i];
		_opts.clear();

		if (_modConf) {
			delete _modConf;
			_modConf = NULL;
		}

        _binFullName.clear();
	}

	/**
	 * fill this with command line options as supplied from main()
	 */
	void CmdLineOptList::fillFromMain(int argc, char *argv[])
	{
		PositionInfo pos(POSITION_TYPE_WORDARR, "command line");
		SingleOption *sa = NULL;

        if (argc > 0)
            _binFullName = argv[0];

		for (int i = 1; i < argc; i++) {
			string arg = argv[i];
			pos.set(i);

			if (arg[0] == '-')
				sa = addOption(arg, pos, true);
			else if (sa)
				sa->arg(arg, pos);
            else {
                string o = "i";
                sa = addOption(o, pos, true)->arg(arg, pos);
            }
		}
	}

	/**
	 * add a new option to this
	 * @param opt		option string, the option can have several args separated by spaces
	 * @param pos		start position of option, only for error messages
	 * @param single	<code>opt</code> contains only of one single option keyword without args
	 * @return			info object for the option
	 */
	CmdLineOptList::SingleOption* CmdLineOptList::addOption(string& opt, PositionInfo& pos, bool single)
	{
		if (opt.empty())
			return NULL;

		// iterate over words in opt
		size_t wn = 0;
		string word;
		bool quote;
		SingleOption *sa = NULL;
		PositionInfo posA = pos;

		while ((single && !sa) || (!single && StringStore::iterWords(opt, word, wn, quote))) {
			if (single)
				word = opt;
			else if (pos.useCharCount())
				posA = pos + ((wn == string::npos ? opt.size() : wn) - word.size());

			if (!sa || (!quote && word.size() >= 2 && word[0] == '-')) {
				// start of new option
				sa = new CmdLineOptList::SingleOption(this);
				sa->setOpt(word, posA);

				_opts.push_back(sa);
			}
			else {
				// arg for the option
				sa->arg(word, posA);
			}

			if (pos.useWordCount())
				posA += 1;
		}

		return sa;
	}

	/**
	 * delete an option from this, including its args
	 * @param optInfo	info object for the option
	 * @return			true if the option is found and deleted
	 */
	bool CmdLineOptList::delOption(CmdLineOptList::SingleOption* optInfo)
	{
		if (optInfo && optInfo->_cmdLineOptList == this) {
			for (size_t i = 0; i < _opts.size(); i++) {
				if (_opts[i] == optInfo) {
					_opts.erase(_opts.begin() + i);
					delete optInfo;
					return true;
				}
			}
		}

		return false;
	}


	/**
	 * append command line options from another CmdLineOptList object
	 * @param src      source of command line options to append
	 */
	void CmdLineOptList::append(CmdLineOptList& src)
	{
		for (size_t i = 0; i < src._opts.size(); i++) {
			CmdLineOptList::SingleOption *sa = new CmdLineOptList::SingleOption(*(src._opts[i]));
			sa->_cmdLineOptList = this;
			_opts.push_back(sa);
		}
	}
			 

	/**
	 * iterate to the first or next relevant option
     * @param modNames  relevant names for module specification in command line options / NULL: don't check module name
	 * @param iter      current iteration index, start with -1
	 * @param modspec	return level of module specification
	 * @return          next option or NULL if no one is left
	 */
    CmdLineOptList::SingleOption* CmdLineOptList::iterOptions(vector<const char *> *modNames, int &iter, int &modspec)
	{
		if (iter < 0)
			iter = -1;

		for (iter++; iter < (int)_opts.size(); iter++) {
            if (!modNames || (modspec = _opts[iter]->testModName(*modNames)) >= 0)
				return _opts[iter];
		}

		return NULL;
	}


	/**
	 * check if all options in _opts are used by modules
	 * @param ctrl      main object
	 */
	void CmdLineOptList::checkCmdLineOptUsed(MainControl *ctrl)
	{
		for (size_t i = 0; i < _opts.size(); i++) {
			if (_opts[i]->_useCount == 0) {
				ctrl->outWarnUnusedCmdLineOpt(_opts[i]);
			}
		}
	}


	/****** functions for serialization ****/

	/**
	 * insert strings and locations used from this in the data object
	 */
	void CmdLineOptList::insertStringsAndLocs(MainData *data)
	{
		StringStore *s = data->globStrings();

		for (vector<SingleOption *>::iterator it = _opts.begin(); it != _opts.end(); it++) {
			SingleOption *opt = *it;

			s->store(opt->_opt);
			s->store(opt->_module);

			opt->_locName = data->persistentLocation(opt->_locName);
			data->searchInsertInGlobLocs(&(opt->_locName));

			opt->_locOpt = data->persistentLocation(opt->_locOpt);
			data->searchInsertInGlobLocs(&(opt->_locOpt));

			for (vector<string>::iterator its = opt->_args.begin(); its != opt->_args.end(); its++) {
				s->store(*its);
			}

			for (vector<PositionInfo>::iterator itl = opt->_argPos.begin(); itl != opt->_argPos.end(); itl++) {
				data->persistentPosition(*itl);
				LocationInfo loc(*itl);
				data->searchInsertInGlobLocs(&loc);
			}
		}
	}

	/**
	 * write data object to output stream
	 * @param si		serialization info
	 * @param data		main data object
	 */
	void CmdLineOptList::serializeTo(MainData::SerializeInfo& si, const MainData *data)
	{
		StringStore *s = data->globStrings();
		int i = 0;

		for (vector<SingleOption *>::iterator it = _opts.begin(); it != _opts.end(); it++) {
			SingleOption *opt = *it;

			if (si.lineNums)
				(*si.ostr) << i++ << '#';

			(*si.ostr) << s->search(opt->_opt) << ';' << s->search(opt->_module) << ';' << 
                data->searchLoc(si, &(opt->_locName)) << ';' << data->searchLoc(si, &(opt->_locOpt)) << ';' <<
				(opt->_neg ? 1 : 0) << ';' << opt->_prio << ';' << opt->_sepArgStart << ';' << opt->_useCount << ';' <<
				opt->_args.size();

			vector<string>::iterator its = opt->_args.begin();
			vector<PositionInfo>::iterator itl = opt->_argPos.begin();
			for (; its != opt->_args.end(); its++, itl++) {
				LocationInfo loc(*itl);
                (*si.ostr) << ';' << s->search(*its) << ';' << data->searchLoc(si, &loc);
			}

			(*si.ostr) << endl;
		}
	}

	/**
	 * fill data object from input stream
	 * @param si		serialization info
	 * @param data		main data object
	 * @param subCnt    count of sub data objects
	 */
	void CmdLineOptList::deserializeFrom(MainData::SerializeInfo& si, const MainData *data, int subCnt)
	{
		string line;

		for (int i = 0; i < subCnt; i++) {
			// read option line from serialization stream
			getline(*si.istr, line);
			if (!si.istr->good())
				throw MainDataInputException("unexpected end of file or read error", *si.pos);

			if (si.lineNums)
				MainData::getNextLong(line, si.pos);

			SingleOption *opt = new SingleOption(this);
			opt->_opt = data->globStrings()->at(si.mapStrings[MainData::getNextLong(line, si.pos)]);
			opt->_module = data->globStrings()->at(si.mapStrings[MainData::getNextLong(line, si.pos)]);
            opt->_locName = *(si.mapLocsFrom[MainData::getNextLong(line, si.pos)]);
            opt->_locOpt = *(si.mapLocsFrom[MainData::getNextLong(line, si.pos)]);
			opt->_neg = (MainData::getNextLong(line, si.pos) != 0);
			opt->_prio = MainData::getNextLong(line, si.pos);
			opt->_sepArgStart = MainData::getNextLong(line, si.pos);
			opt->_useCount = MainData::getNextLong(line, si.pos);

			unsigned ac = MainData::getNextLong(line, si.pos);
			if (ac > 0) {
				opt->_args.reserve(ac);
				opt->_argPos.reserve(ac);

				for (unsigned a = 0; a < ac; a++) {
					opt->_args.push_back(string(data->globStrings()->at(si.mapStrings[MainData::getNextLong(line, si.pos)])));
                    opt->_argPos.push_back(si.mapLocsFrom[MainData::getNextLong(line, si.pos)]->begin());
				}
			}

			// check if option already exists
			SingleOption *o = NULL;
			for (vector<SingleOption *>::iterator it = _opts.begin(); it != _opts.end(); it++) {
				if ((*it)->isEqual(*opt)) {
					o = *it;
					break;
				}
			}

			if (o) {
				// option already exists
				if (o->_useCount < opt->_useCount)
					o->_useCount = opt->_useCount;

				delete opt;
			}
			else {
				// insert option
				_opts.push_back(opt);
			}

			si.pos->addLines();
		}
	}

}

