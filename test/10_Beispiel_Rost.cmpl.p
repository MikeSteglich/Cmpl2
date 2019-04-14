initialize module names from file: .modules
    grow strings array from 0 to 30
    insert string 'test' as #0
    insert string 'compatSymbols' as #1
    insert string 'mathFunctions' as #2
    insert string 'inputFunctions' as #3
    insert string 'classFunctions' as #4
    insert string 'externDataFile' as #5
    insert string 'solverSelect' as #6
    insert string 'boundRow' as #7
    insert string 'linearConstantRow' as #8
    insert string 'linearLogCon' as #9
    insert string 'linearVarProd' as #10
    insert string 'linearSos' as #11
    insert string 'serialize' as #12
    insert string 'transferToServer' as #13
    insert string 'transferFromClient' as #14
    insert string 'transferToClient' as #15
    insert string 'transferFromServer' as #16
    insert string 'precompile' as #17
    insert string 'compile' as #18
    insert string 'interpret' as #19
    insert string 'writeMps' as #20
    insert string 'writeMatrix' as #21
    insert string 'solverCbc' as #22
    insert string 'solverGlpk' as #23
    insert string 'solverCplex' as #24
    insert string 'solverGurobi' as #25
    insert string 'solverScip' as #26
    insert string 'solutionReportAscii' as #27
    insert string 'solutionReportCsv' as #28
    insert string 'solutionReportXml' as #29
    grow strings array from 30 to 60
    insert string '<default>' as #30
    insert string 'default' as #31
    insert string 'cplex' as #32
    insert string 'gurobi' as #33
    insert string 'scip' as #34
    insert string 'script' as #35
    insert string 'client' as #36
    insert string 'server' as #37
    insert string 'check-only' as #38
    insert string 'code' as #39
    insert string 'precomp' as #40
parse regular command line options, including module names
    grow strings array from 0 to 30
    insert string 'p' as #0
parseOption module _MainControl_: p (1): 12288
 setOptionPrio p: 12288
    insert string 'i' as #41
    insert string 'm' as #42
    insert string 'p' as #43
insert module aggregation: <default>
insert module aggregation: default
insert module: compatSymbols
insert module: mathFunctions
insert module: inputFunctions
insert module: classFunctions
insert module: externDataFile
insert module: solverSelect
insert module: boundRow
insert module: linearSos
insert module: linearVarProd
insert module: linearConstantRow
insert module: linearLogCon
insert module: precompile
insert module: transferToServer
insert module: compile
insert module: interpret
insert module: writeMps
insert module: writeMatrix
insert module: solverCbc
insert module: solverGlpk
insert module: solverCplex
insert module: solverGurobi
insert module: solverScip
insert module: solutionReportAscii
insert module: solutionReportCsv
insert module: solutionReportXml
start iterating over modules
construct module class: compatSymbols
parse command line options for module: compatSymbols
 setOptionPrio p: 12288
run module: compatSymbols
    insert string 'compatSymbols' as #2
    insert string 'cmpl' as #3
Start run compatSymbols module compatSymbols
register extension:  compatSymbols: compile (4308615776) 201 1 (1)
End run compatSymbols module compatSymbols
delete module class after run: compatSymbols
construct module class: mathFunctions
parse command line options for module: mathFunctions
 setOptionPrio p: 12288
run module: mathFunctions
    insert string 'mathFunctions' as #4
Start run mathFunctions module mathFunctions
register extension:  mathFunctions: compile (4308615776) 201 2 (1)
register extension:  mathFunctions: interpret (4308616688) 301 2 (18)
End run mathFunctions module mathFunctions
delete module class after run: mathFunctions
construct module class: inputFunctions
parse command line options for module: inputFunctions
 setOptionPrio p: 12288
run module: inputFunctions
    insert string 'inputFunctions' as #5
Start run inputFunctions module inputFunctions
register extension:  inputFunctions: compile (4308615776) 201 20 (1)
register extension:  inputFunctions: interpret (4308616688) 301 20 (2)
End run inputFunctions module inputFunctions
delete module class after run: inputFunctions
construct module class: classFunctions
    insert string 'class' as #6
parse command line options for module: classFunctions
 setOptionPrio p: 12288
run module: classFunctions
    insert string 'classFunctions' as #7
Start run classFunctions module classFunctions
register extension:  classFunctions: compile (4308615776) 201 22 (1)
register extension:  classFunctions: interpret (4308616688) 301 22 (6)
End run classFunctions module classFunctions
delete module class after run: classFunctions
construct module class: externDataFile
parse command line options for module: externDataFile
 setOptionPrio p: 12288
run module: externDataFile
    insert string 'externDataFile' as #8
Start run DataImportBaseMod module externDataFile
register extension:  externDataFile: precompile (4308615264) 101 1 (1)
register extension:  externDataFile: interpret (4308616688) 321 1 (1)
register extension:  externDataFile: precompile (4308615264) 100 1 (1)
register extension:  externDataFile: precompile (4308615264) 100 1 (1)
register extension:  externDataFile: precompile (4308615264) 111 1 (1)
register extension:  externDataFile: interpret (4308616688) 300 1 (1)
End run DataImportBaseMod module externDataFile
delete module class after run: externDataFile
construct module class: solverSelect
parse command line options for module: solverSelect
 setOptionPrio p: 12288
run module: solverSelect
    insert string 'solverSelect' as #9
Start run solverSelect module solverSelect
    insert string 'solversel.opt' as #10
register extension:  solverSelect: interpret (4308616688) 371 28 (1)
register extension:  solverSelect: interpret (4308616688) 300 28 (1)
register extension:  solverSelect: interpret (4308616688) 300 28 (1)
End run solverSelect module solverSelect
delete module class after run: solverSelect
construct module class: boundRow
    insert string '__' as #11
    insert string '_' as #12
parse command line options for module: boundRow
 setOptionPrio p: 12288
run module: boundRow
    insert string 'boundRow' as #13
Start run module boundRow
register extension:  boundRow: interpret (4308616688) 391 29 (1)
register extension:  boundRow: interpret (4308616688) 300 29 (1)
register extension:  boundRow: interpret (4308616688) 300 29 (1)
register extension:  boundRow: interpret (4308616688) 300 29 (1)
register extension:  boundRow: interpret (4308616688) 300 29 (1)
End run module boundRow
delete module class after run: boundRow
construct module class: linearSos
    insert string 'sos' as #14
    insert string 'b' as #15
    insert string 'bu' as #16
    insert string 'd' as #17
    insert string 'sos2' as #18
parse command line options for module: linearSos
 setOptionPrio p: 12288
run module: linearSos
    insert string 'linearSos' as #19
Start run module linearSos
register extension:  linearSos: compile (4308615776) 201 30 (1)
register extension:  linearSos: interpret (4308616688) 301 30 (3)
register extension:  linearSos: interpret (4308616688) 311 30 (1)
register extension:  linearSos: interpret (4308616688) 361 30 (1)
register extension:  linearSos: interpret (4308616688) 391 30 (1)
register extension:  linearSos: <any module> 401 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
register extension:  linearSos: interpret (4308616688) 300 30 (1)
End run module linearSos
delete module class after run: linearSos
construct module class: linearVarProd
    insert string 'n' as #20
parse command line options for module: linearVarProd
 setOptionPrio p: 12288
run module: linearVarProd
    insert string 'linearVarProd' as #21
Start run module linearVarProd
register extension:  linearVarProd: interpret (4308616688) 391 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
register extension:  linearVarProd: interpret (4308616688) 300 33 (1)
End run module linearVarProd
delete module class after run: linearVarProd
construct module class: linearConstantRow
    insert string 'c' as #22
parse command line options for module: linearConstantRow
 setOptionPrio p: 12288
run module: linearConstantRow
    insert string 'linearConstantRow' as #23
Start run module linearConstantRow
register extension:  linearConstantRow: interpret (4308616688) 391 34 (1)
register extension:  linearConstantRow: interpret (4308616688) 300 34 (1)
register extension:  linearConstantRow: interpret (4308616688) 300 34 (1)
register extension:  linearConstantRow: interpret (4308616688) 300 34 (1)
register extension:  linearConstantRow: interpret (4308616688) 300 34 (1)
register extension:  linearConstantRow: interpret (4308616688) 300 34 (1)
register extension:  linearConstantRow: interpret (4308616688) 300 34 (1)
register extension:  linearConstantRow: interpret (4308616688) 300 34 (1)
End run module linearConstantRow
delete module class after run: linearConstantRow
construct module class: linearLogCon
    insert string 'a' as #24
    insert string 'o' as #25
parse command line options for module: linearLogCon
 setOptionPrio p: 12288
run module: linearLogCon
    insert string 'linearLogCon' as #26
Start run module linearLogCon
register extension:  linearLogCon: interpret (4308616688) 391 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
register extension:  linearLogCon: interpret (4308616688) 300 35 (1)
End run module linearLogCon
delete module class after run: linearLogCon
construct module class: precompile
parse command line options for module: precompile
    insert string 'i' as #1
 setOptionPrio i: 12288
 setOptionPrio p: 12288
