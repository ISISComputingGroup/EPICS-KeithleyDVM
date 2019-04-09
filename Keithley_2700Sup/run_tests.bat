:: Run all tests
@echo off
SET TOP="."

SET Tests_failed=%errorlevel%

:: Change the directory depending on if you have a src sub directory
call Keithley_2700Sup\src\O.windows-x64\runner.exe --gtest_output=xml:%TOP%\test-reports\TEST-Keithley_2700.xml

exit /B %Tests_failed%
