#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.c"
#include "wow/types.c"
#include "wow/offsets.c"
#include "wow/static.c"
#include "wow/functions.c"


#define WM_RUN_CODE (WM_USER + 0x1234)

typedef void (*MainThreadCallback)(void*);

typedef struct {
    MainThreadCallback callback;
    void* user_data;
} MainThreadTask;

WNDPROC g_OriginalWndProc = NULL;


LRESULT CALLBACK HookedWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_RUN_CODE) {
        MainThreadTask* task = (MainThreadTask*)lParam;
        if (task && task->callback) {
            task->callback(task->user_data);
        }
        free(task);
        return 0;
    }

    return CallWindowProc(g_OriginalWndProc, hwnd, msg, wParam, lParam);
}

void hookWindowProc(HWND hwnd) {
    if (g_OriginalWndProc == NULL) {
        g_OriginalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
    }
}

void runMainThread(HWND hwnd, MainThreadCallback fn, void* data) {
    MainThreadTask* task = (MainThreadTask*)malloc(sizeof(MainThreadTask));
    if (!task) return;

    task->callback = fn;
    task->user_data = data;

    PostMessage(hwnd, WM_RUN_CODE, 0, (LPARAM)task);
}

void doStuff(void* data) {
    u64 player_guid = ClntObjMgrGetActivePlayer();
    CGPlayer_C *player = GetObjectPtr(player_guid);
    C3Vector pos = ((CGUnit_C *)player)->m_currentPosition;

    ConsoleWriteA("Active Player: %llu", ERROR_COLOR, player_guid);
    ConsoleWriteA("Ptr: 0x%x", ERROR_COLOR, player);
    ConsoleWriteA("Position: X=%.2f Y=%.2f Z=%.2f\n", ERROR_COLOR, pos.x, pos.y, pos.z);
}

u32 entry(HMODULE handle) {
    s_active = 1;
    s_consoleHeight = 1;
    ConsoleWrite("Hello from lazybot!", WARNING_COLOR);

    doStuff(null);

    while (true) {
        if (GetAsyncKeyState(VK_END) & 0x8000) break;
        if (GetAsyncKeyState(VK_UP) & 0x8000) doStuff(null);

        Sleep(80);
    }

    ConsoleWrite("Goodbye.", ERROR_COLOR);

    FreeLibraryAndExitThread(handle, 0);
}

BOOL WINAPI DllMain(HINSTANCE instance, u32 reason, void *reserved) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(null, 0, (LPTHREAD_START_ROUTINE)entry, instance, 0, null);
        break;
    }

    return true;
}