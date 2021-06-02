@echo off
if NOT exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /LD -DSOKOL_GLCORE33 main.cpp gui.cpp imgui\imgui_app.cpp utils.cpp user32.lib gdi32.lib /Zi /link /OUT:..\bin\kronos.dll
