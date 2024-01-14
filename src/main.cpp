#include <windows.h>
#include <d3d9.h>
#include <stdio.h>
#include <assert.h>
#include <dxgi.h>

#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "types.cpp"
#include "wow\entities.cpp"
#include "wow\object_manager.cpp"
#include "wow\globals.cpp"
#include "wow\functions.cpp"
#include "window.cpp"
#include "ui.cpp"

void tick() {
}

u32 start(HMODULE parameter) {
    UI::hook();

    for (;;) {
        if (GetAsyncKeyState(VK_END) & 0x1) break;

        Window::run_on_wndproc(tick);

        Sleep(300);
    }

    ConsolePrintf("Cleanning thing up, bye bye.");
    FreeLibraryAndExitThread(parameter, 0);
    return true;
}

b32 DllMain(HINSTANCE inst, u32 reason, void *reserved) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        Window::attach(FindWindowA(NULL, "World of Warcraft")); 
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start, inst, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        UI::unhook();
        Window::dettach();
        break;
    }
    return true;
}
