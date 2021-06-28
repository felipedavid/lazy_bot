#include <stdint.h>

#include "objects/object.hpp"

typedef struct {
    float x;
    float y;
    float z;
} Position;

typedef int (__fastcall *_enu_callback)(int, uint32_t, uint32_t);

void enumerate_visible_objects(void *callback);
uint32_t get_object_ptr(uint64_t guid);
uint64_t get_player_guid();
