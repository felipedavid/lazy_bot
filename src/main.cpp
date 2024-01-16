#include <windows.h>
#include <d3d9.h>
#include <stdio.h>
#include <assert.h>
#include <dxgi.h>
#include <vector>

#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "types.cpp"
#include "wow\entity_fields.cpp"
#include "wow\entities.cpp"
#include "wow\object_manager.cpp"
#include "wow\globals.cpp"
#include "wow\functions.cpp"
struct EntityManager {
    u64 visibleObjs[4096];
    size_t objsLen = 0;
};

bool lazy_fish_running = true;
EntityManager entityManager;

#include "window.cpp"
#include "gui.cpp"
#include "directx_hook.cpp"

void refresh(EntityManager *entMgr) {
    entMgr->objsLen = 0;

    auto objMgr = getObjectManager();
    WoWObject *obj = objMgr->visibleObjects;

    while (obj && (((u32)obj & 1) == 0)) {
        u64 guid  = *(u64*)(obj->objectFields+OBJECT_FIELD_GUID);

        entMgr->visibleObjs[entMgr->objsLen++] = guid;

        u32 obj_mgr_unk_field = *(u32*)((u32)objMgr+0xA4);
        obj = *(WoWObject**)((u32)obj + obj_mgr_unk_field + 4);
    }
}

void refresh_target() {
    u64 guid = *s_currentTargetGUID ;
    *s_currentTargetGUID = 0;
    CGameUI__Target(guid);
}

void tick() {
    refresh_target();
    refresh(&entityManager);
}

u32 sneakyThreadEntryPoint(HMODULE module) {
    hookDirectX();
    takeoverWindowProc(getProcessWindow()); 

    while (lazy_fish_running) {
        runCodeOnMainThread(tick);
        Sleep(300);
    }

    givebackWindowProc();
    unhookDirectX();

    FreeLibraryAndExitThread(module, 0);
    return true;
}

b32 DllMain(HMODULE module, u32 reason, void *reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sneakyThreadEntryPoint, module, 0, NULL);
    }
    return true;
}
