if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /Zi /LD /EHsc main.cpp bot.cpp entity_manager.cpp utils.cpp gui\gui.cpp gui\imgui.cpp gui\imgui_demo.cpp gui\imgui_draw.cpp gui\imgui_impl_dx9.cpp gui\imgui_impl_win32.cpp gui\imgui_tables.cpp gui\imgui_widgets.cpp -o ..\bin\lazy_bot.dll /link user32.lib d3d9.lib
cl.exe injector\injector.cpp user32.lib advapi32.lib -o ..\bin\injector.exe
