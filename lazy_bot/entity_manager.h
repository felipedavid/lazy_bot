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
    // Offsets
    static const u32 type_offset = 0x14;
    static const u32 guid_offset = 0x30;

    // We only need the pointer to the base of the entity object
    // to obtein all info that we need.
    u32 base_addr;

    Entity(u32 base_addr);
    u64 get_guid();
    Entity_Type get_type();
};

struct Position {float x, y, z;};

struct Unit : public Entity {
    // Units store their details in a separate memory location.
    // We can get a pointer to that at offset "0x8".
    static const u32 descriptor_ptr_offset = 0x8;
    static const u32 health_offset         = 0x58;
    static const u32 name_offset           = 0xB30; 
    static const u32 position_offset       = 0x9B8;

    using Entity::Entity;
    u32 get_descriptor_ptr();
    int get_health();
    char *get_name();
    Position get_position();
};

struct Player : public Unit {
    static const u32 name_base_offset   = 0xC0E230;
    static const u32 next_name_offset   = 0xC;
    static const u32 player_name_offset = 0x14;

    using Unit::Unit;
    char *get_name();
};

struct Local_Player : public Player {
    static const u32 get_player_guid_fun_ptr = 0x00468550; // TODO: update this

    using Player::Player;
    u64 get_guid();
    float distance_to(Position pos);
};

struct Entity_Manager {
    // Offsets
    static const u32 client_connection_offset = 0x00C79CE0;
    static const u32 entity_manager_offset = 0x2ED0;
    static const u32 first_entity_offset = 0xac;
    static const u32 next_entity_offset  = 0x3c;
    static const u32 entity_type_offset  = 0x14;
    static const u64 entity_guid_offset  = 0xC0;

    std::unordered_map<u64, Unit> units;
    std::unordered_map<u64, Player> players;
    Local_Player local_player = 0;

    void populate_lists();
};
