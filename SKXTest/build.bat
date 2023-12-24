REM Build script for testbed
@ECHO OFF
SetLocal EnableDelayedExpansion

SET cc=clang

REM Get a list of all the .cpp files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=SKXTest

if %cc% == clang (
		SET compilerFlags=-g
		REM -Wall -Werror
		SET includeFlags=-Isrc -I../SKXEngine/src/
		SET linkerFlags=-L../bin/ -lSKXEngine
		SET defines=-D_DEBUG -DSKX_IMPORT
		SET output=-o ../bin/%assembly%.exe
)


ECHO "Building %assembly%%..."
%cc% %cFilenames% %compilerFlags% %output% %defines% %includeFlags% %linkerFlags%
