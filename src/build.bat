if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /Zi /LD /EHsc main.cpp position.cpp game\objects\object.cpp game\objects\unit.cpp game\object_manager.cpp  memory_manager.cpp user32.lib -o ..\bin\lazy_bot.dll
