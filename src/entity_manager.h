#include <vector>

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
    static const u32 type_offset = 0x14;
    static const u32 guid_offset = 0x30;

    u64 guid;
    u32 pointer;
    Entity_Type type;

    Entity(u32 pointer);
};

struct Entity_Manager {
    static const u32 entity_manager_addr = 0x00B41414;
    static const u32 first_entity_offset = 0xac;
    static const u32 next_entity_offset  = 0x3c;
    static const u32 descriptor_offset   = 0x8;

    std::vector<Entity> entities;

    void populate_lists();
};
