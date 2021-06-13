#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

#include "utils.h"
#include "game_functions.h"
#include "bot.h"
#include "sync_thread.h"
#include "state.h"

extern HINSTANCE instance_handle;
extern state_stack_t state_stack;

bool bot_running = false;
uint32_t update_delay = 100;

void toggle_bot_running_state() {
    if (!bot_running && (get_player_guid() > 0)) {
        printf("---- STARTING BOT ----\n");
        bot_running = true;
        state_stack.top_index = -1;
        state_stack.max_size = 20;
        push_state(GrindState);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, &instance_handle, 0, 0);
    } else {
        printf("---- STOPPING BOT ----\n");
        bot_running = false;
        state_stack.top_index = -1;
    }
}

// It runs on the main thread before the hooked window procedure so it should 
// not contain infinite loops
void update() {
    populate_lists();
    switch (get_top_state()) {
        case GrindState:        handle_grind_state();          break;
        case MoveToTargetState: handle_move_to_target_state(); break;
        case CombatState:       handle_combat_state();         break;
        case LootState:         handle_loot_state();           break;
    }
}

void bot() {
    while (true) {
        if (!bot_running) {
            click_to_move(local_player->position, NoneClick);
            break;
        }
        run_procedure_on_main_thread(&update);
        Sleep(update_delay);
    }
}