run module: precompile
    insert string 'precompile' as #27
Start run precompile module precompile
iterInput: 1 0
  iterTo: '10_Beispiel_Rost.cmpl' (0) from: command line:$1
    insert string '10_Beispiel_Rost.cmpl' as #28
<<EOF>>
End run precompile module precompile
delete module class after run: precompile
construct module class: transferToServer
parse command line options for module: transferToServer
 setOptionPrio p: 12288
run module: transferToServer
    insert string 'transferToServer' as #29
Start run module transferToServer
End run module transferToServer
delete module class after run: transferToServer
construct module class: compile
parse command line options for module: compile
 setOptionPrio p: 12288
    insert string 'warn-insert-eos' as #2
parseOption module compile: warn-insert-eos (50): 4099
 setOptionPrio warn-insert-eos: 4099
    insert string 'compat-linenamepref' as #3
parseOption module compile: compat-linenamepref (40): 4099
 setOptionPrio compat-linenamepref: 4099
    insert string 'compat-cbsymbols' as #4
parseOption module compile: compat-cbsymbols (41): 4099
 setOptionPrio compat-cbsymbols: 4099
    insert string 'compat-cbh-assign' as #5
parseOption module compile: compat-cbh-assign (42): 4099
 setOptionPrio compat-cbh-assign: 4099
run module: compile
    grow strings array from 30 to 60
    insert string 'compile' as #30
Start run compiler module compile
allocate array for intermediary code with initial capacity: 1000
 @ 0 (0): FUNCTION - START: 0, 0
    grow strings array from 0 to 30
    insert string 'par' as #0
    grow symbols array from 0 to 30
    insert string 'par' as #31
    insert string 'var' as #1
    insert string 'var' as #32
    insert string 'obj' as #2
    insert string 'obj' as #33
    insert string 'con' as #3
    insert string 'con' as #34
    insert string 'real' as #4
    insert string 'real' as #35
    insert string 'int' as #5
    insert string 'int' as #36
    insert string 'bin' as #6
    insert string 'bin' as #37
    insert string 'numeric' as #7
    insert string 'numeric' as #38
    insert string 'formula' as #8
    insert string 'formula' as #39
    insert string 'string' as #9
    insert string 'string' as #40
    insert string 'indexpart' as #10
    insert string 'indexpart' as #41
    insert string 'tuple' as #11
    insert string 'tuple' as #42
    insert string 'set' as #12
    insert string 'set' as #43
    insert string 'interval' as #13
    insert string 'interval' as #44
    insert string 'function' as #14
    insert string 'function' as #45
    insert string 'container' as #15
    insert string 'container' as #46
    insert string 'type' as #16
    insert string 'type' as #47
    insert string 'objecttype' as #17
    insert string 'objecttype' as #48
    insert string 'true' as #18
    insert string 'true' as #49
    insert string 'false' as #19
    insert string 'false' as #50
    insert string 'null' as #20
    insert string 'null' as #51
    insert string 'inf' as #21
    insert string 'inf' as #52
    insert string 'invalid' as #22
    insert string 'invalid' as #53
    insert string 'sum' as #23
    insert string 'sum' as #54
    insert string 'min' as #24
    insert string 'min' as #55
    insert string 'max' as #25
    insert string 'max' as #56
    insert string 'and' as #26
    insert string 'and' as #57
    insert string 'or' as #27
    insert string 'or' as #58
    insert string 'mod' as #28
    insert string 'mod' as #59
    insert string 'div' as #29
    grow strings array from 60 to 90
    insert string 'div' as #60
    grow strings array from 30 to 60
    insert string 'srand' as #30
    grow symbols array from 30 to 60
    insert string 'srand' as #61
    insert string 'rand' as #31
    insert string 'rand' as #62
    insert string 'count' as #32
    insert string 'count' as #63
    insert string 'def' as #33
    insert string 'def' as #64
    insert string 'valid' as #34
    insert string 'valid' as #65
    insert string 'dim' as #35
    insert string 'dim' as #66
    insert string 'defset' as #36
    insert string 'defset' as #67
    insert string 'validset' as #37
    insert string 'validset' as #68
    insert string 'len' as #38
    insert string 'len' as #69
    insert string 'rank' as #39
    insert string 'rank' as #70
    insert string 'echo' as #40
    insert string 'echo' as #71
    insert string 'error' as #41
    insert string 'error' as #72
    insert string 'format' as #42
    insert string 'format' as #73
    grow strings array from 0 to 30
    insert string 'as_var' as #0
    grow symbols array from 0 to 30
    insert string 'as_var' as #74
    insert string 'as_con' as #1
    insert string 'as_con' as #75
    insert string 'as_obj' as #2
    insert string 'as_obj' as #76
    insert string 'as_string' as #3
    insert string 'as_string' as #77
    insert string '$arg' as #43
    insert string '$arg' as #78
    insert string '$this' as #44
    insert string '$this' as #79
    insert string '$func' as #45
    insert string '$func' as #80
    insert string '$curTuple' as #46
    insert string '$curTuple' as #81
    insert string '$curDestName' as #47
    insert string '$curDestName' as #82
    insert string '$curDestTuple' as #48
    insert string '$curDestTuple' as #83
    insert string '$varByName' as #49
    insert string '$varByName' as #84
    insert string '$varByNo' as #50
    insert string '$varByNo' as #85
    insert string '$conByName' as #51
    insert string '$conByName' as #86
    insert string '$conByNo' as #52
    insert string '$conByNo' as #87
    insert string '$objectType' as #4
    insert string '$objectType' as #88
    insert string '$dataType' as #5
    insert string '$dataType' as #89
    insert string '$typeBase' as #6
    grow strings array from 90 to 120
    insert string '$typeBase' as #90
    insert string '$typePar' as #7
    insert string '$typePar' as #91
    insert string '$isReadOnly' as #8
    insert string '$isReadOnly' as #92
    insert string '$destName' as #9
    insert string '$destName' as #93
    insert string '$destTuple' as #10
    insert string '$destTuple' as #94
    insert string '$destNameTuple' as #11
    insert string '$destNameTuple' as #95
    insert string '$destFullName' as #12
    insert string '$destFullName' as #96
    insert string '$fullFormula' as #13
    insert string '$fullFormula' as #97
    insert string '$formulaArray' as #14
    insert string '$formulaArray' as #98
run all extensions:  compile (4308615776) 201
 extension CompatSymbols: define symbols: 201 1
    insert string 'parameters' as #53
    insert string 'parameters' as #99
    insert string 'variables' as #54
    insert string 'variables' as #100
    insert string 'objectives' as #55
    insert string 'objectives' as #101
    insert string 'constraints' as #56
    insert string 'constraints' as #102
    insert string 'integer' as #57
    insert string 'integer' as #103
    insert string 'binary' as #58
    insert string 'binary' as #104
 extension CompatSymbols: end
 extension mathFunctions: define symbols: 201 2
    insert string 'sqrt' as #59
    insert string 'sqrt' as #105
    grow strings array from 60 to 90
    insert string 'exp' as #60
    grow symbols array from 60 to 90
    insert string 'exp' as #106
    insert string 'ln' as #61
    insert string 'ln' as #107
    insert string 'lg' as #62
    insert string 'lg' as #108
    insert string 'ld' as #63
    insert string 'ld' as #109
    insert string 'sin' as #64
    insert string 'sin' as #110
    insert string 'cos' as #65
    insert string 'cos' as #111
    insert string 'tan' as #66
    insert string 'tan' as #112
    insert string 'asin' as #67
    insert string 'asin' as #113
    insert string 'acos' as #68
    insert string 'acos' as #114
    insert string 'atan' as #69
    insert string 'atan' as #115
    insert string 'sinh' as #70
    insert string 'sinh' as #116
    insert string 'cosh' as #71
    insert string 'cosh' as #117
    insert string 'tanh' as #72
    insert string 'tanh' as #118
    insert string 'abs' as #73
    insert string 'abs' as #119
    insert string 'ceil' as #74
    grow strings array from 120 to 150
    insert string 'ceil' as #120
    insert string 'floor' as #75
    insert string 'floor' as #121
    insert string 'round' as #76
    insert string 'round' as #122
 extension mathFunctions: end
 extension inputFunctions: define symbols: 201 20
    insert string 'readstdin' as #77
    insert string 'readstdin' as #123
    insert string 'readcsv' as #78
    insert string 'readcsv' as #124
 extension inputFunctions: end
 extension classFunctions: define symbols: 201 22
    insert string 'class' as #79
    insert string 'runat' as #15
    insert string 'runat' as #125
    insert string 'construct' as #16
    insert string 'construct' as #126
    insert string 'copy' as #17
    insert string 'copy' as #127
    insert string 'refcopy' as #18
    insert string 'refcopy' as #128
    insert string 'finalize' as #19
    insert string 'finalize' as #129
 extension classFunctions: end
 extension linearSos: define symbols: 201 30
    insert string 'sos' as #80
    insert string 'sos1' as #20
    insert string 'sos1' as #130
    insert string 'sos2' as #21
    insert string 'ord' as #22
    insert string 'ord' as #131
