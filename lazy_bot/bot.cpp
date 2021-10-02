#include <cstdio>

#include "bot.h"
#include "imgui\imgui.h"
#include "entity_manager.h"
#include "utils.h"

void test(Menu *menu) {
    if (!Game::get_player_guid()) {
        menu->add_log("Please, log in.\n");
        return;
    }
    char log[256];

    Entity_Manager entity_manager;
    entity_manager.populate_lists();
    Unit c = entity_manager.units.begin()->second;

    Vec3 pos = c.get_position();
    sprintf_s(log, "Base addr: 0x%x\nType: %s\nHealth: %d\nGuid: %llu\nName: %s\nPosition: X: %.2f, Y: %.2f, Z: %.2f\n\n", 
        c.base_addr, entity_type_to_str(c.get_type()), c.get_health(), c.get_guid(), c.get_name(), pos.x, pos.y, pos.z);
    menu->add_log(log);

    entity_manager.local_player.click_to_move(c.get_position());

}
