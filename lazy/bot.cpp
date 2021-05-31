#include <windows.h>
#include <stdbool.h>
#include <cstdio>

#include "object_manager.h"
#include "game_functions.h"
#include "sync_thread.h"
#include "bot.h"
#include "state.h"

bool running = false;

void start() {
    if (!running) {
        printf("\n--- Starting Bot ---\n");
        running = true;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, &instance_handle, 0, NULL);
    } else {
        printf("Bot already running.\n");
    }
}

void stop() {
    if (running) {
        printf("\n--- Stoping Bot ---\n");
        running = false;
    } else {
        printf("Bot is already stopped.\n");
    }
}

// temporary, just for debugging
void update() {
    //if (player_logged_in()) {
    //    static uint64_t prev_target_guid = 0;
    //    n_units = 0;
    //    game_enumerate_visible_objects(objects_callback, 0);
    //    
    //    if (closest_unit.guid != prev_target_guid) {
    //        printf("\nNew Target:\n");
    //        print_object_info(closest_unit);
    //        prev_target_guid = closest_unit.guid;
    //    }

    //    if (closest_unit.distance_from_local_player >= 4) {
    //        click_to_move(closest_unit.position);
    //    } else {
    //        click_to_move_stop();
    //        set_target(closest_unit);
    //        cast_spell_by_name("Attack");
    //    }
    //} else {
    //    running = false;
    //}

    switch (top_state()) {
        case GRIND_STATE: 
            grind_state_handler();
            puts("GRIND_STATE");
            break;
        case MOVE_TO_TARGET_STATE:
            move_to_target_state_handler();
            puts("MOVE_TO_TARGET_STATE");
            break;
        case COMBAT_STATE:
            combat_state_handler();
            puts("COMBAT_STATE");
            break;
        case NO_STATE: 
            push_state(GRIND_STATE);
            break;
    }
}

void bot() {
    while (true) {
        if (!running) {
            // TODO: Create a general function to run stuff on the main thread
            click_to_move_stop();
            break;
        }
        run_update_on_main_thread();
        Sleep(50);
    }
}
