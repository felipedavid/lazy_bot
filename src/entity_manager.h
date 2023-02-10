#pragma once
#include "game_info.h"
#include "lazy_bot.h"
#include "utils.h"

typedef enum {
    ET_NONE       = 0,
    ET_ITEM       = 1,
    ET_CONTAINER  = 2,
    ET_NPC        = 3,
    ET_PLAYER     = 4,
    ET_GAME_OBJ   = 5,
    ET_DYN_OBJ    = 6,
    ET_CORPSE     = 7,
} Entity_Type;

typedef u32 Entity;
typedef Entity Item;
typedef Entity Container;
typedef Entity NPC;
typedef Entity Player;
typedef Entity Game_Object;
typedef Entity Dynamic_Object;
typedef Entity Corpse;

Entity_Type get_type(Entity ent);
u32 get_descriptor(Entity ent);
u64 get_guid(Entity ent);
i32 get_display_id(Entity ent);
u64 get_creator_guid(Entity ent);
void populate_entities();
void log_entities();