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

typedef struct {
    uint64_t guid;
    uint32_t pointer;
    object_type_t type;
} object_t;

typedef struct {
    float x;
    float y;
    float z;
} position_t;

#endif
