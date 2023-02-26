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

typedef struct {float x, y, z;} Vec3;

typedef u8* Entity;

void log_entity_list();
void populate_entity_list();
inline u64 get_guid(Entity ent);
inline Entity_Type get_type(Entity ent);
inline b32 is_active_player(Entity ent);
