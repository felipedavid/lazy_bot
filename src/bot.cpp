#include "bot.h"

void Bot::toggle_running_state() {
    running = !running;
}

void Bot::print_visible_objects() {
    entity_manager.populate_lists();

    int i = 1;
    for (auto entity : entity_manager.entities) {
        printf("Entity %d\nGuid: %llu\nPointer: %u\nType: %d\n\n", i, entity.guid, entity.pointer, entity.type);
        i++;
    }
}
