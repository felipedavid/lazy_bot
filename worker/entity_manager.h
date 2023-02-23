#pragma once
#include "def.h"

typedef enum {
	ET_NONE,
	ET_ITEM,
	ET_CONTAINER,
	ET_UNIT,
	ET_PLAYER,
	ET_GAMEOBJ,
	ET_DYNOBJ,
	ET_CORPSE,
} Entity_Type;

typedef struct {
	u64 guid;
	u32 addr;
	Entity_Type type;
} Entity;

void log_entity_list();
void populate_entity_list();
