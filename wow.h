#pragma once
#include "defs.h"

struct CVar {
	u8 unknown[40];
	char* value;
};

namespace WoW {
	typedef const char *(*_ConsolePrintf)(const char *format, ...); 
	typedef const char *(*_ConsoleCommandRegister)(const char *command, void *callback, u32 a1, u32 a2, u32 a3); 
	typedef const char *(__cdecl *_ConsoleCommandUnregister)(const char *command); 
	typedef u32 (__cdecl *_Spell_C_CastSpell)(u32 spell_id, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7, u32 a8); 
	typedef u8 *(*_ClntObjMgrObjectPtr)(u64 guid, u32 obj_type_mask); 
	typedef u32 (__fastcall *_CGGameObject_C__OnRightClick)(void *thiss);
	typedef u32 *(__cdecl *_CVar__Register)(const char *name, const char *help, u32 a3, const char *value, void *callback, u32 a6, char a7, u32 a8, char a9);
	typedef CVar *(__cdecl *_CVar__Lookup)(const char *var_name);
	typedef void (__cdecl *_ConsoleWrite)(const char *str, int color);

	extern _ConsolePrintf ConsolePrintf;
	extern _ConsoleCommandRegister ConsoleCommandRegister;
	extern _ConsoleCommandUnregister ConsoleCommandUnregister;
	extern _Spell_C_CastSpell Spell_C_CastSpell;
	extern _ClntObjMgrObjectPtr ClntObjMgrObjectPtr;
	extern _CGGameObject_C__OnRightClick CGGameObject_C__OnRightClick;
	extern _CVar__Register CVar__Register;
	extern _CVar__Lookup CVar__Lookup;
	extern _ConsoleWrite ConsoleWrite;
}
