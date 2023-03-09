#include "pch.h"
#include "offsets.h"
#include "wow.h"

namespace WoW {
	_ConsolePrintf ConsolePrintf = (_ConsolePrintf)CONSOLEPRINTF_FUN_PTR;
	_ConsoleCommandRegister ConsoleCommandRegister = (_ConsoleCommandRegister)CONSOLECOMMANDREGISTER_FUN_PTR;
	_ConsoleCommandUnregister ConsoleCommandUnregister = (_ConsoleCommandUnregister)CONSOLECOMMANDUNREGISTER_FUN_PTR;
	_Spell_C_CastSpell Spell_C_CastSpell = (_Spell_C_CastSpell)SPELL_C_CASTSPELL_FUN_PTR;
	_ClntObjMgrObjectPtr ClntObjMgrObjectPtr = (_ClntObjMgrObjectPtr)CLNTOBJMGROBJECTPTR_FUN_PTR;
	_CGGameObject_C__OnRightClick CGGameObject_C__OnRightClick = (_CGGameObject_C__OnRightClick)CGGAMEOBJECT_C__ONRIGHTCLICK_FUN_PTR;
	_CVar__Register CVar__Register = (_CVar__Register)CVAR__REGISTER_FUN_PTR;
	_CVar__Lookup CVar__Lookup = (_CVar__Lookup)CVAR__LOOKUP_FUN_PTR;
	_ConsoleWrite ConsoleWrite = (_ConsoleWrite) CONSOLEWRITE_FUN_PTR;
}
