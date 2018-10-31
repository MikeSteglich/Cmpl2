/***********************************************************************
 *  This code is part of CMPL
 *
 *  Copyright (C) 2007, 2008, 2009, 2010, 2011 Thomas Schleiff - Halle(Saale),
 *  Germany and Mike Steglich - Technical University of Applied Sciences
 *  Wildau, Germany 
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


#include "StringStore.hh"
#include "MainControl.hh"


namespace cmpl
{
	/**
	 * constructor
     * @param addEmpty  add empty string as first string to the string store
     */
    StringStore::StringStore(bool addEmpty)
	{
		init();

        if (addEmpty)
            storeInd("");
	}

	/**
	 * destructor
	 */
	StringStore::~StringStore()
	{
		clear();
	}

    /**
     * initialize new string store
     */
    void StringStore::init()
    {
        _modp = NULL;
        _strings_ind = NULL;
        _strings_sort = NULL;
        _index = NULL;
        _cap = _len = 0;
    }

	/**
	 * remove all strings from the string table
	 */
	void StringStore::clear()
	{
		if (_cap > 0) {
			for (unsigned i = 0; i < _len; i++) {
				delete _strings_ind[i];
			}

			delete _strings_ind;
			delete _strings_sort;
			delete _index;
		}

		init();
	}

	/**
	 * search and insert a string to the string store.
	 * @param glvar         main execution object
	 * @param str           input string
	 * @param free          free original string (or don't copy it when inserting, so it is freed in the destructor)
	 * @param insert		insert if not found
	 * @param found         return if string <code>str</code> is found (true) or new inserted (false)
	 * @return              reference number of the string
	 */
    unsigned StringStore::searchInsert(const char *str, bool free, bool insert, bool &found)
	{
		unsigned i, iu, io;
		int comp;
		const char *s;

		//PROTO_OUTL("  string store: " << _name);

		// search the string
		iu = i = 0;
		if (_len > 0) {
			io = _len - 1;

			while (iu <= io)
			{
				i = (io + iu) / 2;
				comp = strcmp(str, _strings_sort[i]);
				if (comp == 0)
				{
					//PROTO_OUTL("    found string '" << str << "' as #" << i);
					if (free)
						delete str;

					found = true;
					return _index[i];
				}

				if (comp > 0)
					iu = i + 1;
				else if (i > 0)
					io = i - 1;
				else
					break;
			}
		}

		// string not found
		found = false;
		if (!insert)
			return 0;

		// insert string at position iu
		if (_len == _cap) {
			// grow the arrays
			unsigned newcap = ARR_NEWCAP(_cap);
			PROTO_OUTL("    grow strings array from " << _cap << " to " << newcap);
			_cap = newcap;

			ARR_REALLOC(_strings_ind, const char *, _len, _cap);
			ARR_REALLOC(_strings_sort, const char *, _len, _cap);
			ARR_REALLOC(_index, unsigned, _len, _cap);
		}

		// move array content if necessary
		if (iu < _len) {
			memmove(_strings_sort + iu + 1, _strings_sort + iu, sizeof(char *) * (_len - iu));
			memmove(_index + iu + 1, _index + iu, sizeof(unsigned) * (_len - iu));
		}

		// copy string if necessary
		if (!free) {
			char *s1 = new char[strlen(str) + 1];
			strcpy(s1, str);
			s = s1;
		}
		else {
			s = str;
		}

		PROTO_OUTL("    insert string '" << s << "' as #" << _len);

		// insert string
		_strings_ind[_len] = s;
		_strings_sort[iu] = s;
		_index[iu] = _len++;

		return (_len-1);
	}

	/**
	 * merge contents of a second string store to this.
	 * @param ss2			second string store
	 * @param mr			map to insert mapping for the reference numbers of merged strings
	 * @param mc			map to insert mapping for the char pointers of merged strings
	 * @return				count of strings inserted in this
	 */
	unsigned StringStore::merge(StringStore& ss2, map<unsigned, unsigned>& mr, map<const char *, const char *>& mc)
	{
		const char *cs;
		unsigned rs, rd;
		bool found;
		unsigned res = 0;

		for (rs = 0; rs < ss2.size(); rs++) {
			cs = ss2[rs];
			rd = searchInsert(cs, false, true, found);
			if (!found)
				res++;

			mr[rs] = rd;
			mc[cs] = at(rd);
		}

		return res;
	}

    string StringStore::replaceAll(const string& str, const string& targ, const string& repl)
    {
        string tmpStr=str;
        if ( targ.empty() || repl.empty() )
              return tmpStr;

        size_t idx = 0;
        while (true) {
            idx = tmpStr.find( targ, idx);
            if (idx == string::npos)
                break;

            tmpStr.replace( idx, targ.length(), repl);

            idx += repl.length();
        }
        return tmpStr;
    } // end replaceString

    bool StringStore::stringEndsWith(string str, string end) {
        if (str.length()<end.length())
            return false;
        else
           return  ( str.substr(str.length()-end.length() ) == end );
    } // end stringEndsWith


    void StringStore::getOptionValue(const string& str, string& key, string& val) {
        istringstream iss(str);

        iss >> key;
        iss >> val;

        key = StringStore::lrTrim(key);
        val =StringStore::lrTrim(val);

    }



    void StringStore::split(const string& str, vector<string>& strVec, const char *sep ) {

        string entry;
        size_t pn = 0;

        while (StringStore::iterWords(str, entry, pn, sep)) {
            entry = StringStore::lrTrim(entry);
            strVec.push_back(entry);
        }

    }

    bool StringStore::toInt(const string& str, int& t) {
        string tmpStr=StringStore::lrTrim(str);
        if (tmpStr.find_first_not_of("0123456789-e")!=string::npos)
            return false;
        stringstream sStr(tmpStr);
        return !( (sStr >> t).fail() );

    }

    bool StringStore::toLong(const string& str, long& t ) {
        string tmpStr=StringStore::lrTrim(str);
        if (tmpStr.find_first_not_of("0123456789-e")!=string::npos)
            return false;
        stringstream sStr(tmpStr);
        return !( (sStr >> t).fail() );

    }

    bool StringStore::toDouble(const string& str, double& t ) {
        string tmpStr=StringStore::lrTrim(str);
        if (tmpStr.find_first_not_of("0123456789.-+e")!=string::npos)
            return false;
        stringstream sStr(tmpStr);
        return !( (sStr >> t).fail() );
    }

    void StringStore::cleanDoubleQuotes(string &str) {
        size_t firstQuote, lastQuote;
        if ((firstQuote=str.find_first_of("\""))!=string::npos)
            if ((lastQuote=str.find_last_of("\""))!=string::npos)
                str=str.substr(firstQuote+1,lastQuote-firstQuote-1);
        // str=str.substr(firstQuote+1,lastQuote-1);
    }

    /**
	 * iterates over words in a string, on each call the next word is given back, with regarding of quotes
	 * @param str       string to iterate over
	 * @param word      return of next word
	 * @param pos       current position in string, start iteration with 0
	 * @param quote     return if the word was quoted
	 * @param qc        quote char / '\0' no quote char
	 * @param sep       separating chars
	 * @return          false if no more word found
	 */
    bool StringStore::iterWords(const string& str, string& word, size_t& pos, bool& quote, char qc, const char *sep)
	{
		size_t start, end;
		bool dquote = false;

		// start of next word
		if (pos != string::npos)
			pos = str.find_first_not_of(sep, pos);

		if (pos == string::npos) {
			word.clear();
			return false;
		}

		quote = (qc != '\0' && qc == str[pos]);

		// end of next word
		if (!quote) {
			start = pos;
			end = str.find_first_of(sep, start);
		}
		else {
			start = pos + 1;
			end = 0;

			while (end == 0) {
				pos = str.find(qc, pos+1);

				if (pos == string::npos) {
					// no closing quote
					end = string::npos;
				}
				else if (pos == str.size() - 1 || str[pos+1] != qc) {
					// closing quote ending the word
					end = pos - 1;
				}
				else {
					// double quote is treated as one quote in the result word
					if (!dquote)
						word = str.substr(start, pos + 1 - start);
					else
						word += str.substr(start, pos + 1 - start);

					dquote = true;
					start = pos + 2;
					pos++;
				}
			}
		}

		// get next word
		if (!dquote)
			word = str.substr(start, (end==string::npos ? string::npos : (end - start)));
		else
			word += str.substr(start, (end==string::npos ? string::npos : (end - start)));

		// if not quoted search for a quote inside of the word
		if (!quote && qc != '\0') {
			pos = word.find(qc);
			if (pos != string::npos) {
				// word ends before the quote
				word = word.substr(0, pos);
				end = start + pos;
			}
		}

		pos = (end==string::npos ? string::npos : (quote ? end + 1 : end));

		return true;
	}



    /**
     * return a string suitable as name
     * @param str		source string
     * @param rplSp		replacement char for space, 0 for removing spaces, space char for leaving spaces unchanged
     * @param mLen		max length for result name
     * @return
     */
    string StringStore::asName(const string& str, char rplSp, unsigned mLen)
    {
        if (rplSp != ' ') {
            const string& ws = whiteSpaces();
            size_t pos = str.find_first_of(ws);

            if (pos != string::npos) {
                string s = str;
                while (pos != string::npos && pos < mLen) {
                    if (rplSp)
                        s[pos++] = rplSp;
                    else
                        s.erase(pos, 1);

                    pos = s.find_first_of(ws, pos);
                }

                if (s.length() > mLen)
                    s = s.substr(0, mLen);

                return s;
            }
        }

        if (str.length() > mLen)
            return str.substr(0, mLen);

        return str;
    }
}

