@echo off
setlocal EnableDelayedExpansion

if not exist bin\ (
	mkdir bin
)

set c_filenames=
for /R %%f in (*.c) do (
    set c_filenames=!c_filenames! %%f
)

set assembly=potato
set compiler_flags=/LD
set linker_flags=/link user32.lib kernel32.lib

echo "Building %assembly%..."
cl %compiler_flags% %c_filenames% /Fe:bin\%assembly%.dll %linker_flags%

del *.obj
del *.pdb
