#include <stdint.h>

typedef enum {
    None,
    Item,
    Container,
    Unit,
    Player,
    GameObject,
    DynamicObject,
    Corpse,
} object_type_t;

typedef struct {
    uint64_t guid;
    object_type_t type;
} object_t;
