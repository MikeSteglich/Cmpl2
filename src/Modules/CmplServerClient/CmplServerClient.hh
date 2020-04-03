
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


#ifndef CMPLSERVERCLIENT_HH
#define CMPLSERVERCLIENT_HH

/*#include <string>
#include <vector>
#include <iostream>
*/

#include "../../Control/ModuleBase.hh"


using namespace std;



namespace cmpl
{


#define SYNC_SOLVE          0;

#define ASYNC_SEND          1;
#define ASYNC_KNOCK         2;
#define ASYNC_RETRIEVE      3;
#define ASYNC_CANCEL        4;






    /**
	 * <code>TestModule</code> is only used for tests of cmpl main control.
	 * <code>TestModule</code> uses three test command line options:
	 * 	-a		boolean option without any argument
	 * 	-b		option with one argument, which must be an int number
	 * 	-c		option with arbitrary arguments
	 * beside these options there is an output control command line options:
	 *  -o		option with one file name argument, this file is used for outputs instead of <code>cout</code>
	 */
	class CmplServerClient : public ModuleBase
	{
	private:
        int _mode;
        string _serverUrl;
        string _optFileName;
        string _runOnServerScript;
        int _maxServerTries;
        int _maxServerQueuingTime;

        void readOptFile();


	public:
		/**
		 * initialize modul, to call immediately after the constructor.
		 * @param ctrl			main object
		 * @param data			data object
		 * @param name			module name (or alias)
		 */
		virtual void init(MainControl *ctrl, MainData *data, const char *name);

		/**
		 * run module function
		 */
		virtual void run();

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
	};
}

#endif // TESTMODULE_HH

