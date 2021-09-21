#include <windows.h>
#include "bot.h"

void Bot::toggle_running_state() {
    running = !running;
}

void Bot::print_visible_objects() {
    entity_manager.populate_lists();

    system("cls");
    int i = 1;
    for (auto unit : entity_manager.units) {
        printf("Unit %d\nGuid: %llu\nPointer: %u\nHealth: %d\n\n", 
                i, unit.get_guid(), unit.base_addr, unit.get_health());
        i++;
    }
}
