#pragma once
#include <unordered_map>

#include "type.h"

enum Entity_Type {
    ET_NONE = 0,  
    ET_ITEM = 1,  
    ET_CONTAINER = 2,  
    ET_UNIT = 3,  
    ET_PLAYER = 4,  
    ET_GAMEOBJ = 5,  
    ET_DYNOBJ = 6,  
    ET_CORPSE = 7,
};

struct Entity {
    u32 base_addr;
    Entity_Type type;
};

struct Entity_Manager {
    std::unordered_map<u64, Entity> entities; 

    void populate_lists();
};
