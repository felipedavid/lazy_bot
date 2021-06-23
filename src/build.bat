@echo off
if not exist ..\bin\ (
    mkdir ..\bin\
)

fxc.exe /nologo /T vs_4_0_level_9_0 /E vs /O3 /Zpc /Ges /Fh nuklear_d3d11_vertex_shader.h /Vn nk_d3d11_vertex_shader /Qstrip_reflect /Qstrip_debug /Qstrip_priv nuklear_d3d11.hlsl
fxc.exe /nologo /T ps_4_0_level_9_0 /E ps /O3 /Zpc /Ges /Fh nuklear_d3d11_pixel_shader.h /Vn nk_d3d11_pixel_shader /Qstrip_reflect /Qstrip_debug /Qstrip_priv nuklear_d3d11.hlsl

cl.exe /LD main.c gui.c user32.lib dxguid.lib d3d11.lib -o ..\bin\lazy_bot.dll
