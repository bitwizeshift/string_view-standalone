SETLOCAL EnableDelayedExpansion

@REM  # Test the project

ctest -j 4 -C %CONFIGURATION% || exit /b !ERRORLEVEL!