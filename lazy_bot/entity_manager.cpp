#include <cstdio>

#include "utils.h"

#include "entity_manager.h"

void Entity_Manager::populate_lists() {
    entities.erase(entities.begin(), entities.end());

    u32 current = read<u32>(read<u32>(read<u32>(0x00C79CE0) + 0x2ED0) + 0xAC);
    u32 next = current;

    while (current != 0 && (current & 1) == 0) {
        auto guid = read<u64>(current + 0xC0);
        entities.insert({guid, Entity{current, type}});

        next = read<u32>(current + 0x3c);  
        if (current == next) break;
        current = next;  
    }
}
