#pragma once
#include "defs.h"

enum SpellID {
	SPELLID_FISHING = 7620,
};

enum GameObject_DisplayID {
	GO_DISPLAYID_NONE = 0,
	GO_DISPLAYID_BOBBER = 668,
};

// from: https://github.com/TrinityCore/TrinityCore/blob/master/src/server/game/Miscellaneous/SharedDefines.h
enum GameObject_Flags {
	GO_FLAG_IN_USE                                  = 0x00000001, // disables interaction while animated
	GO_FLAG_LOCKED                                  = 0x00000002, // require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
	GO_FLAG_INTERACT_COND                           = 0x00000004, // cannot interact (condition to interact - requires GO_DYNFLAG_LO_ACTIVATE to enable interaction clientside)
	GO_FLAG_TRANSPORT                               = 0x00000008, // any kind of transport? Object can transport (elevator, boat, car)
	GO_FLAG_NOT_SELECTABLE                          = 0x00000010, // not selectable even in GM mode
	GO_FLAG_NODESPAWN                               = 0x00000020, // never despawn, typically for doors, they just change state
	GO_FLAG_AI_OBSTACLE                             = 0x00000040, // makes the client register the object in something called AIObstacleMgr, unknown what it does
	GO_FLAG_FREEZE_ANIMATION                        = 0x00000080,

	// for object types GAMEOBJECT_TYPE_GARRISON_BUILDING, GAMEOBJECT_TYPE_GARRISON_PLOT and GAMEOBJECT_TYPE_PHASEABLE_MO flag bits 8 to 12 are used as WMOAreaTable::NameSetID
	GO_FLAG_DAMAGED                                 = 0x00000200,
	GO_FLAG_DESTROYED                               = 0x00000400,

	GO_FLAG_IGNORE_CURRENT_STATE_FOR_USE_SPELL      = 0x00004000, // Allows casting use spell without checking current state (opening open gameobjects, unlocking unlocked gameobjects and closing closed gameobjects)
	GO_FLAG_INTERACT_DISTANCE_IGNORES_MODEL         = 0x00008000, // Client completely ignores model bounds for interaction distance check
	GO_FLAG_IGNORE_CURRENT_STATE_FOR_USE_SPELL_EXCEPT_UNLOCKED = 0x00040000, // Allows casting use spell without checking current state except unlocking unlocked gamobjets (opening open gameobjects and closing closed gameobjects)
	GO_FLAG_INTERACT_DISTANCE_USES_TEMPLATE_MODEL   = 0x00080000, // client checks interaction distance from model sent in SMSG_QUERY_GAMEOBJECT_RESPONSE instead of GAMEOBJECT_DISPLAYID
	GO_FLAG_MAP_OBJECT                              = 0x00100000, // pre-7.0 model loading used to be controlled by file extension (wmo vs m2)
	GO_FLAG_IN_MULTI_USE                            = 0x00200000, // GO_FLAG_IN_USE equivalent for objects usable by multiple players
	GO_FLAG_LOW_PRIORITY_SELECTION                  = 0x04000000, // client will give lower cursor priority to this object when multiple objects overlap
};

namespace WoW {
	typedef const char *(*_ConsolePrintf)(const char* format, ...); 
	typedef const char *(*_ConsoleCommandRegister)(const char *format, void *callback, int a1, int a2, int a3); 
	typedef int(__cdecl *_Spell_C_CastSpell)(SpellID spell, int a2, int a3, int a4, int a5, int a6, int a7, int a8); 
	typedef u8 *(*_ClntObjMgrObjectPtr)(u64 guid, int obj_type_mask); 
	typedef int (__fastcall *_CGGameObject_C__OnRightClick)(void *thiss);

	extern _ConsolePrintf ConsolePrintf;
	extern _ConsoleCommandRegister ConsoleCommandRegister;
	extern _Spell_C_CastSpell Spell_C_CastSpell;
	extern _ClntObjMgrObjectPtr ClntObjMgrObjectPtr;
	extern _CGGameObject_C__OnRightClick CGGameObject_C__OnRightClick;
}
