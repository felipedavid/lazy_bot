#include <stdint.h>
#include "object.h"

int32_t __fastcall objects_callback(void *thiscall_garbage, uint32_t filter, uint64_t guid);
float local_player_distance_from_position(position_t position);
void set_unit_position(object_t *object);
uint32_t get_object_descriptor_addr(object_t *object);
void sort_units_by_distance();
