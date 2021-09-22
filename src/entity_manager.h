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
    // We only need the pointer to the base of the entity object
    // to obtein all info that we need.
    u32 base_addr;

    // Offsets
    static const u32 type_offset = 0x14;
    static const u32 guid_offset = 0x30;

    Entity(u32 base_addr);
    u64 Entity::get_guid();
    Entity_Type Entity::get_type();
};

struct Unit : public Entity {
    // Units store their details in a separate memory location.
    // We can get a pointer to that at offset "0x8".
    static const u32 descriptor_ptr_offset = 0x8;
    static const u32 health_offset = 0x58;
    static const u32 name_offset = 0xB30; 

    using Entity::Entity;
    u32 get_descriptor_ptr();
    int get_health();
    char *get_name();
};

struct Entity_Manager {
    std::vector<Unit> units;

    // Offsets
    static const u32 entity_manager_addr = 0xB41414;
    static const u32 first_entity_offset = 0xac;
    static const u32 next_entity_offset  = 0x3c;
    static const u32 descriptor_offset   = 0x8;
    static const u32 entity_type_offset  = 0x14;

    void populate_lists();
};
