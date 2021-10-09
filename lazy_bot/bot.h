#pragma once

#include "entity_manager.h"
#include "imgui\imgui.h"

struct Bot {
    static Entity_Manager entity_manager;
    static Local_Player player;
    static bool running;

    // Gui stuff
    bool show_menu = false;
    static ImGuiTextBuffer log_buffer;
    static bool scroll_to_bottom;

    Bot();
    void draw_menu();
    static void add_log(const char *log_message);
    static void __cdecl update();
    static void __cdecl main_loop();
};
