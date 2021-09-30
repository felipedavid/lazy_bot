#include <cstdio>

#include "bot.h"
#include "imgui\imgui.h"
#include "entity_manager.h"

void bot_loop(Menu *menu) {
    char log[256];

    Entity_Manager entity_manager;
    entity_manager.populate_lists();

    for (auto& entity : entity_manager.entities) {
        sprintf_s(log, "Base addr: 0x%x\nGuid: %llu\n", entity.second.base_addr, entity.first);
        menu->add_log(log);
    }
}
