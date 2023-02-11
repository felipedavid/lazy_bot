#include <windows.h>
#include <stdio.h>
#include "fishing.h"
#include "common.h"

// temporary
#include "game_info.h"
#include "function_wrappers.h"

WNDPROC old_wnd_proc;

LRESULT new_wnd_proc(HWND wnd, u32 msg, u32 w_param, u32 l_param) {
    if (msg == WM_USER) {
        typedef void (*_procedure)();
		_procedure procedure = (_procedure)w_param;
		procedure();
    }

    return CallWindowProc(old_wnd_proc, wnd, msg, w_param, l_param);
}

void run_on_main_thread(void *procedure) {
    HWND wnd = FindWindowA(NULL, "World of Warcraft");
    SendMessage(wnd, WM_USER, (u32)procedure, 0);
}

void start(HMODULE h) {
    buf_test();
    AllocConsole();
    FILE *f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    HWND wnd = FindWindowA(NULL, "World of Warcraft");
    old_wnd_proc = (WNDPROC)SetWindowLongPtr(wnd, GWL_WNDPROC, (LONG_PTR)new_wnd_proc);

    bool running = false;
    while (TRUE) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_HOME) & 1) {
            running = !running;
        }

        if (running) {
            run_on_main_thread(pulse);
        }

        Sleep(100);
    }

    SetWindowLongPtr(wnd, GWL_WNDPROC, (LONG_PTR)old_wnd_proc);

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(h, 0);
}

BOOL DllMain(HINSTANCE inst, u32 reason, void *reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start, inst, 0, NULL);
    }
    return TRUE;
}
