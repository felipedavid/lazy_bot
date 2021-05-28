#include <windows.h>
#include <stdbool.h>

#include "object_manager.h"
#include "game_functions.h"
#include "sync_thread.h"
#include "bot.h"

extern HINSTANCE instance_handle; // <- keep an eye on this buddy :)
extern object_t local_player;
extern object_t closest_unit;
extern int n_units;
//extern object_t units[100];

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
        go_to(closest_unit.position, NoneClick);
    } else {
        printf("Bot is already stopped.\n");
    }
}

// temporary, just for debugging
void update() {
    if (game_get_player_guid()) {
        static uint64_t prev_target_guid = 0;
        n_units = 0;
        game_enumerate_visible_objects(objects_callback, 0);
        
        if (closest_unit.guid != prev_target_guid) {
            printf("\nNew Target:\n");
            print_object_info(closest_unit);
            prev_target_guid = closest_unit.guid;
        }

        if (closest_unit.distance_from_local_player >= 4) {
            go_to(closest_unit.position, MoveClick);
        } else {
            go_to(closest_unit.position, NoneClick);
            game_set_target(closest_unit.guid);
            run_lua_on_main_thread("CastSpellByName('Attack')");
        }
    }
}

void bot() {
    while (running) {
        run_update_on_main_thread();
        Sleep(500);
    }
}
