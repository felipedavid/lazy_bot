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

typedef struct {
    Entity_Type type;
    u32 base_addr;
} Entity;
