#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

#include "utils.h"
#include "objects.h"
#include "local_player.h"
#include "game_functions.h"
#include "bot.h"
#include "sync_thread.h"

extern HINSTANCE instance_handle;
bool bot_running = false;

void toggle_bot_running_state() {
    if (!bot_running) {
        //printf("---- STARTING BOT ----");
        bot_running = true;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, &instance_handle, 0, 0);
    } else {
        //printf("---- STOPPING BOT ----");
        bot_running = false;
    }
}

// It runs on the main thread before the hooked window procedure so it should 
// not contain infinite loops
void update() {
    update_view();
    object_t closest_enemy = get_closest_enemy();
    position_t closest_enemy_pos = get_object_position(closest_enemy);
    if (get_distance_from_object(closest_enemy) >= 4) {
        click_to_move(closest_enemy_pos, MoveClick);
    } else {
        click_to_move(get_object_position(*local_player), NoneClick);
        set_target(closest_enemy);
        call_lua("CastSpellByName(\"Attack\")");
    }
}

void bot() {
    while (true) {
        if (!bot_running) {
            click_to_move(get_object_position(*local_player), NoneClick);
            break;
        }
        run_update_on_main_thread();
        Sleep(100);
    }
}
