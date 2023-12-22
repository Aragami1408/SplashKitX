REM Build script for testbed
@ECHO OFF
SetLocal EnableDelayedExpansion

call vcvarsall.bat x64
SET cc=clang

REM Get a list of all the .cpp files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=SKXTest

if %cc% == cl.exe (
		SET compilerFlags=/Zc:preprocessor /wd4090 /wd5105
		SET includeFlags=/I.\src\ /I..\SKXCore\src\
		SET linkerFlags=/LIBPATH:..\bin\ SKXCore.lib
		SET defines=/D_DEBUG /DSKX_IMPORT
		SET output=/Fe..\bin\%assembly%.exe
)

if %cc% == clang (
		SET compilerFlags=-g
		REM -Wall -Werror
		SET includeFlags=-Isrc -I../SKXCore/src/
		SET linkerFlags=-L../bin/ -lSKXCore
		SET defines=-D_DEBUG -DSKX_IMPORT
		SET output=-o ../bin/%assembly%.exe
)


ECHO "Building %assembly%%..."
%cc% %cFilenames% %compilerFlags% %output% %defines% %includeFlags% %linkerFlags%
