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

enum Creature_Type {
    UT_BEAST         = 1,
    UT_DRAGONKIN     = 2,
    UT_DEMON         = 3,
    UT_ELEMENTAL     = 4,
    UT_GIANT         = 5,
    UT_UNDEAD        = 6,
    UT_HUMANOID      = 7,
    UT_CRITTER       = 8,
    UT_MECHANICAL    = 9,
    UT_NOT_SPECIFIED = 10,
    UT_TOTEM         = 11,
};

enum Creature_Reaction {
    CR_HATED,
    CR_HOSTILE,
    CR_UNFRIENDLY,
    CR_NEUTRAL,
    CR_FRIENDLY,
    CR_HONORED,
    CR_REVERED,
    CR_EXALED,
};

struct Unit : public Entity {
    // Units store their details in a separate memory location.
    // We can get a pointer to that at offset "0x8".
    static const u32 descriptor_ptr_offset = 0x8;
    static const u32 health_offset         = 0x58;
    static const u32 max_health_offset     = 0x70;
    static const u32 name_offset           = 0xB30; 
    static const u32 position_offset       = 0x9B8;
    static const u32 level_offset          = 0x88;
    static const u32 rage_offset           = 0x60;
    static const u32 mana_offset           = 0x5C;
    static const u32 dynamic_flags_offset  = 0x23C;
    static const u32 buffs_base_offset     = 0xBC; 
    static const u32 debuffs_base_offset   = 0x13C; 

    using Entity::Entity;
    u32 get_descriptor_ptr();
    int get_health();
    int get_max_health();
    int get_health_percentage();
    int get_rage();
    char *get_name();
    Vec3 get_position();
    float get_facing_direction();
    bool can_be_looted();
    int get_level();
    int get_mana();
    Creature_Type get_type();
    Creature_Reaction get_reaction(u32 player_ptr);
    std::vector<u32> get_buff_ids();
    std::vector<u32> get_debuff_ids();
    bool has_buff(const char *buff_name);
};

struct Player : public Unit {
    static const u32 name_base_offset   = 0xC0E230;
    static const u32 next_name_offset   = 0xC;
    static const u32 player_name_offset = 0x14;

    using Unit::Unit;
    char *get_name();
};

struct Local_Player : public Player {
    static const u32 get_player_guid_fun_ptr = 0x468550;
    static const u32 player_spells_base_addr = 0xB700F0;;

    std::unordered_map<const char *, u32> spells;

    using Player::Player;
    u64 get_guid();
    float distance_to(Vec3 pos);
    void click_to_move(Vec3 pos);
    void click_to_stop();
    void cast_spell(const char *spell_name);
    void set_target(u64 guid);
    u64 get_target_guid();
    Unit select_closest_enemy(std::unordered_map <u64, Unit> *units);
    void refresh_spells();
    bool is_spell_ready(const char *spell_name, int spell_rank);
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
