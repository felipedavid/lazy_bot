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
#include "directx_hook.cpp"

void tick() {
}

u32 sneaky_thread_entry_point(HMODULE parameter) {
    takeover_window_proc(get_process_window()); 
    hook_directx();

    for (;;) {
        if (GetAsyncKeyState(VK_END) & 0x1) break;
        run_code_on_main_thread(tick);
        Sleep(300);
    }

    unhook_directx();
    giveback_window_proc();
    FreeLibraryAndExitThread(parameter, 0);
    return true;
}

b32 DllMain(HMODULE module, u32 reason, void *reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sneaky_thread_entry_point, module, 0, NULL);
    }
    return true;
}
