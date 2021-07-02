#include <cstdint>

#include "player.h"
#include "../../memory_manager.h"

char *Player::get_name() {
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
