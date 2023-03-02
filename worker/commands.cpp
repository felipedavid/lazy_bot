#include <Windows.h>
#include "commands.h"
#include "wow.h"
#include "object_manager.h"

extern HMODULE module_handle;
extern Object_Manager obj_mgr;

void unload() {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, module_handle, 0, NULL);
}

void sayhi() {
	WoW::ConsolePrintf("Hiiii!");
}

void objs() {
	obj_mgr.pulse();
	WoW::ConsolePrintf("Game objects:");
	for (auto obj : obj_mgr.game_objects) {
		WoW::ConsolePrintf("Ptr: 0x%x, Type: %d, GUID: %llu", obj.ptr, obj.type, obj.guid);
	}
	WoW::ConsolePrintf("Local player:");
	WoW::ConsolePrintf("Ptr: 0x%x, Type: %d, GUID: %llu", obj_mgr.me.ptr, obj_mgr.me.type, obj_mgr.me.guid);
}
