@echo off

if not exist "bin" (
    echo "Creating bin directory..."
    mkdir bin
)

set compiler_flags=/LD /DEBUG:FULL
set libraries=kernel32.lib user32.lib d3d9.lib d3dcompiler.lib dxgi.lib
set sources=..\src\kiero\minhook\src\hde\hde32.c ..\src\kiero\minhook\src\*.c ..\src\kiero\kiero.cpp ..\src\imgui\imgui*.cpp ..\src\main.cpp

echo "Building go_fish.dll..."
pushd bin
cl.exe %compiler_flags% %sources% /Fe:go_fish.dll /link %libraries%
popd bin
