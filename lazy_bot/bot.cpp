#include <cstdio>

#include "bot.h"
#include "imgui\imgui.h"
#include "entity_manager.h"
#include "utils.h"

void bot_loop(Menu *menu) {
    if (!Game::get_player_guid()) {
        menu->add_log("Please, log in.\n");
        return;
    }
    char log[256];

    Entity_Manager entity_manager;
    entity_manager.populate_lists();

    int i = 1;
    for (auto& entity : entity_manager.units) {
        Unit &e = entity.second; 
        Vec3 pos = entity.second.get_position();
        sprintf_s(log, "Entity %d\nBase addr: 0x%x\nType: %s\nHealth: %d\nGuid: %llu\nName: %s\nPosition: X: %.2f, Y: %.2f, Z: %.2f\n\n", 
            i, e.base_addr, entity_type_to_str(e.get_type()), e.get_health(), entity.first, e.get_name(), pos.x, pos.y, pos.z );
        menu->add_log(log);
        i++;
    }
    for (auto& entity : entity_manager.players) {
        Player &e = entity.second; 
        sprintf_s(log, "Entity %d\nBase addr: 0x%x\nType: %s\nHealth: %d\nGuid: %llu\nName: %s\n\n",
            i, e.base_addr, entity_type_to_str(e.get_type()), e.get_health(), entity.first, e.get_name());
        menu->add_log(log);
        i++;
    }

    Local_Player *p = &entity_manager.local_player;
    Vec3 pos = p->get_position();
    sprintf_s(log, "Entity %d\nBase addr: 0x%x\nType: %s\nHealth: %d\nGuid: %llu\nName: %s\nPosition: X: %.2f, Y: %.2f, Z: %.2f\n\n",
        i, p->base_addr, entity_type_to_str(p->get_type()), p->get_health(), p->get_guid(), p->get_name(), pos.x, pos.y, pos.z);
    menu->add_log(log);

}
