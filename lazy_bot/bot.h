#pragma once

#include "entity_manager.h"
#include "imgui\imgui.h"

struct Bot {
    static Entity_Manager entity_manager;
    static Local_Player player;
    static bool running;

    // Gui stuff
    bool show_menu = false;
    ImGuiTextBuffer log_buffer;
    bool scroll_to_bottom = false;

    Bot();
    void draw_menu();
    void add_log(const char *log_message);
    static void __cdecl update();
    static void __cdecl main_loop();
};
