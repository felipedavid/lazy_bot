@echo off
setlocal EnableDelayedExpansion

set c_filenames=
for /R %%f in (*.c) do (
    set c_filenames=!c_filenames! %%f
)

set assembly=bot
set compiler_flags=/LD /Zi
set linker_flags=/link user32.lib kernel32.lib

echo "Building %assembly%..."
cl %compiler_flags% %c_filenames% /Fe:bin\%assembly%.dll %linker_flags%

del *.obj
del *.pdb
