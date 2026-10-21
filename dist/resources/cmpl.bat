@echo off
rem Cmpl 2 - Startskript fuer Windows (Gegenstueck zum bash-Skript cmpl)
rem
rem Laeuft cmpl zuerst nur mit dem Precompiler, entscheidet cmplStarter
rem anhand der erzeugten Dateien, ob lokal, mit CmplXlsData oder ueber
rem einen CmplServer geloest wird.

setlocal

set "CMPLHOME=%~dp0"
set "PATH=%CMPLHOME%;%PATH%"
set "PYTHONPATH=%CMPLHOME%pyCmpl\lib3;%PYTHONPATH%"

rem cmplStarter ist mit Nuitka kompiliert, Python nur als Fallback
set "CMPLSTARTERBIN=%CMPLHOME%bin\cmplStarter.dist\cmplStarter.exe"
if "%PYTHONBIN%"=="" set "PYTHONBIN=python"

if "%~1"=="" (
	"%CMPLHOME%bin\cmpl.exe"
	exit /b %ERRORLEVEL%
)

set "outAlias=cmpl__%RANDOM%%RANDOM%__"

"%CMPLHOME%bin\cmpl.exe" %* -o-opt "%outAlias%.optcmpl" -o-pre "%outAlias%.precmpl" -o-extern "%outAlias%.extdata" -modules precomp -no-warn-unused

if not exist "%outAlias%.optcmpl" exit /b %ERRORLEVEL%

if exist "%CMPLSTARTERBIN%" (
	"%CMPLSTARTERBIN%" "%outAlias%"
) else if exist "%CMPLHOME%bin\cmplStarter.py" (
	"%PYTHONBIN%" "%CMPLHOME%bin\cmplStarter.py" "%outAlias%"
) else (
	echo ERROR: cmplStarter not found ^<%CMPLSTARTERBIN%^> 1>&2
	exit /b 1
)

exit /b %ERRORLEVEL%
