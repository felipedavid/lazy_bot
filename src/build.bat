if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /Zi /LD main.cpp memory_manager.cpp game\object_manager.cpp game\functions.cpp game\objects\object.cpp user32.lib -o ..\bin\lazy_bot.dll
