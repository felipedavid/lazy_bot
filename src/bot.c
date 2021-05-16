#include <windows.h>
#include <stdbool.h>

#include "object_manager.h"

extern object_t local_player;
extern object_t nearest_monster;

bool running = false;

void start() {
    if (!running) {
        printf("Starting Bot...\n");
        running = true;
    } else {
        printf("Bot already running.\n");
    }
}

void stop() {
    if (running) {
        printf("Stoping Bot...\n");
        running = false;
    } else {
        printf("Bot is already stopped.\n");
    }
}

void bot() {
    while (true) {
        if (running) {
            invoke_update();
        }
        Sleep(500);
    }
}
