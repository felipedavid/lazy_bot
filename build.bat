@echo off

if not exist "bin" (
    echo "Creating bin directory..."
    mkdir bin
)

set compiler_flags=/LD
set linker_flags=/link kernel32.lib user32.lib

echo "Building go_fish.dll..."
pushd bin
cl.exe %compiler_flags% ..\src\main.cpp /Fe:go_fish.dll %linker_flags%
popd bin
