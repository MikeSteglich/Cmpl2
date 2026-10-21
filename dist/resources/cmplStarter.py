# ***********************************************************************
#  This code is part of pyCMPL
#
#  Copyright (C) 
#  Mike Steglich - Technical University of Applied Sciences
#  Wildau, Germany
#
#  pyCMPL is a project of the Technical University of
#  Applied Sciences Wildau and the Institute for Operations Research
#  and Business Management at the Martin Luther University
#  Halle-Wittenberg.
#  Please visit the project homepage <www.coliop.org>
#
#  pyCMPL is free software; you can redistribute it and/or modify it
#  under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
#
#  pyCMPL is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
#  License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with this program; if not, see <http://www.gnu.org/licenses/>.
#
# **********************************************************************

import sys
import os
#import traceback #only for debugging
import subprocess
import tempfile


from pyCmpl import *


isError=False
debugMode=False
outAlias = sys.argv[1]

def delTmpFiles(debug=False):
	if not debug:
		os.remove(outAlias+".optcmpl")
		os.remove(outAlias+".precmpl")
		os.remove(outAlias+".extdata")

try:
	if not os.path.exists(outAlias+".optcmpl"):
		raise CmplException("Cannot read opt file"  )

	if not os.path.exists(outAlias+".precmpl"):
		raise CmplException("Cannot read precompiler file"  )

	if not os.path.exists(outAlias+".extdata"):
		raise CmplException("Cannot read external data file"  )

	args=CmplArgs(outAlias+".optcmpl")
	args.parseOptFile()
	msgFile=args.msgFile

	

	if args.runMode == CMPL_LOCAL and not args.xlsDataFile:
		cmplCmd="\""+os.getenv('CMPLHOME')+"bin"+os.sep+"cmpl\" -i-opt "+outAlias+".optcmpl "+"-i-pre "+outAlias+".precmpl "+"-i-extern "+outAlias+".extdata -modules woPreComp -silent-start"
		subprocess.Popen(cmplCmd, shell=True).wait()

	else:
		model = Cmpl(args.cmplFile, args)
		#model.debug()

		model.setOutput(not args.isSilent,"")

		if args.xlsDataFile and args.runMode in ( CMPL_LOCAL, CMPL_REMOTE_SOLVE, CMPL_REMOTE_SEND): 

			if args.isDisplayOpt:
				raise CmplException("ERROR: Display options are not allowed when using CmplXlsData")

			model.setXlsDataFile(args.xlsDataFile)

			if args.runMode==CMPL_LOCAL:
				isCmplFullPath = (args.cmplFile.startswith(os.sep) or args.cmplFile[1:2] == ":")
				isCmplXlsDataFullPath =  (args.xlsDataFile.startswith(os.sep) or args.xlsDataFile[1:2] == ":")

				xlsDataFileFullName=""
				if isCmplFullPath and not isCmplXlsDataFullPath:
					basePath = os.path.dirname(args.cmplFile)+os.sep 
					xlsDataFileFullName = basePath + args.xlsDataFile
					baseName = os.path.splitext(os.path.basename(args.baseName))[0] 
					xlsDataFileAlias = basePath+baseName+"__"+next(tempfile._get_candidate_names())+"_.cdat"
				else:
					xlsDataFileFullName = args.xlsDataFile
					xlsDataFileAlias=args.baseName+"__"+next(tempfile._get_candidate_names())+"_.cdat"
		
				model.setOption("-filealias "+xlsDataFileFullName+"="+xlsDataFileAlias)
				model.setDataFile(xlsDataFileAlias)

		if args.runMode in (CMPL_REMOTE_SOLVE,CMPL_REMOTE_SEND) and not args.url:
			raise CmplException("ERROR: Url of the CmplServer is not defined")
			
		if args.runMode in (CMPL_REMOTE_KNOCK , CMPL_REMOTE_RETRIEVE, CMPL_REMOTE_CANCEL) and not args.url:
			print ("WARNING: The newly defined URL of the CmplServer was ignored and the original was used.\n")

		model.setOption("-mark-used xlsdata url send knock retrieve cancel maxtries maxtime")

		if args.runMode in ( CMPL_LOCAL, CMPL_REMOTE_SOLVE):			
			if args.runMode==CMPL_REMOTE_SOLVE:
				if args.isFileOut:
					raise CmplException("ERROR: CmplServer cannot be used with -m, -fm, -p or -matrix")

				model.setMaxServerQueuingTime(args.maxTime)
				model.setMaxServerTries(args.maxTries)
				model.connect(args.url)
			else:
				model.setOption("-i-opt "+outAlias+".optcmpl")
				model.setOption("-i-pre "+outAlias+".precmpl")
				model.setOption("-i-extern "+outAlias+".extdata")
				model.setOption("-modules woPreComp")
				model.setOption("-silent-start")

			model.solve()
		
		elif args.runMode ==  CMPL_REMOTE_SEND:
			model.setOutput(True, "")
			model.setMaxServerQueuingTime(args.maxTime)
			model.setMaxServerTries(args.maxTries)
			model.connect(args.url)
			model.send()
			model.dump()
		
		elif args.runMode ==  CMPL_REMOTE_KNOCK:
			model.load()
			model.knock()
			model.dump()
			
		elif args.runMode == CMPL_REMOTE_RETRIEVE:
			model.load()
			model.retrieve()
					
		elif args.runMode == CMPL_REMOTE_CANCEL:
			model.load()
			model.cancel()
			print("CMPL: Problem has been canceled ...")

		if model.cmplStatus==CMPL_WARNINGS:
			for m in model.cmplMessages:
				print(m.type, m.location, m.description)

		if args.runMode in (  CMPL_REMOTE_SOLVE, CMPL_REMOTE_RETRIEVE):
			if model.solverStatus == SOLVER_OK:
				if not (args.solFile or args.solCsvFile or args.solAsciiFile ):
					model.solutionReport()
				if args.solFile:
					model.saveSolution(args.solFile)
				if args.solAsciiFile:
					model.saveSolutionAscii(args.solAsciiFile)
				if args.solCsvFile:
					model.saveSolutionCsv(args.solCsvFile)

			if args.msgFile:
				model.saveCmplMessageFile(args.msgFile)

		debugMode=model.isDebug

	delTmpFiles(debugMode)
					
except CmplException as e:	
	print(e.msg)
	#traceback.print_exc(file=sys.stdout)
	delTmpFiles(debugMode)
	
except IOError as e:
	print(str(sys.exc_info()[1]))
	#traceback.print_exc(file=sys.stdout)
	delTmpFiles(debugMode)
	
except: 
	isError=True
	print(str(sys.exc_info()[1]))
	#traceback.print_exc(file=sys.stdout)
	delTmpFiles(debugMode)
	