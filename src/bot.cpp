#include <windows.h>

#include "game/object_manager.h"
#include "game/objects/local_player.h"
#include "bot.h"

bool running = false;
int update_delay = 100;

void update() {
    ObjectManager object_manager;
    LocalPlayer &player = object_manager.local_player;
    while (running) {
        object_manager.update();
        player.move_to(object_manager.get_closest_unit().get_position());
        Sleep(update_delay);
    }
}

void start() {
    if (!running) {
        running = true;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)update, NULL, 0, 0);
    } else {
        running = false;
    }
}

void stop() {
    running = false;
}
