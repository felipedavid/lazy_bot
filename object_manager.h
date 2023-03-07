#pragma once
#include "defs.h"
#include "map"

enum Object_Type {
	OBJECT_TYPE_NONE,
	OBJECT_TYPE_ITEM,
	OBJECT_TYPE_CONTAINER,
	OBJECT_TYPE_UNIT,
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_GAMEOBJECT,
	OBJECT_TYPE_DYNAMICOBJECT,
	OBJECT_TYPE_CORPSE,
};

struct WoW_Object {
	u8 *ptr;
	u64 guid;
	u8 *descriptors;
	Object_Type type;

	void init(u8 *ptr, u64 guid, Object_Type type);
	b32 is_valid();
	void log();
};

struct WoW_GameObject : WoW_Object {

};

struct WoW_DynamicObject : WoW_Object {

};

struct WoW_Unit : WoW_Object {

};

struct WoW_Corpse : WoW_Object {

};

struct WoW_Item : WoW_Object {

};

struct WoW_Container : WoW_Item {

};

struct WoW_Player : WoW_Unit {

};

struct WoW_LocalPlayer : WoW_Player {

};

struct Object_Manager {
	std::map<u64, WoW_Item> items;
	std::map<u64, WoW_Player> players;
	std::map<u64, WoW_Container> containers;
	std::map<u64, WoW_Unit> units;
	std::map<u64, WoW_GameObject> game_objs;
	std::map<u64, WoW_DynamicObject> dyn_objs;
	std::map<u64, WoW_Corpse> corpses;

	WoW_LocalPlayer local_player;
	void populate_objects();
	void log();
};
