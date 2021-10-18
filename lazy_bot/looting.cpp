
#include "looting.h"
#include "game.h"
#include "bot.h"
#include "utils.h"

extern Bot bot;

void Loot_Frame::init() {
    for (u32 slot = 0; slot < 15; slot++) {
        u32 item_id = read<u32>(loot_frame_base_addr + slot * 0x1c);
        if (item_id == 0) break;
        char *item_name = (char*) read<u32>(Game::get_item_cache_entry_wrapper(item_id))+0x8;
        bot.log(item_name);
        items.push_back(Loot_Item{item_id, slot});
    }
}
