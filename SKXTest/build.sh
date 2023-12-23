#!/bin/bash
# Build script for SKXTest
set echo on

mkdir -p ../bin

cc=clang

# Get a list of all the .cpp files.
cFilenames=$(find . -type f -name "*.cpp")

# echo "Files:" $cFilenames

assembly="SKXTest"
compilerFlags="-g -fdeclspec -fPIC -std=c++17" 
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I../SKXCore/src/"
linkerFlags="-L../bin/ -lSKXCore -Wl,-rpath,."
defines="-D_DEBUG -DSKX_IMPORT"

echo "Building $assembly..."
echo clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
