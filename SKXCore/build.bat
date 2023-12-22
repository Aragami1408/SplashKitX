REM Build script for SplashKitX Engine
REM @ECHO OFF
SetLocal EnableDelayedExpansion

call vcvarsall.bat x64
SET cc=clang

REM Get a list of all the .cpp files
SET cFilenames=
FOR /R %%f in (*.cpp) do (
	SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=SKXCore

if %cc% == cl.exe (
		SET compilerFlags=/Zc:preprocessor /wd4090 /wd5105
		SET includeFlags=/I.\src\ /I%VULKAN_SDK%\Include
		SET linkerFlags=/link /DEBUG user32.lib vulkan-1.lib /LIBPATH:%VULKAN_SDK%\Lib
		SET defines=/D_DEBUG /DSKX_EXPORT /D_CRT_SECURE_NO_WARNINGS
		SET output=/Fe..\bin\%assembly%.lib
)

if %cc% == clang (
		SET compilerFlags=-g -shared -Wvarargs -Wall -Werror
		SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
		SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib
		SET defines=-D_DEBUG -DSKX_EXPORT -D_CRT_SECURE_NO_WARNINGS
		SET output= -o ../bin/%assembly%.lib
)


ECHO "Building %assembly%..."
%cc% %cFilenames% %compilerFlags% %output% %defines% %includeFlags% %linkerFlags%
