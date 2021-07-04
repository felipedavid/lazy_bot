#include <cstdint>

#include "enums/click_type.h"
#include "../position.h"

uint64_t get_player_guid();
uint32_t get_object_ptr(uint64_t guid);
void click_to_move(uint32_t player_base, ClickType click_type, Position pos);
