#include <windows.h>
#include "object_manager.h"
#include "mem.h"
#include "commands.h"
#include "wow.h"

HMODULE module_handle;
Object_Manager obj_mgr;

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	module_handle = module;
	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		WoW::ConsolePrintf("Dll injected!");

		u8 arr[] = {0x45};
		mem_write((u8*)0x6571D1, arr, 1);

		WoW::ConsoleCommandRegister("objs", objs, 0, 0, 0);
		WoW::ConsoleCommandRegister("unload", unload, 0, 0, 0);
		WoW::ConsoleCommandRegister("sayhi", sayhi, 0, 0, 0);
	} break;
	case DLL_PROCESS_DETACH:
		WoW::ConsolePrintf("Dll unloaded!");
		break;
	}
	return TRUE;
}
