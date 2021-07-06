#include <windows.h>

#include "game/object_manager.h"
#include "game/objects/local_player.h"
#include "game/functions.h"
#include "sync_thread.h"
#include "bot.h"

ObjectManager object_manager;
LocalPlayer &player = object_manager.local_player;
bool running = false;
int update_delay = 100;

void update() {
    //object_manager.update();
    run_lua("Jump()");
    //player.move_to(object_manager.get_closest_unit().get_position());
}

void bot() {
    while (true) {
        if (!running) break;
        run_procedure_on_main_thread(update);
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