declSymbol: ord (1, 104): 1 0
    insert string 'name' as #23
    insert string 'name' as #132
declSymbol: name (1, 105): 1 0
    insert string 'add' as #24
    insert string 'add' as #133
declSymbol: add (1, 106): 1 0
    insert string '*vararray' as #25
    insert string '*vararray' as #134
declSymbol: *vararray (1, 107): 1 0
 extension linearSos: end
    insert string 'command line' as #135
    insert string 'x1A' as #81
    insert string 'x1A' as #136
 @ 1 (3): FETCH - GLOBAL: 0, 1
 @ 2 (3):     (argNo2) 108, 0
    insert string 'x1B' as #82
    insert string 'x1B' as #137
 @ 3 (4): FETCH - GLOBAL: 0, 1
 @ 4 (4):     (argNo2) 109, 0
    insert string 'x1C' as #83
    insert string 'x1C' as #138
 @ 5 (5): FETCH - GLOBAL: 0, 1
 @ 6 (5):     (argNo2) 110, 0
    insert string 'x2A' as #84
    insert string 'x2A' as #139
 @ 7 (6): FETCH - GLOBAL: 0, 1
 @ 8 (6):     (argNo2) 111, 0
    insert string 'x2B' as #85
    insert string 'x2B' as #140
 @ 9 (7): FETCH - GLOBAL: 0, 1
 @ 10 (7):     (argNo2) 112, 0
    insert string 'x2C' as #86
    insert string 'x2C' as #141
 @ 11 (8): FETCH - GLOBAL: 0, 1
 @ 12 (8):     (argNo2) 113, 0
    insert string 'x3A' as #87
    insert string 'x3A' as #142
 @ 13 (9): FETCH - GLOBAL: 0, 1
 @ 14 (9):     (argNo2) 114, 0
    insert string 'x3B' as #88
    insert string 'x3B' as #143
 @ 15 (10): FETCH - GLOBAL: 0, 1
 @ 16 (10):     (argNo2) 115, 0
    insert string 'x3C' as #89
    insert string 'x3C' as #144
 @ 17 (11): FETCH - GLOBAL: 0, 1
 @ 18 (11):     (argNo2) 116, 0
    grow strings array from 90 to 120
    insert string 'x4A' as #90
    grow symbols array from 90 to 120
    insert string 'x4A' as #145
 @ 19 (12): FETCH - GLOBAL: 0, 1
 @ 20 (12):     (argNo2) 117, 0
    insert string 'x4B' as #91
    insert string 'x4B' as #146
 @ 21 (13): FETCH - GLOBAL: 0, 1
 @ 22 (13):     (argNo2) 118, 0
    insert string 'x4C' as #92
    insert string 'x4C' as #147
 @ 23 (14): FETCH - GLOBAL: 0, 1
 @ 24 (14):     (argNo2) 119, 0
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
 ExprParseInfo::oper: 14, 2
checkDefSymbol: x1A (0, 108)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x1A (0, 108): 1 0
 @ 1 (3): FETCH - GLOBAL: 1, 1
 @ 2 (3):     (argNo2) 108, 82
checkDefSymbol: x1B (0, 109)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x1B (0, 109): 1 0
 @ 3 (4): FETCH - GLOBAL: 1, 1
 @ 4 (4):     (argNo2) 109, 83
checkDefSymbol: x1C (0, 110)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x1C (0, 110): 1 0
 @ 5 (5): FETCH - GLOBAL: 1, 1
 @ 6 (5):     (argNo2) 110, 84
checkDefSymbol: x2A (0, 111)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x2A (0, 111): 1 0
 @ 7 (6): FETCH - GLOBAL: 1, 1
 @ 8 (6):     (argNo2) 111, 85
checkDefSymbol: x2B (0, 112)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x2B (0, 112): 1 0
 @ 9 (7): FETCH - GLOBAL: 1, 1
 @ 10 (7):     (argNo2) 112, 86
checkDefSymbol: x2C (0, 113)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x2C (0, 113): 1 0
 @ 11 (8): FETCH - GLOBAL: 1, 1
 @ 12 (8):     (argNo2) 113, 87
checkDefSymbol: x3A (0, 114)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x3A (0, 114): 1 0
 @ 13 (9): FETCH - GLOBAL: 1, 1
 @ 14 (9):     (argNo2) 114, 88
checkDefSymbol: x3B (0, 115)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x3B (0, 115): 1 0
 @ 15 (10): FETCH - GLOBAL: 1, 1
 @ 16 (10):     (argNo2) 115, 89
checkDefSymbol: x3C (0, 116)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x3C (0, 116): 1 0
 @ 17 (11): FETCH - GLOBAL: 1, 1
 @ 18 (11):     (argNo2) 116, 90
checkDefSymbol: x4A (0, 117)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x4A (0, 117): 1 0
 @ 19 (12): FETCH - GLOBAL: 1, 1
 @ 20 (12):     (argNo2) 117, 91
checkDefSymbol: x4B (0, 118)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x4B (0, 118): 1 0
 @ 21 (13): FETCH - GLOBAL: 1, 1
 @ 22 (13):     (argNo2) 118, 92
checkDefSymbol: x4C (0, 119)
  modificators: Modificators < ObjectType: var (D) >
