@echo off

if not exist "bin" (
    echo "Creating bin directory..."
    mkdir bin
)

set compiler_flags=/LD /DEBUG:FULL
set libraries=kernel32.lib user32.lib
set sources=..\src\main.cpp

echo "Building lazy.dll..."
pushd bin
cl.exe %compiler_flags% %sources% /Fe:lazy.dll /link %libraries%
popd bin
