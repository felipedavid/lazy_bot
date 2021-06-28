#include <stdint.h>

#include "objects/object.hpp"

typedef struct {
    float x;
    float y;
    float z;
} Position;

void enumerate_visible_objects(void *callback);
uint32_t get_object_ptr(uint64_t guid);
void set_target(WowObject object);
void call_lua(char *code);
void click_to_move(Position position, int click_type);
uint64_t get_player_guid();
