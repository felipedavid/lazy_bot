@echo off
if NOT exist ..\build\ (
    mkdir ..\build\
)
cl.exe /LD -DSOKOL_GLCORE33 main.cpp gui.cpp utils.cpp sync_thread.cpp game_functions.cpp bot.cpp memory_manager.cpp object_manager.cpp imgui\imgui_app.cpp state.cpp user32.lib gdi32.lib /Zi /link /OUT:..\build\lazy_bot.dll
