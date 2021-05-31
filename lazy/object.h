#include <stdint.h>
#ifndef OBJECTS
#define OBJECTS

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

typedef struct {
    float x;
    float y;
    float z;
} position_t;

typedef struct {
    uint64_t guid;
    uint32_t pointer;
    uint32_t health;
    char *name_ptr;
    position_t position;
    object_type_t type;
    float distance_from_local_player;
    uint64_t target_guid;
} object_t;

typedef enum {
    MoveClick = 0x4,
    NoneClick = 0xD,
} click_type_t;

#endif
