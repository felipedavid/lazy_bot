// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "wow.h"
#include "object_manager.h"
#include "windows.h"
#include "mem.h"

HMODULE module_handle;

int __cdecl list_objs(const char* cmd, const char* args) {
    populate_objs();
    return 1;
}

int __cdecl unload(const char* cmd, const char* args) {
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, module_handle, 0, NULL);
    return 1;
}

int sayhi() {
    ConsolePrintf("Hiiiiiiiiiiiii!!!!");
    return 1;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    module_handle = module;
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        u8 lul = 0x45;
        mem_write((u8*)0x6571D1, &lul, 1);
        ConsolePrintf("Registering command");
        ConsoleCommandRegister("objs", (void*)list_objs, 1, "does nothing", 0);
        ConsoleCommandRegister("unload", (void*)unload, 1, "Unloads the dll", 0);
        ConsoleCommandRegister("sayhi", (void*)sayhi, 1, "Just says hi", 0);
        break;
    }
    return TRUE;
}

