#!/bin/bash
# Build script for SKXEngine
set echo on

mkdir -p ../bin

# Get a list of all the .cpp files.
cFilenames=$(find . -type f -name "*.cpp")

# echo "Files:" $cFilenames

assembly="SKXEngine"
compilerFlags="-g -shared -fdeclspec -fPIC -std=c++17 -Wno-deprecated-declarations"
# -fms-extensions
# -Wall -Werror
if [[ "$OSTYPE" == "darwin"* ]] ; then
    includeFlags="-Isrc -I$VULKAN_SDK/macOS/include"
    linkerFlags="-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L$VULKAN_SDK/macOS/lib -L/usr/X11R6/lib"
else
    includeFlags="-Isrc -I$VULKAN_SDK/include"
    linkerFlags="-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L$VULKAN_SDK/lib -L/usr/X11R6/lib"
fi
defines="-D_DEBUG -DSKX_EXPORT"

echo "Building $assembly..."
clang $cFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags
