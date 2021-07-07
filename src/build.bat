if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /Zi /LD /EHsc main.cpp position.cpp bot.cpp sync_thread.cpp hacks.cpp game\objects\object.cpp game\objects\unit.cpp game\objects\local_player.cpp game\object_manager.cpp  game\functions.cpp memory_manager.cpp gui\imgui*.cpp gui\gui.cpp -o ..\bin\lazy_bot.dll /link user32.lib d3d9.lib 