declSymbol: x4C (0, 119): 1 0
 @ 23 (14): FETCH - GLOBAL: 1, 1
 @ 24 (14):     (argNo2) 119, 93
 @ 25 (16): FETCH - GLOBAL: 0, 1
 @ 26 (16):     (argNo2) 74, 59
 @ 27 (18): ASSIGN - NORMAL: 8204, 1
 @ 28 (18):     (argNo2) 2, 0
 @ 29 (22): LIT_VAL - INT: 3, 0
 @ 30 (23): FETCH - GLOBAL: 0, 1
 @ 31 (23):     (argNo2) 108, 82
 ExprParseInfo::oper: 1, 2
 @ 32 (24): OPERATION - MUL: 2, 0
 @ 33 (25): FETCH - GLOBAL: 0, 1
 @ 34 (25):     (argNo2) 112, 86
 ExprParseInfo::oper: 1, 2
 @ 35 (26): OPERATION - MUL: 2, 0
 @ 36 (27): LIT_VAL - INT: 8, 0
 @ 37 (28): FETCH - GLOBAL: 0, 1
 @ 38 (28):     (argNo2) 108, 82
 ExprParseInfo::oper: 1, 2
 @ 39 (29): OPERATION - MUL: 2, 0
 @ 40 (30): FETCH - GLOBAL: 0, 1
 @ 41 (30):     (argNo2) 113, 87
 ExprParseInfo::oper: 1, 2
 @ 42 (31): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 43 (32): OPERATION - ADD: 2, 0
 @ 44 (33): LIT_VAL - INT: 3, 0
 @ 45 (34): FETCH - GLOBAL: 0, 1
 @ 46 (34):     (argNo2) 109, 83
 ExprParseInfo::oper: 1, 2
 @ 47 (35): OPERATION - MUL: 2, 0
 @ 48 (36): FETCH - GLOBAL: 0, 1
 @ 49 (36):     (argNo2) 111, 85
 ExprParseInfo::oper: 1, 2
 @ 50 (37): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 51 (38): OPERATION - ADD: 2, 0
 @ 52 (39): LIT_VAL - INT: 3, 0
 @ 53 (40): FETCH - GLOBAL: 0, 1
 @ 54 (40):     (argNo2) 109, 83
 ExprParseInfo::oper: 1, 2
 @ 55 (41): OPERATION - MUL: 2, 0
 @ 56 (42): FETCH - GLOBAL: 0, 1
 @ 57 (42):     (argNo2) 113, 87
 ExprParseInfo::oper: 1, 2
 @ 58 (43): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 59 (44): OPERATION - ADD: 2, 0
 @ 60 (45): LIT_VAL - INT: 7, 0
 @ 61 (46): FETCH - GLOBAL: 0, 1
 @ 62 (46):     (argNo2) 110, 84
 ExprParseInfo::oper: 1, 2
 @ 63 (47): OPERATION - MUL: 2, 0
 @ 64 (48): FETCH - GLOBAL: 0, 1
 @ 65 (48):     (argNo2) 111, 85
 ExprParseInfo::oper: 1, 2
 @ 66 (49): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 67 (50): OPERATION - ADD: 2, 0
 @ 68 (51): LIT_VAL - INT: 3, 0
 @ 69 (52): FETCH - GLOBAL: 0, 1
 @ 70 (52):     (argNo2) 110, 84
 ExprParseInfo::oper: 1, 2
 @ 71 (53): OPERATION - MUL: 2, 0
 @ 72 (54): FETCH - GLOBAL: 0, 1
 @ 73 (54):     (argNo2) 112, 86
 ExprParseInfo::oper: 1, 2
 @ 74 (55): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 75 (56): OPERATION - ADD: 2, 0
 @ 76 (57): LIT_VAL - INT: 4, 0
 @ 77 (58): FETCH - GLOBAL: 0, 1
 @ 78 (58):     (argNo2) 108, 82
 ExprParseInfo::oper: 1, 2
 @ 79 (59): OPERATION - MUL: 2, 0
 @ 80 (60): FETCH - GLOBAL: 0, 1
 @ 81 (60):     (argNo2) 112, 86
 ExprParseInfo::oper: 1, 2
 @ 82 (61): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 83 (62): OPERATION - ADD: 2, 0
 @ 84 (63): LIT_VAL - INT: 11, 0
 @ 85 (64): FETCH - GLOBAL: 0, 1
 @ 86 (64):     (argNo2) 108, 82
 ExprParseInfo::oper: 1, 2
 @ 87 (65): OPERATION - MUL: 2, 0
 @ 88 (66): FETCH - GLOBAL: 0, 1
 @ 89 (66):     (argNo2) 116, 90
 ExprParseInfo::oper: 1, 2
 @ 90 (67): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 91 (68): OPERATION - ADD: 2, 0
 @ 92 (69): LIT_VAL - INT: 4, 0
 @ 93 (70): FETCH - GLOBAL: 0, 1
 @ 94 (70):     (argNo2) 109, 83
 ExprParseInfo::oper: 1, 2
 @ 95 (71): OPERATION - MUL: 2, 0
 @ 96 (72): FETCH - GLOBAL: 0, 1
 @ 97 (72):     (argNo2) 114, 88
 ExprParseInfo::oper: 1, 2
 @ 98 (73): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 99 (74): OPERATION - ADD: 2, 0
 @ 100 (75): LIT_VAL - INT: 4, 0
 @ 101 (76): FETCH - GLOBAL: 0, 1
 @ 102 (76):     (argNo2) 109, 83
 ExprParseInfo::oper: 1, 2
 @ 103 (77): OPERATION - MUL: 2, 0
 @ 104 (78): FETCH - GLOBAL: 0, 1
 @ 105 (78):     (argNo2) 116, 90
 ExprParseInfo::oper: 1, 2
 @ 106 (79): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 107 (80): OPERATION - ADD: 2, 0
 @ 108 (81): LIT_VAL - INT: 9, 0
 @ 109 (82): FETCH - GLOBAL: 0, 1
 @ 110 (82):     (argNo2) 110, 84
 ExprParseInfo::oper: 1, 2
 @ 111 (83): OPERATION - MUL: 2, 0
 @ 112 (84): FETCH - GLOBAL: 0, 1
 @ 113 (84):     (argNo2) 114, 88
 ExprParseInfo::oper: 1, 2
 @ 114 (85): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 115 (86): OPERATION - ADD: 2, 0
 @ 116 (87): LIT_VAL - INT: 4, 0
 @ 117 (88): FETCH - GLOBAL: 0, 1
 @ 118 (88):     (argNo2) 110, 84
 ExprParseInfo::oper: 1, 2
 @ 119 (89): OPERATION - MUL: 2, 0
 @ 120 (90): FETCH - GLOBAL: 0, 1
 @ 121 (90):     (argNo2) 114, 88
 ExprParseInfo::oper: 1, 2
 @ 122 (91): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 123 (92): OPERATION - ADD: 2, 0
 @ 124 (93): LIT_VAL - INT: 3, 0
 @ 125 (94): FETCH - GLOBAL: 0, 1
 @ 126 (94):     (argNo2) 111, 85
 ExprParseInfo::oper: 1, 2
 @ 127 (95): OPERATION - MUL: 2, 0
 @ 128 (96): FETCH - GLOBAL: 0, 1
 @ 129 (96):     (argNo2) 115, 89
 ExprParseInfo::oper: 1, 2
 @ 130 (97): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 131 (98): OPERATION - ADD: 2, 0
 @ 132 (99): LIT_VAL - INT: 3, 0
 @ 133 (100): FETCH - GLOBAL: 0, 1
 @ 134 (100):     (argNo2) 111, 85
 ExprParseInfo::oper: 1, 2
 @ 135 (101): OPERATION - MUL: 2, 0
 @ 136 (102): FETCH - GLOBAL: 0, 1
 @ 137 (102):     (argNo2) 115, 89
 ExprParseInfo::oper: 1, 2
 @ 138 (103): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 139 (104): OPERATION - ADD: 2, 0
 @ 140 (105): LIT_VAL - INT: 7, 0
 @ 141 (106): FETCH - GLOBAL: 0, 1
 @ 142 (106):     (argNo2) 111, 85
 ExprParseInfo::oper: 1, 2
 @ 143 (107): OPERATION - MUL: 2, 0
 @ 144 (108): FETCH - GLOBAL: 0, 1
 @ 145 (108):     (argNo2) 116, 90
 ExprParseInfo::oper: 1, 2
 @ 146 (109): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 147 (110): OPERATION - ADD: 2, 0
 @ 148 (111): LIT_VAL - INT: 3, 0
 @ 149 (112): FETCH - GLOBAL: 0, 1
 @ 150 (112):     (argNo2) 112, 86
 ExprParseInfo::oper: 1, 2
 @ 151 (113): OPERATION - MUL: 2, 0
 @ 152 (114): FETCH - GLOBAL: 0, 1
 @ 153 (114):     (argNo2) 114, 88
 ExprParseInfo::oper: 1, 2
 @ 154 (115): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 155 (116): OPERATION - ADD: 2, 0
 @ 156 (117): LIT_VAL - INT: 3, 0
 @ 157 (118): FETCH - GLOBAL: 0, 1
 @ 158 (118):     (argNo2) 112, 86
 ExprParseInfo::oper: 1, 2
 @ 159 (119): OPERATION - MUL: 2, 0
 @ 160 (120): FETCH - GLOBAL: 0, 1
 @ 161 (120):     (argNo2) 116, 90
 ExprParseInfo::oper: 1, 2
 @ 162 (121): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 163 (122): OPERATION - ADD: 2, 0
 @ 164 (123): LIT_VAL - INT: 8, 0
 @ 165 (124): FETCH - GLOBAL: 0, 1
 @ 166 (124):     (argNo2) 113, 87
 ExprParseInfo::oper: 1, 2
 @ 167 (125): OPERATION - MUL: 2, 0
 @ 168 (126): FETCH - GLOBAL: 0, 1
 @ 169 (126):     (argNo2) 114, 88
 ExprParseInfo::oper: 1, 2
 @ 170 (127): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 171 (128): OPERATION - ADD: 2, 0
 @ 172 (129): LIT_VAL - INT: 3, 0
 @ 173 (130): FETCH - GLOBAL: 0, 1
 @ 174 (130):     (argNo2) 113, 87
 ExprParseInfo::oper: 1, 2
 @ 175 (131): OPERATION - MUL: 2, 0
 @ 176 (132): FETCH - GLOBAL: 0, 1
 @ 177 (132):     (argNo2) 115, 89
 ExprParseInfo::oper: 1, 2
 @ 178 (133): OPERATION - MUL: 2, 0
 ExprParseInfo::oper: 1, 2
 @ 179 (134): OPERATION - ADD: 2, 0
 @ 180 (134): ASSIGN - RHSONLY: 8192, 1
 @ 181 (134):     (argNo2) 3, 0
 @ 182 (138): FETCH - GLOBAL: 0, 1
 @ 183 (138):     (argNo2) 108, 82
 @ 184 (139): FETCH - GLOBAL: 0, 1
 @ 185 (139):     (argNo2) 109, 83
 ExprParseInfo::oper: 1, 2
 @ 186 (140): OPERATION - ADD: 2, 0
 @ 187 (141): FETCH - GLOBAL: 0, 1
 @ 188 (141):     (argNo2) 110, 84
 ExprParseInfo::oper: 1, 2
 @ 189 (142): OPERATION - ADD: 2, 0
 @ 190 (143): LIT_VAL - INT: 1, 0
 ExprParseInfo::oper: 5, 2
 @ 191 (144): OPERATION - EQ: 2, 0
 @ 192 (144): ASSIGN - RHSONLY: 8192, 1
 @ 193 (144):     (argNo2) 4, 0
 @ 194 (146): FETCH - GLOBAL: 0, 1
 @ 195 (146):     (argNo2) 111, 85
 @ 196 (147): FETCH - GLOBAL: 0, 1
 @ 197 (147):     (argNo2) 112, 86
 ExprParseInfo::oper: 1, 2
 @ 198 (148): OPERATION - ADD: 2, 0
 @ 199 (149): FETCH - GLOBAL: 0, 1
 @ 200 (149):     (argNo2) 113, 87
 ExprParseInfo::oper: 1, 2
 @ 201 (150): OPERATION - ADD: 2, 0
 @ 202 (151): LIT_VAL - INT: 1, 0
 ExprParseInfo::oper: 5, 2
 @ 203 (152): OPERATION - EQ: 2, 0
 @ 204 (152): ASSIGN - RHSONLY: 8192, 1
 @ 205 (152):     (argNo2) 4, 0
 @ 206 (154): FETCH - GLOBAL: 0, 1
 @ 207 (154):     (argNo2) 114, 88
 @ 208 (155): FETCH - GLOBAL: 0, 1
 @ 209 (155):     (argNo2) 115, 89
 ExprParseInfo::oper: 1, 2
 @ 210 (156): OPERATION - ADD: 2, 0
 @ 211 (157): FETCH - GLOBAL: 0, 1
 @ 212 (157):     (argNo2) 116, 90
 ExprParseInfo::oper: 1, 2
 @ 213 (158): OPERATION - ADD: 2, 0
 @ 214 (159): LIT_VAL - INT: 1, 0
 ExprParseInfo::oper: 5, 2
 @ 215 (160): OPERATION - EQ: 2, 0
 @ 216 (160): ASSIGN - RHSONLY: 8192, 1
 @ 217 (160):     (argNo2) 4, 0
 @ 218 (162): FETCH - GLOBAL: 0, 1
 @ 219 (162):     (argNo2) 108, 82
 @ 220 (163): FETCH - GLOBAL: 0, 1
 @ 221 (163):     (argNo2) 111, 85
 ExprParseInfo::oper: 1, 2
 @ 222 (164): OPERATION - ADD: 2, 0
 @ 223 (165): FETCH - GLOBAL: 0, 1
 @ 224 (165):     (argNo2) 114, 88
 ExprParseInfo::oper: 1, 2
 @ 225 (166): OPERATION - ADD: 2, 0
 @ 226 (167): LIT_VAL - INT: 1, 0
 ExprParseInfo::oper: 5, 2
 @ 227 (168): OPERATION - EQ: 2, 0
 @ 228 (168): ASSIGN - RHSONLY: 8192, 1
 @ 229 (168):     (argNo2) 4, 0
 @ 230 (170): FETCH - GLOBAL: 0, 1
 @ 231 (170):     (argNo2) 109, 83
 @ 232 (171): FETCH - GLOBAL: 0, 1
 @ 233 (171):     (argNo2) 112, 86
 ExprParseInfo::oper: 1, 2
 @ 234 (172): OPERATION - ADD: 2, 0
 @ 235 (173): FETCH - GLOBAL: 0, 1
 @ 236 (173):     (argNo2) 115, 89
 ExprParseInfo::oper: 1, 2
 @ 237 (174): OPERATION - ADD: 2, 0
 @ 238 (175): LIT_VAL - INT: 1, 0
 ExprParseInfo::oper: 5, 2
 @ 239 (176): OPERATION - EQ: 2, 0
 @ 240 (176): ASSIGN - RHSONLY: 8192, 1
 @ 241 (176):     (argNo2) 4, 0
 @ 242 (178): FETCH - GLOBAL: 0, 1
 @ 243 (178):     (argNo2) 110, 84
 @ 244 (179): FETCH - GLOBAL: 0, 1
 @ 245 (179):     (argNo2) 113, 87
 ExprParseInfo::oper: 1, 2
 @ 246 (180): OPERATION - ADD: 2, 0
 @ 247 (181): FETCH - GLOBAL: 0, 1
 @ 248 (181):     (argNo2) 116, 90
 ExprParseInfo::oper: 1, 2
 @ 249 (182): OPERATION - ADD: 2, 0
 @ 250 (183): LIT_VAL - INT: 1, 0
 ExprParseInfo::oper: 5, 2
 @ 251 (184): OPERATION - EQ: 2, 0
 @ 252 (184): ASSIGN - RHSONLY: 8192, 1
 @ 253 (184):     (argNo2) 4, 0
