#include <windows.h>
#include <stdbool.h>

#include "object_manager.h"
#include "game_functions.h"
#include "sync_thread.h"
#include "bot.h"

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
    if (player_logged_in()) {
        static uint64_t prev_target_guid = 0;
        n_units = 0;
        game_enumerate_visible_objects(objects_callback, 0);
        
        if (closest_unit.guid != prev_target_guid) {
            printf("\nNew Target:\n");
            print_object_info(closest_unit);
            prev_target_guid = closest_unit.guid;
        }

        if (closest_unit.distance_from_local_player >= 4) {
            click_to_move(closest_unit.position);
        } else {
            click_to_move_stop();
            set_target(closest_unit);
            cast_spell_by_name("Attack");
        }
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
        Sleep(100);
    }
}
