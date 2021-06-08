#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

#include "utils.h"
#include "objects.h"
#include "local_player.h"
#include "game_functions.h"
#include "bot.h"
#include "sync_thread.h"
#include "state.h"

extern HINSTANCE instance_handle;
extern state_stack_t state_stack;

bool bot_running = false;
uint32_t update_delay = 100;

void toggle_bot_running_state() {
    if (!bot_running) {
        printf("---- STARTING BOT ----");
        bot_running = true;
        state_stack.top_index = -1;
        state_stack.max_size = 20;
        push_state(GrindState);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, &instance_handle, 0, 0);
    } else {
        printf("---- STOPPING BOT ----");
        bot_running = false;
        state_stack.top_index = -1;
    }
}

// It runs on the main thread before the hooked window procedure so it should 
// not contain infinite loops
void update() {
    update_view(); // TODO: think about where this goes
    static object_t enemy;
    static position_t enemy_position;

    switch (get_top_state()) {
        case GrindState: {
            enemy = get_closest_enemy_named("Plainstrider");
            if (enemy.guid) {
                set_target(enemy);
                push_state(MoveToTargetState);
            }
            //printf("GrindState\n");
        } break;
        case MoveToTargetState: {
            enemy_position = get_object_position(enemy);
            if (get_distance_from_object(enemy) >= 4) {
                click_to_move(enemy_position, MoveClick);
            } else {
                click_to_move(get_object_position(*local_player), NoneClick);
                push_state(CombatState);
            }
            //printf("MoveToTargetState\n");
        } break;
        case CombatState: {
            if (get_distance_from_object(enemy) >= 4) {
                pop_state();
            } else if (get_object_health(enemy) > 0) {
                call_lua("CastSpellByName(\"Attack\")");
            } else {
                pop_state();
                pop_state();
            }
            //printf("CombatState\n");
        } break;
    }
}

void bot() {
    while (true) {
        if (!bot_running) {
            click_to_move(get_object_position(*local_player), NoneClick);
            break;
        }
        run_procedure_on_main_thread(&update);
        Sleep(update_delay);
    }
}
