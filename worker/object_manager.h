#pragma once
#include "wow.h"
#include "vector"
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

	WoW_Object(u8 *ptr, u64 guid, Object_Type type);
	u8* get_descriptor();
};

struct WoW_GameObject : WoW_Object {
	WoW_GameObject(u8 *ptr, u64 guid, Object_Type type);
	u64 get_creator();
	GameObject_DisplayID get_display_id();
};

struct WoW_Unit : WoW_Object {

};

struct Player : WoW_Unit {

};

struct Local_Player : Player {
	const char* get_name();
};

struct Object_Manager {
	std::vector<WoW_GameObject> game_objects;
	Local_Player me;
	void pulse();
};