Parse cmpl End
 @ 254 (186): FUNCTION - END: 0, 0
    insert string 'pre-defined symbol' as #148
    insert string ':' as #149
    grow strings array from 150 to 180
    insert string '+' as #150
    insert string '*' as #151
    insert string '=' as #152
End run compiler module compile
delete module class after run: compile
construct module class: interpret
parse command line options for module: interpret
 setOptionPrio p: 12288
    insert string 'warn-invalid-sos' as #6
run one extension:  interpret (4308616688) 300 30 for command line option warn-invalid-sos (85, 4097)
 setOptionPrio warn-invalid-sos: 4097
run module: interpret
    insert string 'interpret' as #153
Start run interpreter module interpret
run one extension:  interpret (4308616688) 301 2
 extension mathFunctions: initialize symbol values: 301 2
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 3
 extension mathFunctions: initialize symbol values: 301 3
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 4
 extension mathFunctions: initialize symbol values: 301 4
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 5
 extension mathFunctions: initialize symbol values: 301 5
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 6
 extension mathFunctions: initialize symbol values: 301 6
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 7
 extension mathFunctions: initialize symbol values: 301 7
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 8
 extension mathFunctions: initialize symbol values: 301 8
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 9
 extension mathFunctions: initialize symbol values: 301 9
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 10
 extension mathFunctions: initialize symbol values: 301 10
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 11
 extension mathFunctions: initialize symbol values: 301 11
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 12
 extension mathFunctions: initialize symbol values: 301 12
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 13
 extension mathFunctions: initialize symbol values: 301 13
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 14
 extension mathFunctions: initialize symbol values: 301 14
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 15
 extension mathFunctions: initialize symbol values: 301 15
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 16
 extension mathFunctions: initialize symbol values: 301 16
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 17
 extension mathFunctions: initialize symbol values: 301 17
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 18
 extension mathFunctions: initialize symbol values: 301 18
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 19
 extension mathFunctions: initialize symbol values: 301 19
 extension mathFunctions: end
run one extension:  interpret (4308616688) 301 20
 extension inputFunctions: initialize symbol values: 301 20
 extension inputFunctions: end
run one extension:  interpret (4308616688) 301 21
 extension inputFunctions: initialize symbol values: 301 21
 extension inputFunctions: end
run one extension:  interpret (4308616688) 301 22
 extension classFunctions: initialize symbol values: 301 22
 extension classFunctions: end
run one extension:  interpret (4308616688) 301 30
 extension linearSos: initialize symbol values: 301 30
 extension linearSos: end
run one extension:  interpret (4308616688) 301 23
 extension classFunctions: initialize symbol values: 301 23
 extension classFunctions: end
run one extension:  interpret (4308616688) 301 24
 extension classFunctions: initialize symbol values: 301 24
 extension classFunctions: end
run one extension:  interpret (4308616688) 301 25
 extension classFunctions: initialize symbol values: 301 25
 extension classFunctions: end
run one extension:  interpret (4308616688) 301 26
 extension classFunctions: initialize symbol values: 301 26
 extension classFunctions: end
run one extension:  interpret (4308616688) 301 27
 extension classFunctions: initialize symbol values: 301 27
 extension classFunctions: end
run one extension:  interpret (4308616688) 301 31
 extension linearSos: initialize symbol values: 301 31
 extension linearSos: end
run one extension:  interpret (4308616688) 301 32
 extension linearSos: initialize symbol values: 301 32
 extension linearSos: end
run all extensions:  interpret (4308616688) 311
 extension linearSos: end
start main loop in execution context (level 0) at code pos 0
 @ 0 (186): FUNCTION - START: 0, 0
 @ 1 (3): FETCH - GLOBAL: 1, 1
 @ 2 (3):     (argNo2) 108, 82
pushPre: 1 (3)
 @ 3 (4): FETCH - GLOBAL: 1, 1
 @ 4 (4):     (argNo2) 109, 83
pushPre: 2 (4)
 @ 5 (5): FETCH - GLOBAL: 1, 1
 @ 6 (5):     (argNo2) 110, 84
pushPre: 3 (5)
 @ 7 (6): FETCH - GLOBAL: 1, 1
 @ 8 (6):     (argNo2) 111, 85
pushPre: 4 (6)
 @ 9 (7): FETCH - GLOBAL: 1, 1
 @ 10 (7):     (argNo2) 112, 86
pushPre: 5 (7)
 @ 11 (8): FETCH - GLOBAL: 1, 1
 @ 12 (8):     (argNo2) 113, 87
pushPre: 6 (8)
 @ 13 (9): FETCH - GLOBAL: 1, 1
 @ 14 (9):     (argNo2) 114, 88
pushPre: 7 (9)
 @ 15 (10): FETCH - GLOBAL: 1, 1
 @ 16 (10):     (argNo2) 115, 89
pushPre: 8 (10)
 @ 17 (11): FETCH - GLOBAL: 1, 1
 @ 18 (11):     (argNo2) 116, 90
pushPre: 9 (11)
 @ 19 (12): FETCH - GLOBAL: 1, 1
 @ 20 (12):     (argNo2) 117, 91
pushPre: 10 (12)
 @ 21 (13): FETCH - GLOBAL: 1, 1
 @ 22 (13):     (argNo2) 118, 92
