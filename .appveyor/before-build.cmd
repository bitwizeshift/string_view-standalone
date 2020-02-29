SETLOCAL EnableDelayedExpansion

@REM  # Install 'conan' dependencies

mkdir build
cd build
conan install .. -g cmake

@REM  # Generate the CMake project

cmake .. -A%PLATFORM% -DBPSTD_COMPILE_UNIT_TESTS=On || exit /b !ERRORLEVEL!