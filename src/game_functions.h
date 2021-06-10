#include <stdint.h>
#include "local_player.h"
#include "objects/objects.h"

extern object_t *local_player;

void enumerate_visible_objects(void *callback);
uint32_t get_object_ptr(uint64_t guid);
void set_target(object_t object);
void call_lua(char *code);
void click_to_move(position_t position, click_type_t click_type);
