#include <cstdio>

#include "entity_manager.h"

void bot_loop() {
    Entity_Manager entity_manager;
    entity_manager.populate_lists();
    for (auto& entity : entity_manager.entities) {
        printf("Base addr: 0x%x\nGuid: %llu\n", entity.second.base_addr, entity.first);
    }
}
