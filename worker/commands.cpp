#include <Windows.h>
#include "commands.h"
#include "wow.h"
#include "object_manager.h"
#include "mem.h"
#include "fisher.h"

extern HMODULE module_handle;
extern Object_Manager obj_mgr;
extern Fisher fisher;

void unload() {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, module_handle, 0, NULL);
}

void sayhi() {
	WoW::ConsolePrintf("Hiiii!");
}

void objs() {
	obj_mgr.pulse();
	WoW::ConsolePrintf("Game objects:");
	for (auto it : obj_mgr.game_objects) {
		auto obj = it.second;
		WoW::ConsolePrintf("Ptr: 0x%x, Type: %d, GUID: %llu", obj.ptr, obj.type, obj.guid);
	}
	//WoW::ConsolePrintf("Local player:");
	//WoW::ConsolePrintf("Ptr: 0x%x, Type: %d, GUID: %llu", obj_mgr.me.ptr, obj_mgr.me.type, obj_mgr.me.guid);
}

void test() {
	WoW::Spell_C_CastSpell(SPELLID_FISHING, 0, 0, 0, 0, 0, 0, 0);
}

void fish() {
	fisher.on = !fisher.on;
}

void setup_commands() {
	u8 arr[] = { 0x45 };
	mem_write((u8*)0x6571D1, arr, 1);

	WoW::ConsoleCommandRegister("objs", objs, 0, 0, 0);
	WoW::ConsoleCommandRegister("unload", unload, 0, 0, 0);
	WoW::ConsoleCommandRegister("sayhi", sayhi, 0, 0, 0);
	WoW::ConsoleCommandRegister("test", test, 0, 0, 0);
	WoW::ConsoleCommandRegister("fish", fish, 0, 0, 0);
}
