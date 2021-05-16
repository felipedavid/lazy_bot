#include <stdint.h>
#include "object.h"

int32_t __fastcall callback(void *thiscall_garbage, uint32_t filter, uint64_t guid);
void go_to(object_t local_player, position_t position, click_type_t click_type);
float local_player_distance_from_position(position_t position);
void set_unit_position(object_t *object);
uint32_t get_object_descriptor_addr(object_t *object);
