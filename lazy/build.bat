@echo off
if NOT exist ..\build\ (
    mkdir ..\build\
)
cl.exe /LD main.c gui.c utils.c sync_thread.c game_functions.c bot.c memory_manager.c object_manager.c user32.lib gdi32.lib /Zi /link /OUT:..\build\lazy_bot.dll
