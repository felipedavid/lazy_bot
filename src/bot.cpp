#include <windows.h>
#include "bot.h"

#include "gui\hook.h"

void Bot::toggle_running_state() {
    running = !running;
}

void Bot::print_visible_objects() {
    entity_manager.populate_lists();

    system("cls");
    printf("Player list:");
    int i = 1;
    for (auto unit : entity_manager.units) {
        printf("Unit %d\nName: %s\nGuid: %llu\nPointer: %u\nHealth: %d\n Distance: %.1f\n\n", 
                i, unit.get_name(), unit.get_guid(), unit.base_addr, unit.get_health(), 
                entity_manager.local_player.distance_to(unit.get_position()));
        i++;
    }
    printf("Local player:");
    auto player = entity_manager.local_player;
    printf("Unit %d\nName: %s\nGuid: %llu\nPointer: %u\nHealth: %d\n\n", 
            i, player.get_name(), player.get_guid(), player.base_addr, player.get_health());
}
