#include <cstdio>
#include <Windows.h>

#include "bot.h"
#include "utils.h"

Entity_Manager Bot::entity_manager;
Local_Player Bot::player = 0;
bool Bot::running;

Bot::Bot() {
    running = false;
}

void Bot::main_loop() {
    player.state = GRIND_STATE;
    while (running) {
        run_procedure_on_main_thread((void*)Bot::update);
        Sleep(700);
    }
}

void Bot::update() {
    entity_manager.populate_lists();
    player.base_addr = entity_manager.local_player.base_addr;
    player.update();
}
