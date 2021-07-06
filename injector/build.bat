if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe main.cpp user32.lib advapi32.lib -o ..\bin\injector.exe
