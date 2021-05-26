@echo off
if NOT exist ..\build\ (
    mkdir ..\build\
)
cl.exe injector.c user32.lib advapi32.lib /Zi /link /OUT:..\build\injector.exe
