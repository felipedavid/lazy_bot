#include <cstdio>

#include "bot.h"
#include "imgui\imgui.h"
#include "entity_manager.h"
#include "utils.h"

void bot_loop(Menu *menu) {
    char log[256];

    Entity_Manager entity_manager;
    entity_manager.populate_lists();

    int i = 1;
    for (auto& entity : entity_manager.units) {
        Unit &e = entity.second; 
        sprintf_s(log, "Entity %d\nBase addr: 0x%x\nType: %s\nHealth: %d\nGuid: %llu\n\n", 
            i, e.base_addr, entity_type_to_str(e.get_type()), e.get_health(), entity.first);
        menu->add_log(log);
        i++;
    }
}
