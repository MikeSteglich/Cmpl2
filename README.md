**New beta release of CMPL v.2 available**

*Overview*
 
The CMPL team is pleased to announce the first beta version of CMPL 2. 

CMPL has been (almost) completely redeveloped and comes with a lot of new functionalities. 

Examples are improved syntax,  logical constraints, native support for SOS, the opportunity for users to write their own functions in CMPL and much more. Furthermore, CMPL has been extended with a new interactive interface to Excel. A user can read sets and parameters into the cmpl model and write results directly into an open excel file. This feature is availbale on Windows and macOS. 

In addition, pyCmpl, jCmpl and CmplServer have been revised and  extended. For example, pyCmpl is now fully ported to Python 3. Python2 is no longer supported. 

*Binaries, Examples and Manual*

The executable files for Windows, macOs and Linux, examples and the manual can be found under the following link: https://drive.google.com/drive/folders/1y5tSNsdcbm9ush6wkO_RhMU5kh12BifD

The binaries will be continuously updated with bug fixes until the beta phase ends.

It would be great if you could test this version and report any errors. Please use the CMPL mailing list or report a issue at https://github.com/MikeSteglich/Cmpl2/issues. 

*Installation*

Under Linux and Windows, installation is not required after unpacking the ZIP or tar.gz file. The CMPL package works out of the box in any folder. 

On macOS, a user must double-click the downloaded DMG file in the Finder. This disc image file contains a folder Cmpl2, which has to be copied into the folder Applications via drag-and-drop in the Finder. Then the cmplSetup script must be executed by double-clicking on the icon and a message window appears with "Cmpl setup has finished". 


*Source code*

The source code is available on Github:

https://github.com/MikeSteglich/Cmpl2
  
https://github.com/MikeSteglich/Coliop

https://github.com/MikeSteglich/pyCmpl3

https://github.com/MikeSteglich/jCmpl


**CMPL**

CMPL (<Coliop|Coin> Mathematical Programming Language) is a mathematical programming language 
and a system for mathematical programming and optimization of linear optimization problems. 

The CMPL syntax is similar in formulation to the original mathematical model but also 
includes syntactic elements from modern programming languages. CMPL is intended to combine 
the clarity of mathematical models with the flexibility of programming languages. 

CMPL executes CBC, GLPK, SCIP, Gurobi and CPLEX directly to solve the generated model 
instance. Since it is also possible to transform the mathematical problem into MPS, 
and Free-MPS, alternative solvers can be used. 

CMPL is an open source project licensed under GPL. It is written in C++ and is available 
for most of the relevant operating systems (Windows, OS X and Linux). 
CMPL is a COIN-OR project initiated by the Technical University of Applied Sciences Wildau 
and the Institute for Operations Research and Business Management at the Martin Luther 
University Halle-Wittenberg.

This version is still under development. Please use CMPL 1.12 until a first stable version of CMPL 2 is released.

