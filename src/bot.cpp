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
bool running = false;

void toggle_bot_running_state() {
    if (!running) {
        printf("---- STARTING BOT ----");
        running = true;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, &instance_handle, 0, 0);
    } else {
        printf("---- STOPPING BOT ----");
        running = false;
    }
}

// It runs on the main thread before the hooked window procedure so it should 
// not contain infinite loops
void update() {
    // TODO: debug 'get_closest_enemy()' and see why it returns invalid objects
    // sometimes
    object_t closest_enemy = get_closest_enemy();
    system("cls");
    print_object_info(closest_enemy);
    //set_target(closest_enemy);

    //float distance_from_enemy = get_distance_from_object(closest_enemy);
    //position_t enemy_position = get_object_position(closest_enemy);
    //if (distance_from_enemy > 5) {
    //    click_to_move(enemy_position, Move);
    //} else {
    //    click_to_move(enemy_position, Stop);
    //    call_lua("CastSpellByName('Attack')");
    //}
}

void bot() {
    while (running) {
        update_view();
        run_update_on_main_thread();
        Sleep(100);
    }
}
