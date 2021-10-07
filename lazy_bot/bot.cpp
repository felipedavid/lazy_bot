#include <cstdio>

#include "bot.h"

Entity_Manager Bot::entity_manager;
Local_Player Bot::player = 0;
bool Bot::running;

Bot::Bot() {
    running = false;
}

void __cdecl Bot::update() {
    if (running) {
        entity_manager.populate_lists();
        player = entity_manager.local_player;

        player.update();
    }
}
