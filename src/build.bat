if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /Zi /LD /EHsc main.cpp game\position.cpp bot\bot.cpp utils\sync_thread.cpp utils\hacks.cpp game\objects\object.cpp game\objects\unit.cpp game\objects\local_player.cpp game\object_manager.cpp  game\functions.cpp utils\memory_manager.cpp gui\imgui*.cpp gui\gui.cpp -o ..\bin\lazy_bot.dll /link user32.lib d3d9.lib 
cl.exe injector\injector.cpp user32.lib advapi32.lib -o ..\bin\injector.exe