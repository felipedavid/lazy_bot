#pragma once
#include "imgui\imgui.h"

struct Menu {
    const char *title = "Lazy Bot";
    bool show = false;  
    ImGuiTextBuffer log_buffer;
    bool scroll_to_bottom = false;

    void draw();
    void add_log(const char *log_message);
};
