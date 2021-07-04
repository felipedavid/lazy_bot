#include <cstdint>

#include "local_player.h"
#include "../../memory_manager.h"
#include "../functions.h"
#include "../enums/click_type.h"

LocalPlayer::LocalPlayer() {
    base_addr = get_object_ptr(get_player_guid());
}

uint64_t LocalPlayer::get_guid() {
    return get_player_guid();
}

char *LocalPlayer::get_name() {
    static const uint32_t name_base_offset = 0xC0E230;
    static const uint32_t next_name_offset = 0xC;
    static const uint32_t player_name_offset = 0x14;

    uint64_t player_guid = get_guid();
    uint32_t name_ptr = read_uint(name_base_offset);
    while (true) {
        uint64_t next_guid = read_uint64(name_ptr + next_name_offset);

        if (next_guid != player_guid) name_ptr = read_uint(name_ptr);
        else break;
    }
    return (char *) (name_ptr + player_name_offset);
}

void LocalPlayer::move_to(Position pos) {
    click_to_move(base_addr, Move, pos);
}
