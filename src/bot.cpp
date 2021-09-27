#include <windows.h>

#include "bot.h"

void Bot::toggle_running_state() {
    running = !running;
}

void Bot::print_entity_list() {
    system("cls");
    printf("Player list:");
    int i = 1;
    for (auto& player : entity_manager.units) {
        printf("Player %d\nName: %s\nGuid: %llu\nPointer: %u\nHealth: %d\n Distance: %.1f\n\n", 
                i, player.second.get_name(), player.second.get_guid(), player.second.base_addr, player.second.get_health(), 
                entity_manager.local_player.distance_to(player.second.get_position()));
        i++;
    }

    printf("Local player:");
    auto player = entity_manager.local_player;
    printf("Unit %d\nName: %s\nGuid: %llu\nPointer: %u\nHealth: %d\n\n", 
            i, player.get_name(), player.get_guid(), player.base_addr, player.get_health());
}
