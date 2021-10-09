#include <vector>
#include "type.h"
#pragma once

struct Loot_Item {
    u32 item_id, slot;
};

struct Loot_Frame {
    static const u32 loot_frame_base_addr = 0x00B7196C;
    std::vector<Loot_Item> items;
    void init(); 
};
