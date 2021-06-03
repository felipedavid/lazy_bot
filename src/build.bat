@echo off
if NOT exist ..\bin\ (
    mkdir ..\bin\
)
@set LIBS=user32.lib gdi32.lib
cl.exe /LD -DSOKOL_GLCORE33 main.cpp gui.cpp object_manager.cpp utils.cpp memory_manager.cpp game_functions.cpp imgui\imgui_app.cpp %LIBS% /Zi /link /OUT:..\bin\kronos.dll
