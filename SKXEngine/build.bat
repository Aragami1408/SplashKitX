REM Build script for SplashKitX Engine
REM @ECHO OFF
SetLocal EnableDelayedExpansion

SET cc=clang

REM Get a list of all the .cpp files
SET cFilenames=
FOR /R %%f in (*.cpp) do (
	SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=SKXEngine

if %cc% == clang (
		SET compilerFlags=-g -shared -Wvarargs -Wall -Werror
		SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
		SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib
		SET defines=-D_DEBUG -DSKX_EXPORT -D_CRT_SECURE_NO_WARNINGS
		SET output= -o ../bin/%assembly%.lib
)


ECHO "Building %assembly%..."
%cc% %cFilenames% %compilerFlags% %output% %defines% %includeFlags% %linkerFlags%