pushPre: 11 (13)
 @ 23 (14): FETCH - GLOBAL: 1, 1
 @ 24 (14):     (argNo2) 119, 93
pushPre: 12 (14)
 @ 25 (16): FETCH - GLOBAL: 0, 1
 @ 26 (16):     (argNo2) 74, 59
pushPre: 13 (16)
 @ 27 (18): ASSIGN - NORMAL: 8204, 1
 @ 28 (18):     (argNo2) 2, 0
  cntLhs 12; assignConst 0; assignInitial 0; assignOrdered 0; setResName 1
  rhs = <data type 'bin'>
stackPrev: 12
  -> <symbol_value>
stackPrev: 11
  -> <symbol_value>
stackPrev: 10
  -> <symbol_value>
stackPrev: 9
  -> <symbol_value>
stackPrev: 8
  -> <symbol_value>
stackPrev: 7
  -> <symbol_value>
stackPrev: 6
  -> <symbol_value>
stackPrev: 5
  -> <symbol_value>
stackPrev: 4
  -> <symbol_value>
stackPrev: 3
  -> <symbol_value>
stackPrev: 2
  -> <symbol_value>
stackPrev: 1
  -> <symbol_value>
pushPre: 14 (16)
  setValueStore: sym 108
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 109
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 110
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 111
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 112
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 113
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 114
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 115
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 116
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 117
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 118
popTo: 13
pushPre: 14 (16)
  setValueStore: sym 119
popTo: 1
pop: 0
 @ 29 (22): LIT_VAL - INT: 3, 0
pushPre: 1 (22)
 @ 30 (23): FETCH - GLOBAL: 0, 1
 @ 31 (23):     (argNo2) 108, 82
pushPre: 2 (23)
 @ 32 (24): OPERATION - MUL: 2, 0
stackPrev: 1
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (24)
 @ 33 (25): FETCH - GLOBAL: 0, 1
 @ 34 (25):     (argNo2) 112, 86
pushPre: 2 (25)
 @ 35 (26): OPERATION - MUL: 2, 0
stackPrev: 1
  -> <f-v: 3*<var#1>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (26)
 @ 36 (27): LIT_VAL - INT: 8, 0
pushPre: 2 (27)
 @ 37 (28): FETCH - GLOBAL: 0, 1
 @ 38 (28):     (argNo2) 108, 82
pushPre: 3 (28)
 @ 39 (29): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 8
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (29)
 @ 40 (30): FETCH - GLOBAL: 0, 1
 @ 41 (30):     (argNo2) 113, 87
pushPre: 3 (30)
 @ 42 (31): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 8*<var#1>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (31)
 @ 43 (32): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-vp: 3*<var#1>*<var#5>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (32)
 @ 44 (33): LIT_VAL - INT: 3, 0
pushPre: 2 (33)
 @ 45 (34): FETCH - GLOBAL: 0, 1
 @ 46 (34):     (argNo2) 109, 83
pushPre: 3 (34)
 @ 47 (35): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (35)
 @ 48 (36): FETCH - GLOBAL: 0, 1
 @ 49 (36):     (argNo2) 111, 85
pushPre: 3 (36)
 @ 50 (37): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 3*<var#2>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (37)
 @ 51 (38): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (38)
 @ 52 (39): LIT_VAL - INT: 3, 0
pushPre: 2 (39)
 @ 53 (40): FETCH - GLOBAL: 0, 1
 @ 54 (40):     (argNo2) 109, 83
pushPre: 3 (40)
 @ 55 (41): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (41)
 @ 56 (42): FETCH - GLOBAL: 0, 1
 @ 57 (42):     (argNo2) 113, 87
pushPre: 3 (42)
 @ 58 (43): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 3*<var#2>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (43)
 @ 59 (44): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (44)
 @ 60 (45): LIT_VAL - INT: 7, 0
pushPre: 2 (45)
 @ 61 (46): FETCH - GLOBAL: 0, 1
 @ 62 (46):     (argNo2) 110, 84
pushPre: 3 (46)
 @ 63 (47): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 7
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (47)
 @ 64 (48): FETCH - GLOBAL: 0, 1
 @ 65 (48):     (argNo2) 111, 85
pushPre: 3 (48)
 @ 66 (49): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 7*<var#3>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (49)
 @ 67 (50): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (50)
 @ 68 (51): LIT_VAL - INT: 3, 0
pushPre: 2 (51)
 @ 69 (52): FETCH - GLOBAL: 0, 1
 @ 70 (52):     (argNo2) 110, 84
pushPre: 3 (52)
 @ 71 (53): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (53)
 @ 72 (54): FETCH - GLOBAL: 0, 1
 @ 73 (54):     (argNo2) 112, 86
pushPre: 3 (54)
 @ 74 (55): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 3*<var#3>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (55)
 @ 75 (56): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (56)
 @ 76 (57): LIT_VAL - INT: 4, 0
pushPre: 2 (57)
 @ 77 (58): FETCH - GLOBAL: 0, 1
 @ 78 (58):     (argNo2) 108, 82
pushPre: 3 (58)
 @ 79 (59): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 4
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (59)
 @ 80 (60): FETCH - GLOBAL: 0, 1
 @ 81 (60):     (argNo2) 112, 86
pushPre: 3 (60)
 @ 82 (61): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 4*<var#1>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (61)
 @ 83 (62): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (62)
 @ 84 (63): LIT_VAL - INT: 11, 0
pushPre: 2 (63)
 @ 85 (64): FETCH - GLOBAL: 0, 1
 @ 86 (64):     (argNo2) 108, 82
pushPre: 3 (64)
 @ 87 (65): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 11
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (65)
 @ 88 (66): FETCH - GLOBAL: 0, 1
 @ 89 (66):     (argNo2) 116, 90
pushPre: 3 (66)
 @ 90 (67): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 11*<var#1>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (67)
 @ 91 (68): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (68)
 @ 92 (69): LIT_VAL - INT: 4, 0
pushPre: 2 (69)
 @ 93 (70): FETCH - GLOBAL: 0, 1
 @ 94 (70):     (argNo2) 109, 83
pushPre: 3 (70)
 @ 95 (71): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 4
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (71)
 @ 96 (72): FETCH - GLOBAL: 0, 1
 @ 97 (72):     (argNo2) 114, 88
pushPre: 3 (72)
 @ 98 (73): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 4*<var#2>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (73)
 @ 99 (74): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (74)
 @ 100 (75): LIT_VAL - INT: 4, 0
pushPre: 2 (75)
 @ 101 (76): FETCH - GLOBAL: 0, 1
 @ 102 (76):     (argNo2) 109, 83
pushPre: 3 (76)
 @ 103 (77): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 4
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (77)
 @ 104 (78): FETCH - GLOBAL: 0, 1
 @ 105 (78):     (argNo2) 116, 90
pushPre: 3 (78)
 @ 106 (79): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 4*<var#2>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (79)
 @ 107 (80): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (80)
 @ 108 (81): LIT_VAL - INT: 9, 0
pushPre: 2 (81)
 @ 109 (82): FETCH - GLOBAL: 0, 1
 @ 110 (82):     (argNo2) 110, 84
pushPre: 3 (82)
 @ 111 (83): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 9
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (83)
 @ 112 (84): FETCH - GLOBAL: 0, 1
 @ 113 (84):     (argNo2) 114, 88
pushPre: 3 (84)
 @ 114 (85): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 9*<var#3>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (85)
 @ 115 (86): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (86)
 @ 116 (87): LIT_VAL - INT: 4, 0
pushPre: 2 (87)
 @ 117 (88): FETCH - GLOBAL: 0, 1
 @ 118 (88):     (argNo2) 110, 84
pushPre: 3 (88)
 @ 119 (89): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 4
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (89)
 @ 120 (90): FETCH - GLOBAL: 0, 1
 @ 121 (90):     (argNo2) 114, 88
pushPre: 3 (90)
 @ 122 (91): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 4*<var#3>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (91)
 @ 123 (92): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (92)
 @ 124 (93): LIT_VAL - INT: 3, 0
pushPre: 2 (93)
 @ 125 (94): FETCH - GLOBAL: 0, 1
 @ 126 (94):     (argNo2) 111, 85
pushPre: 3 (94)
 @ 127 (95): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (95)
 @ 128 (96): FETCH - GLOBAL: 0, 1
 @ 129 (96):     (argNo2) 115, 89
pushPre: 3 (96)
 @ 130 (97): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 3*<var#4>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (97)
 @ 131 (98): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>> + 4*<f-vp: *<var#3>*<var#7>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (98)
 @ 132 (99): LIT_VAL - INT: 3, 0
pushPre: 2 (99)
 @ 133 (100): FETCH - GLOBAL: 0, 1
 @ 134 (100):     (argNo2) 111, 85
pushPre: 3 (100)
 @ 135 (101): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (101)
 @ 136 (102): FETCH - GLOBAL: 0, 1
 @ 137 (102):     (argNo2) 115, 89
