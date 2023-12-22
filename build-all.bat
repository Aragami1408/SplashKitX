@ECHO OFF
REM Build Everything

ECHO "Building everything..."

IF NOT EXIST bin mkdir bin

PUSHD SKXCore
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && pause)

PUSHD SKXTest
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && pause)

ECHO "All assemblies built successfully."
