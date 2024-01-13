#include <windows.h>
#include <stdio.h>
#include <assert.h>

#include "types.cpp"
#include "wow\entities.cpp"
#include "wow\object_manager.cpp"
#include "wow\globals.cpp"
#include "wow\functions.cpp"
#include "window.cpp"

// TODO: Find out the right way to this so that I don't need to write assembly
ObjectManager *get_obj_mgr() {
    __asm {
        mov ecx,dword ptr fs:[0x2C]
        mov eax,dword ptr ds:[0xD439BC]
        mov edx,dword ptr ds:[ecx+eax*4]
        mov eax,dword ptr ds:[edx+8]
    }
}

b32 log_entity(u64 guid, u32 filter) {
    WoWObject *obj = ClntObjMgrObjectPtr(guid, TYPEMASK_ALL);
    ConsolePrintf("ptr: 0x%x", obj);
    ConsolePrintf("guid: %llu", guid);
    ConsolePrintf("type: %s", obj_type_str[obj->type]);
    if (obj->type == OT_PLAYER || obj->type == OT_UNIT) {
        auto unit = (Unit *) obj;
        auto pos = unit->position;
        ConsolePrintf("position: %.2f %.2f %.2f", pos.x, pos.y, pos.z);
    }
    ConsolePrintf(" ");
    return 1;
}

b32 say_hi(u64 guid, u32 filter) {
    WoWObject *obj = ClntObjMgrObjectPtr(guid, TYPEMASK_ALL);
    static char buf[255];
    if (obj->type == OT_UNIT) {
        sprintf(buf, "0x%x", (u32)obj);
        ChatBubbleShow((Unit*)obj, 1, buf);
    }

    return 1;
}

void log_all_visible_entities() {
    ObjectManager *obj_mgr = get_obj_mgr();
    WoWObject *obj = obj_mgr->visibleObjects;

    while (obj && ((u32)obj & 1 == 0)) {
        ConsolePrintf("ptr 0x%s", obj);
        u32 unknown = *(u32*)((u32)obj_mgr+0xA4);
        obj = *(WoWObject**)((u32)obj + unknown + 4);
    }
}

void tick() {
    static bool done = false;
    
    if (!done) {
        log_all_visible_entities();
    }
}

#define TICK_DELAY 300

u32 start(HMODULE parameter) {
    *s_consoleActive = true;
    *s_consoleOpen = true;
    *s_consoleSize = 1.0;
    ConsolePrintf("Starting up loader...");

    for (;;) {
        if (GetAsyncKeyState(VK_END) & 0x1) break;

        Window::run_on_wndproc(tick);

        Sleep(TICK_DELAY);
    }

    *s_consoleActive  = true;
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
        Window::dettach();
        break;
    }
    return true;
}
