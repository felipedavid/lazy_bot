#pragma once

#include "menu.h"
#include "entity_manager.h"

struct Bot {
    static Entity_Manager entity_manager;
    static Local_Player player;
    static bool running;

    Bot();
    static void __cdecl update();
    static void __cdecl main_loop();
};
