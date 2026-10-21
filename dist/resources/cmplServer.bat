@echo off
rem Startet und steuert CmplServer bzw. CmplGridScheduler.
rem Logs und Problemdateien liegen in %USERPROFILE%\CmplServer.
rem
rem Der Server laeuft im Vordergrund - gestoppt wird er in einem zweiten
rem Fenster mit "cmplServer -stop [<port>]".

setlocal

set "CMPLHOME=%~dp0"
set "PYTHONPATH=%CMPLHOME%pyCmpl\lib3;%PYTHONPATH%"
if "%PYTHONBIN%"=="" set "PYTHONBIN=python"

set "serverOpt=%CMPLHOME%bin\cmplServer.opt"
set "serverBin=%CMPLHOME%bin\cmplServer.dist\cmplServer.exe"
set "serverHandler=%CMPLHOME%pyCmpl\lib3\cmplServer\cmplServerHandler.py"

if not exist "%serverOpt%" (
	echo CmplServer option file not found! ^<%serverOpt%^>
	exit /b 1
)

set "cmplPort=8008"
for /f "eol=# tokens=1,* delims== " %%a in ('findstr /i /r "^[ ]*cmplServerPort" "%serverOpt%"') do set "cmplPort=%%b"
if not "%~2"=="" set "cmplPort=%~2"

set "command=%~1"
if "%command%"=="-start" goto run
if "%command%"=="-startInGrid" goto run
if "%command%"=="-startScheduler" goto run
if "%command%"=="-stop" goto run
if "%command%"=="-status" goto run
goto usage

:run
if "%command%"=="-start" echo Starting CmplServer ... Please stop it with "cmplServer -stop %cmplPort%" in another terminal
if "%command%"=="-startInGrid" echo Starting CmplServer in CmplGrid ... Please stop it with "cmplServer -stop %cmplPort%" in another terminal
if "%command%"=="-startScheduler" echo Starting CmplGridScheduler ... Please stop it with "cmplServer -stop %cmplPort%" in another terminal

if exist "%serverBin%" (
	"%serverBin%" %command% %cmplPort%
) else if exist "%serverHandler%" (
	"%PYTHONBIN%" "%serverHandler%" %command% %cmplPort%
) else (
	echo ERROR: cmplServer not found ^<%serverBin%^> 1>&2
	exit /b 1
)
exit /b %ERRORLEVEL%

:usage
echo Usage: cmplServer ^<command^> [^<port^>]
echo command:
echo    -start           - starts as single CMPLServer
echo    -startInGrid     - starts CMPLServer and connects to CMPLGrid
echo    -startScheduler  - starts as CMPLGridScheduler
echo    -stop            - stops CMPLServer or CMPLGridScheduler
echo    -status          - returns the status of the CMPLServer or CMPLGridScheduler
echo port                - defines CMPLServer's or CMPLGridScheduler's port (default in cmplServer.opt: %cmplPort%)
exit /b 1
