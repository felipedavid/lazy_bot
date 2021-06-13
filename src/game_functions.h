#include <stdint.h>
#include "local_player.h"
#include "objects.h"

extern object_t *local_player;

void enumerate_visible_objects(void *callback);
void set_target(object_t object);
void call_lua(char *code);
void click_to_move(position_t position, click_type_t click_type);
uint64_t get_player_guid();
uint32_t get_creature_type(object_t object);
uint32_t get_unit_reaction(object_t object);
void set_object_ptr(object_t *object);
