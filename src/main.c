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

int __stdcall log_object(u64 guid) {
    CGObject_C *obj = GetObjectPtr(guid);

    COLOR_T color = DEFAULT_COLOR;
    if (obj->type == ID_PLAYER) color = ERROR_COLOR;
    if (obj->type == ID_UNIT) color = WARNING_COLOR;

    if (obj->type != ID_PLAYER) return 1;

    ConsoleWriteA("Type: %s", color, OBJECT_TYPE_ID_STR[obj->type]);
    ConsoleWriteA("Pointer: 0x%x", color, obj);

    if (obj->type >= ID_UNIT && obj->type <= ID_CORPSE) {
        C3Vector pos = ((CGUnit_C *)obj)->m_currentPosition;
        ConsoleWriteA("Position: %.2f %.2f %.2f", color, pos.x, pos.y, pos.z);
    }
    ConsoleWrite(" ", color);

    return 1;
}

void doStuff(void* data) {
    ClntObjMgrEnumVisibleObjects(log_object, 0);
}

void init() {
    s_consoleEnabled = true;
}

void cleanup() {
    s_consoleEnabled = false;
}

u32 entry(HMODULE handle) {
    init();
    s_active = true;
    s_consoleHeight = 1;
    ConsoleWrite("Hello from lazybot!", WARNING_COLOR);

    HWND window = FindWindowA(NULL, "World of Warcraft");
    if (!window) {
        ConsoleWrite("Unable to find wow window. Leaving...", ERROR_COLOR);
        goto END;
    }

    while (true) {
        if (GetAsyncKeyState(VK_END) & 0x8000) break;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) doStuff(null);

        Sleep(80);
    }

END:
    cleanup();
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