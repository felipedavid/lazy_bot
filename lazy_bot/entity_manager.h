#pragma once
#include <unordered_map>

#include "type.h"
#include "game.h"

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

struct Vec3 {float x, y, z;};

enum Dynamic_Flag {
    UNTOUCHED     =  0,
    CAN_BE_LOOTED =  1,
    IS_MARKED     =  2,
    TAPPED        =  3,
    TAPPED_BY_ME  =  4,
};

struct Unit : public Entity {
    // Units store their details in a separate memory location.
    // We can get a pointer to that at offset "0x8".
    static const u32 descriptor_ptr_offset = 0x8;
    static const u32 health_offset         = 0x58;
    static const u32 name_offset           = 0xB30; 
    static const u32 position_offset       = 0x9B8;
    static const u32 dynamic_flags_offset  = 0x23C;

    using Entity::Entity;
    u32 get_descriptor_ptr();
    int get_health();
    char *get_name();
    Vec3 get_position();
    float get_facing_direction();
    bool can_be_looted();
};

struct Player : public Unit {
    static const u32 name_base_offset   = 0xC0E230;
    static const u32 next_name_offset   = 0xC;
    static const u32 player_name_offset = 0x14;

    using Unit::Unit;
    char *get_name();
};

enum State {
    NONE_STATE,
    GRIND_STATE,
    MOVE_STATE,
    COMBAT_STATE,
};

struct Local_Player : public Player {
    static const u32 get_player_guid_fun_ptr = 0x00468550;
    State state = NONE_STATE;

    using Player::Player;
    u64 get_guid();
    float distance_to(Vec3 pos);
    void click_to_move(Vec3 pos);
    void click_to_stop();
    void cast_spell(const char *spell_name);
    void set_target(u64 guid);
    u64 get_target_guid();
    Unit select_closest_enemy(std::unordered_map <u64, Unit> *units);
};

struct Entity_Manager {
    // Offsets
    static const u32 entity_type_offset  = 0x14;

    static std::unordered_map<u64, Unit> units;
    static std::unordered_map<u64, Player> players;
    static Local_Player local_player;

    static int __fastcall process_entity(void *thiss, int filter, u64 guid);
    void populate_lists();
};