pushPre: 3 (102)
 @ 138 (103): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 3*<var#4>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (103)
 @ 139 (104): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>> + 4*<f-vp: *<var#3>*<var#7>> + 3*<f-vp: *<var#4>*<var#8>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (104)
 @ 140 (105): LIT_VAL - INT: 7, 0
pushPre: 2 (105)
 @ 141 (106): FETCH - GLOBAL: 0, 1
 @ 142 (106):     (argNo2) 111, 85
pushPre: 3 (106)
 @ 143 (107): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 7
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (107)
 @ 144 (108): FETCH - GLOBAL: 0, 1
 @ 145 (108):     (argNo2) 116, 90
pushPre: 3 (108)
 @ 146 (109): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 7*<var#4>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (109)
 @ 147 (110): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>> + 4*<f-vp: *<var#3>*<var#7>> + 3*<f-vp: *<var#4>*<var#8>> + 3*<f-vp: *<var#4>*<var#8>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (110)
 @ 148 (111): LIT_VAL - INT: 3, 0
pushPre: 2 (111)
 @ 149 (112): FETCH - GLOBAL: 0, 1
 @ 150 (112):     (argNo2) 112, 86
pushPre: 3 (112)
 @ 151 (113): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (113)
 @ 152 (114): FETCH - GLOBAL: 0, 1
 @ 153 (114):     (argNo2) 114, 88
pushPre: 3 (114)
 @ 154 (115): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 3*<var#5>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (115)
 @ 155 (116): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>> + 4*<f-vp: *<var#3>*<var#7>> + 3*<f-vp: *<var#4>*<var#8>> + 3*<f-vp: *<var#4>*<var#8>> + 7*<f-vp: *<var#4>*<var#9>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (116)
 @ 156 (117): LIT_VAL - INT: 3, 0
pushPre: 2 (117)
 @ 157 (118): FETCH - GLOBAL: 0, 1
 @ 158 (118):     (argNo2) 112, 86
pushPre: 3 (118)
 @ 159 (119): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (119)
 @ 160 (120): FETCH - GLOBAL: 0, 1
 @ 161 (120):     (argNo2) 116, 90
pushPre: 3 (120)
 @ 162 (121): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 3*<var#5>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (121)
 @ 163 (122): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>> + 4*<f-vp: *<var#3>*<var#7>> + 3*<f-vp: *<var#4>*<var#8>> + 3*<f-vp: *<var#4>*<var#8>> + 7*<f-vp: *<var#4>*<var#9>> + 3*<f-vp: *<var#5>*<var#7>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (122)
 @ 164 (123): LIT_VAL - INT: 8, 0
pushPre: 2 (123)
 @ 165 (124): FETCH - GLOBAL: 0, 1
 @ 166 (124):     (argNo2) 113, 87
pushPre: 3 (124)
 @ 167 (125): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 8
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (125)
 @ 168 (126): FETCH - GLOBAL: 0, 1
 @ 169 (126):     (argNo2) 114, 88
pushPre: 3 (126)
 @ 170 (127): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 8*<var#6>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (127)
 @ 171 (128): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>> + 4*<f-vp: *<var#3>*<var#7>> + 3*<f-vp: *<var#4>*<var#8>> + 3*<f-vp: *<var#4>*<var#8>> + 7*<f-vp: *<var#4>*<var#9>> + 3*<f-vp: *<var#5>*<var#7>> + 3*<f-vp: *<var#5>*<var#9>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (128)
 @ 172 (129): LIT_VAL - INT: 3, 0
pushPre: 2 (129)
 @ 173 (130): FETCH - GLOBAL: 0, 1
 @ 174 (130):     (argNo2) 113, 87
pushPre: 3 (130)
 @ 175 (131): OPERATION - MUL: 2, 0
stackPrev: 2
  -> 3
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (131)
 @ 176 (132): FETCH - GLOBAL: 0, 1
 @ 177 (132):     (argNo2) 115, 89
pushPre: 3 (132)
 @ 178 (133): OPERATION - MUL: 2, 0
stackPrev: 2
  -> <f-v: 3*<var#6>>
exec operation: 3 (0): 2
  result set: [*null] (0)
popTo: 2
pop: 1
pushPre: 2 (133)
 @ 179 (134): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>> + 4*<f-vp: *<var#3>*<var#7>> + 3*<f-vp: *<var#4>*<var#8>> + 3*<f-vp: *<var#4>*<var#8>> + 7*<f-vp: *<var#4>*<var#9>> + 3*<f-vp: *<var#5>*<var#7>> + 3*<f-vp: *<var#5>*<var#9>> + 8*<f-vp: *<var#6>*<var#7>>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (134)
 @ 180 (134): ASSIGN - RHSONLY: 8192, 1
 @ 181 (134):     (argNo2) 3, 0
  cntLhs 0; assignConst 0; assignInitial 0; assignOrdered 0; setResName 1
  rhs = <f-lc:  + 3*<f-vp: *<var#1>*<var#5>> + 8*<f-vp: *<var#1>*<var#6>> + 3*<f-vp: *<var#2>*<var#4>> + 3*<f-vp: *<var#2>*<var#6>> + 7*<f-vp: *<var#3>*<var#4>> + 3*<f-vp: *<var#3>*<var#5>> + 4*<f-vp: *<var#1>*<var#5>> + 11*<f-vp: *<var#1>*<var#9>> + 4*<f-vp: *<var#2>*<var#7>> + 4*<f-vp: *<var#2>*<var#9>> + 9*<f-vp: *<var#3>*<var#7>> + 4*<f-vp: *<var#3>*<var#7>> + 3*<f-vp: *<var#4>*<var#8>> + 3*<f-vp: *<var#4>*<var#8>> + 7*<f-vp: *<var#4>*<var#9>> + 3*<f-vp: *<var#5>*<var#7>> + 3*<f-vp: *<var#5>*<var#9>> + 8*<f-vp: *<var#6>*<var#7>> + 3*<f-vp: *<var#6>*<var#8>>>
pushPre: 2 (134)
popTo: 1
pop: 0
 @ 182 (138): FETCH - GLOBAL: 0, 1
 @ 183 (138):     (argNo2) 108, 82
pushPre: 1 (138)
 @ 184 (139): FETCH - GLOBAL: 0, 1
 @ 185 (139):     (argNo2) 109, 83
pushPre: 2 (139)
 @ 186 (140): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <var#1: bin>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (140)
 @ 187 (141): FETCH - GLOBAL: 0, 1
 @ 188 (141):     (argNo2) 110, 84
pushPre: 2 (141)
 @ 189 (142): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#1> + <var#2>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (142)
 @ 190 (143): LIT_VAL - INT: 1, 0
pushPre: 2 (143)
 @ 191 (144): OPERATION - EQ: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#1> + <var#2> + <var#3>>
exec operation: 9 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (144)
 @ 192 (144): ASSIGN - RHSONLY: 8192, 1
 @ 193 (144):     (argNo2) 4, 0
  cntLhs 0; assignConst 0; assignInitial 0; assignOrdered 0; setResName 1
  rhs = <f-cmp: <f-lc:  + <var#1> + <var#2> + <var#3>> = 1>
pushPre: 2 (144)
popTo: 1
pop: 0
 @ 194 (146): FETCH - GLOBAL: 0, 1
 @ 195 (146):     (argNo2) 111, 85
pushPre: 1 (146)
 @ 196 (147): FETCH - GLOBAL: 0, 1
 @ 197 (147):     (argNo2) 112, 86
pushPre: 2 (147)
 @ 198 (148): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <var#4: bin>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (148)
 @ 199 (149): FETCH - GLOBAL: 0, 1
 @ 200 (149):     (argNo2) 113, 87
pushPre: 2 (149)
 @ 201 (150): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#4> + <var#5>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (150)
 @ 202 (151): LIT_VAL - INT: 1, 0
pushPre: 2 (151)
 @ 203 (152): OPERATION - EQ: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#4> + <var#5> + <var#6>>
exec operation: 9 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (152)
 @ 204 (152): ASSIGN - RHSONLY: 8192, 1
 @ 205 (152):     (argNo2) 4, 0
  cntLhs 0; assignConst 0; assignInitial 0; assignOrdered 0; setResName 1
  rhs = <f-cmp: <f-lc:  + <var#4> + <var#5> + <var#6>> = 1>
pushPre: 2 (152)
popTo: 1
pop: 0
 @ 206 (154): FETCH - GLOBAL: 0, 1
 @ 207 (154):     (argNo2) 114, 88
pushPre: 1 (154)
 @ 208 (155): FETCH - GLOBAL: 0, 1
 @ 209 (155):     (argNo2) 115, 89
pushPre: 2 (155)
 @ 210 (156): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <var#7: bin>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (156)
 @ 211 (157): FETCH - GLOBAL: 0, 1
 @ 212 (157):     (argNo2) 116, 90
pushPre: 2 (157)
 @ 213 (158): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#7> + <var#8>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (158)
 @ 214 (159): LIT_VAL - INT: 1, 0
