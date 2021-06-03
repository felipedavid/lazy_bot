#include <stdint.h>
#include "local_player.h"

extern object_t *local_player;

void click_to_move(position_t position);
void enumerate_visible_objects(void *callback);
uint32_t get_object_ptr(uint64_t guid);
