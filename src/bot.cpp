#include <windows.h>

#include "game/object_manager.h"
#include "game/objects/local_player.h"
#include "game/objects/unit.h"
#include "game/functions.h"
#include "sync_thread.h"
#include "bot.h"

ObjectManager object_manager;
LocalPlayer &player = object_manager.local_player;
bool running = false;
int update_delay = 300;

// TODO: Implement this as a state machine
void update() {
    object_manager.update();
    Unit enemy = object_manager.get_closest_unit();
    float distance = player.get_position().distance_from(enemy.get_position());
    if (distance >= 10.0) {
        run_lua("CastSpellByName(\"Auto Shot\")");
    } else if (distance > 4.0) {
        player.move_to(enemy.get_position());
    } else {
        run_lua("CastSpellByName(\"Raptor Strike\")");
    }
    set_target(enemy);
}

void bot() {
    while (true) {
        if (!running) break;
        run_procedure_on_main_thread(&update);
        Sleep(update_delay);
    }
}

void start() {
    if (!running) {
        running = true;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, NULL, 0, 0);
    } else {
        running = false;
    }
}

void stop() {
    running = false;
}