pushPre: 2 (159)
 @ 215 (160): OPERATION - EQ: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#7> + <var#8> + <var#9>>
exec operation: 9 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (160)
 @ 216 (160): ASSIGN - RHSONLY: 8192, 1
 @ 217 (160):     (argNo2) 4, 0
  cntLhs 0; assignConst 0; assignInitial 0; assignOrdered 0; setResName 1
  rhs = <f-cmp: <f-lc:  + <var#7> + <var#8> + <var#9>> = 1>
pushPre: 2 (160)
popTo: 1
pop: 0
 @ 218 (162): FETCH - GLOBAL: 0, 1
 @ 219 (162):     (argNo2) 108, 82
pushPre: 1 (162)
 @ 220 (163): FETCH - GLOBAL: 0, 1
 @ 221 (163):     (argNo2) 111, 85
pushPre: 2 (163)
 @ 222 (164): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <var#1: bin>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (164)
 @ 223 (165): FETCH - GLOBAL: 0, 1
 @ 224 (165):     (argNo2) 114, 88
pushPre: 2 (165)
 @ 225 (166): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#1> + <var#4>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (166)
 @ 226 (167): LIT_VAL - INT: 1, 0
pushPre: 2 (167)
 @ 227 (168): OPERATION - EQ: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#1> + <var#4> + <var#7>>
exec operation: 9 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (168)
 @ 228 (168): ASSIGN - RHSONLY: 8192, 1
 @ 229 (168):     (argNo2) 4, 0
  cntLhs 0; assignConst 0; assignInitial 0; assignOrdered 0; setResName 1
  rhs = <f-cmp: <f-lc:  + <var#1> + <var#4> + <var#7>> = 1>
pushPre: 2 (168)
popTo: 1
pop: 0
 @ 230 (170): FETCH - GLOBAL: 0, 1
 @ 231 (170):     (argNo2) 109, 83
pushPre: 1 (170)
 @ 232 (171): FETCH - GLOBAL: 0, 1
 @ 233 (171):     (argNo2) 112, 86
pushPre: 2 (171)
 @ 234 (172): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <var#2: bin>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (172)
 @ 235 (173): FETCH - GLOBAL: 0, 1
 @ 236 (173):     (argNo2) 115, 89
pushPre: 2 (173)
 @ 237 (174): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#2> + <var#5>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (174)
 @ 238 (175): LIT_VAL - INT: 1, 0
pushPre: 2 (175)
 @ 239 (176): OPERATION - EQ: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#2> + <var#5> + <var#8>>
exec operation: 9 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (176)
 @ 240 (176): ASSIGN - RHSONLY: 8192, 1
 @ 241 (176):     (argNo2) 4, 0
  cntLhs 0; assignConst 0; assignInitial 0; assignOrdered 0; setResName 1
  rhs = <f-cmp: <f-lc:  + <var#2> + <var#5> + <var#8>> = 1>
pushPre: 2 (176)
popTo: 1
pop: 0
 @ 242 (178): FETCH - GLOBAL: 0, 1
 @ 243 (178):     (argNo2) 110, 84
pushPre: 1 (178)
 @ 244 (179): FETCH - GLOBAL: 0, 1
 @ 245 (179):     (argNo2) 113, 87
pushPre: 2 (179)
 @ 246 (180): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <var#3: bin>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (180)
 @ 247 (181): FETCH - GLOBAL: 0, 1
 @ 248 (181):     (argNo2) 116, 90
pushPre: 2 (181)
 @ 249 (182): OPERATION - ADD: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#3> + <var#6>>
exec operation: 1 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (182)
 @ 250 (183): LIT_VAL - INT: 1, 0
pushPre: 2 (183)
 @ 251 (184): OPERATION - EQ: 2, 0
stackPrev: 1
  -> <f-lc:  + <var#3> + <var#6> + <var#9>>
exec operation: 9 (0): 2
  result set: [*null] (0)
popTo: 1
pop: 0
pushPre: 1 (184)
 @ 252 (184): ASSIGN - RHSONLY: 8192, 1
 @ 253 (184):     (argNo2) 4, 0
  cntLhs 0; assignConst 0; assignInitial 0; assignOrdered 0; setResName 1
  rhs = <f-cmp: <f-lc:  + <var#3> + <var#6> + <var#9>> = 1>
pushPre: 2 (184)
popTo: 1
pop: 0
 @ 254 (186): FUNCTION - END: 0, 0
leave execution context (level 0) at code pos 254
run all extensions:  interpret (4308616688) 361
 extension linearSos: end
Model type: 4 (vartypes:2, conditions:0, varprodInt:1, varprodReal:0, sos:0)
run all extensions:  interpret (4308616688) 371
 extension SolverSelect: 371 28
  init model type and extensions
  read config file: /Users/mike/Documents/Projekte/Cmpl2/bin/solversel.opt
  search for initial section []
  line 1: start of section []
   line 4 (LP[..., sos!] || MIP[..., sos!] || QP) -> false
   line 5 (last) -> false
   line 8 (LP || MIP) -> true
    action: -solver CBC
    insert string 'solver' as #7
run one extension:  interpret (4308616688) 300 28 for command line option solver (201, 8192)
 setOptionPrio solver: 8192
    insert string 'solver' as #44
 extension SolverSelect: end
run all extensions:  interpret (4308616688) 391
 extension boundRow: matrix remodeling: 391 29
 start remodelations (without parallel threads)
 executed 0 remodelations
 extension boundRow: end
 extension linearSos: matrix remodeling: 391 30
 extension linearSos: end
 extension linearVarProd: matrix remodeling: 391 33
 start remodelations (without parallel threads)
    insert string '__x1A_x2B' as #154
    insert string '__line8' as #155
    insert string '__line9' as #156
    insert string '__line10' as #157
    insert string '__x1A_x2C' as #158
    insert string '__line11' as #159
    insert string '__line12' as #160
    insert string '__line13' as #161
    insert string '__x1B_x2A' as #162
    insert string '__line14' as #163
    insert string '__line15' as #164
    insert string '__line16' as #165
    insert string '__x1B_x2C' as #166
    insert string '__line17' as #167
    insert string '__line18' as #168
    insert string '__line19' as #169
    insert string '__x1C_x2A' as #170
    insert string '__line20' as #171
    insert string '__line21' as #172
    insert string '__line22' as #173
    insert string '__x1C_x2B' as #174
    insert string '__line23' as #175
    insert string '__line24' as #176
    insert string '__line25' as #177
    insert string '__x1A_x3C' as #178
    insert string '__line26' as #179
    grow strings array from 180 to 210
    insert string '__line27' as #180
    insert string '__line28' as #181
    insert string '__x1B_x3A' as #182
    insert string '__line29' as #183
    insert string '__line30' as #184
    insert string '__line31' as #185
    insert string '__x1B_x3C' as #186
    insert string '__line32' as #187
    insert string '__line33' as #188
    insert string '__line34' as #189
    insert string '__x1C_x3A' as #190
    insert string '__line35' as #191
    insert string '__line36' as #192
    insert string '__line37' as #193
    insert string '__x2A_x3B' as #194
    insert string '__line38' as #195
    insert string '__line39' as #196
    insert string '__line40' as #197
    insert string '__x2A_x3C' as #198
    insert string '__line41' as #199
    insert string '__line42' as #200
    insert string '__line43' as #201
    insert string '__x2B_x3A' as #202
    insert string '__line44' as #203
    insert string '__line45' as #204
    insert string '__line46' as #205
    insert string '__x2B_x3C' as #206
    insert string '__line47' as #207
    insert string '__line48' as #208
    insert string '__line49' as #209
    grow strings array from 210 to 240
    insert string '__x2C_x3A' as #210
    insert string '__line50' as #211
    insert string '__line51' as #212
    insert string '__line52' as #213
    insert string '__x2C_x3B' as #214
    insert string '__line53' as #215
    insert string '__line54' as #216
    insert string '__line55' as #217
 executed 0 remodelations
 extension linearVarProd: end
 extension linearConstantRow: matrix remodeling: 391 34
 start remodelations (without parallel threads)
 executed 0 remodelations
 extension linearConstantRow: end
 extension linearLogCon: matrix remodeling: 391 35
 start remodelations (without parallel threads)
 executed 0 remodelations
 extension linearLogCon: end
run all extensions:  interpret (4308616688) 361
 extension linearSos: end
Model type: 2 (vartypes:2, conditions:0, varprodInt:0, varprodReal:0, sos:0)
popTo: 1
pop: 0
End run interpreter module interpret
delete module class after run: interpret
construct module class: writeMps
parse command line options for module: writeMps
    insert string 'm' as #8
 setOptionPrio m: 12288
 setOptionPrio p: 12288
run module: writeMps
    insert string 'writeMps' as #218
Start run module writeMps
run all extensions:  writeMps (4308616736) 401
 extension linearSos: end
write model to file '10_Beispiel_Rost.mps' (standard MPS format)
get linear model
