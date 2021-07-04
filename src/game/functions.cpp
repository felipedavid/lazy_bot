#include <cstdint>

#include "enums/click_type.h"
#include "../position.h"

uint64_t get_player_guid() {
    static const uint32_t get_player_guid_fun_ptr = 0x00468550;
    return ((uint64_t (__stdcall*)())(get_player_guid_fun_ptr))();
}

uint32_t get_object_ptr(uint64_t guid) {
    static const uint32_t get_object_ptr_fun_ptr = 0x00464870;
    return ((uint32_t (__stdcall*)(uint64_t))(get_object_ptr_fun_ptr))(guid);
}

void click_to_move(uint32_t player_base, ClickType click_type, Position pos) {
    static const uint32_t click_to_move_fun_ptr = 0x00611130;
    typedef void (__fastcall* _click_to_move)(uint32_t thiss, 
                                              uint32_t player_ptr, 
                                              ClickType click_type,
                                              uint64_t *interact_guid, 
                                              Position *position, 
                                              float precision);
    _click_to_move fun = (_click_to_move) click_to_move_fun_ptr;
    uint64_t interact_guid;
    fun(player_base, player_base, click_type, &interact_guid, &pos, 2);
}
