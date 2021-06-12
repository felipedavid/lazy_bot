#include <stdint.h>

#ifndef OBJ_TYPES
#define OBJ_TYPES 

typedef enum {
    None          = 0x0,
    Item          = 0x1,
    Container     = 0x2,
    Unit          = 0x3,
    Player        = 0x4,
    GameObject    = 0x5,
    DynamicObject = 0x6,
    Corpse        = 0x7,
} object_type_t;

typedef enum {
    MoveClick = 0x4,
    NoneClick = 0xD,
} click_type_t;

typedef enum {
    Beast = 1,
    Dragonkin = 2,
    Demon = 3,
    Elemental = 4,
    Giant = 5,
    Undead = 6,
    Humanoid = 7,
    Critter = 8,
    Mechanical = 9,
    NotSpecified = 10,
    Totem = 11,
} creature_type_t;

typedef enum {
    Hated,
    Hostile,
    Unfriendly,
    Neutral,
    Friendly,
    Honored,
    Revered,
    Exalted,
} unit_reaction_t;

typedef struct {
    float x;
    float y;
    float z;
} position_t;

typedef struct {
    uint64_t guid;
    uint32_t pointer;
    uint32_t health;
    object_type_t type;
    creature_type_t creature_type;
    unit_reaction_t unit_reaction;
} object_t;

#endif

extern object_t *local_player;

void update_view();
uint32_t __fastcall enumerate_objects_callback(void *thiss, uint32_t filter, uint64_t guid);
object_type_t get_object_type(uint32_t object_ptr);
char *get_object_name(object_t object);
uint32_t get_object_health(object_t object);
position_t get_object_position(object_t object);
void print_object_info(object_t object);
