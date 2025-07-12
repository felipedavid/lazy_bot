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

void HookWndProc(HWND hwnd) {
    if (g_OriginalWndProc == NULL) {
        g_OriginalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
    }
}

void RunInMainThread(HWND hwnd, MainThreadCallback fn, void* data) {
    MainThreadTask* task = (MainThreadTask*)malloc(sizeof(MainThreadTask));
    if (!task) return;

    task->callback = fn;
    task->user_data = data;

    PostMessage(hwnd, WM_RUN_CODE, 0, (LPARAM)task);
}

    
void MyInjectedCallback(void* data) {
    u64 id = ClntObjMgrGetActivePlayer();
    u32 player = ClntObjMgrObjectPtr(id);

    ConsoleWriteA("Active Player: %llu", ERROR_COLOR, id);
    ConsoleWriteA("Ptr: 0x%x", ERROR_COLOR, player);
}

u32 entry(HMODULE handle) {
    s_active = 1;
    s_consoleHeight = 1;
    ConsoleWrite("Hello from lazybot!", WARNING_COLOR);

    HWND wowWindow = FindWindowA(NULL, "World of Warcraft");
    HookWndProc(wowWindow);

    while (true) {
        RunInMainThread(wowWindow, MyInjectedCallback, NULL);
        Sleep(100);
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