#pragma once
#include "vector"
#include "defs.h"

enum Object_Type {
	OBJECT_TYPE_NONE,
	OBJECT_TYPE_ITEM,
	OBJECT_TYPE_CONTAINER,
	OBJECT_TYPE_UNIT,
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_GAME_OBJECT,
	OBJECT_TYPE_GAME_DYNAMIC_OBJECT,
	OBJECT_TYPE_CORPSE,
};

struct WoW_Object {
	u8 *ptr;
	u64 guid;
	Object_Type type;
};

struct Object_Manager {
	std::vector<WoW_Object> objs;
	void refresh();
};