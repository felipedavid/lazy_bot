#pragma once
#include "defs.h"

enum Object_Type {
	ENTITY_TYPE_NONE,
	ENTITY_TYPE_ITEM,
	ENTITY_TYPE_CONTAINER,
	ENTITY_TYPE_UNIT,
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_GAMEOBJ,
	ENTITY_TYPE_DYNOBJ,
	ENTITY_TYPE_CORPSE,
};

struct Object {
	u32 ptr;
	unsigned long long guid;
	Object_Type type;
};

void populate_objs();
