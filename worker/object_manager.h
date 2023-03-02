#pragma once
#include "wow.h"
#include "map"
#include "defs.h"

enum Object_Type {
	OBJECT_TYPE_NONE,
	OBJECT_TYPE_ITEM,
	OBJECT_TYPE_CONTAINER,
	OBJECT_TYPE_UNIT,
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_GAMEOBJECT,
	OBJECT_TYPE_GAMEDYNAMICOBJECT,
	OBJECT_TYPE_CORPSE,
};

struct WoW_Object {
	u8 *ptr;
	u64 guid;
	Object_Type type;
	u8* descriptors_field;

	void init(u8 *ptr);
	u8* get_descriptor();
	bool is_valid();
};

struct WoW_GameObject : WoW_Object {
	u64 get_creator();
	GameObject_DisplayID get_display_id();
	u32 get_flags();
	int interact();
};

struct WoW_Unit : WoW_Object {
	bool is_casting(SpellID spell_id);
	SpellID get_channel_spell();
	u64 get_channel_object();
};

struct Player : WoW_Unit {

};

struct Active_Player : Player {
	void cast_spell(SpellID id);
};

struct Object_Manager {
	std::map<u64, WoW_GameObject> game_objects;
	Active_Player me;
	void pulse();
};