@echo off
rem Gurobi fuer cmpl: braucht ein Python mit gurobipy
if "%PYTHONBIN%"=="" set "PYTHONBIN=python"
"%PYTHONBIN%" "%~dp0gurobiCmpl.py" %*
