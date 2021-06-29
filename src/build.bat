if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /Zi /LD -DSOKOL_GLCORE33 main.cpp memory_manager.cpp game\object_manager.cpp game\functions.cpp game\objects\object.cpp game\objects\unit.cpp gui\imgui_app.cpp gui\gui.cpp user32.lib -o ..\bin\lazy_bot.dll
