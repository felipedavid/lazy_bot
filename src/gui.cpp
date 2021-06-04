#include <stdio.h>
#include <windows.h>
#include <stdint.h>

#include "imgui\imgui.h"
#include "utils.h"
#include "objects.h"
#include "local_player.h"
#include "game_functions.h"
#include "hacks.h"

#define WINDOW_NAME "Kenny Bot"

void frame() {
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("#tabs", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Main")) {
            if (ImGui::Button("Start")) {
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Debug")) {
            if (ImGui::Button("Show Console")) {
                create_console();
            }
            ImGui::SameLine();
            if (ImGui::Button("Test")) {
                update_view();
                object_t closest_enemy = get_closest_enemy();
                set_target(closest_enemy);
                go_to(get_object_position(closest_enemy));
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Lua")) {
            static char lua_input[256];
            ImGui::InputText("Lua command", lua_input, 256);
            if (ImGui::Button("Run")) {
                call_lua(lua_input);
            }
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();

    // Reformat the imgui's window frame to match Windows's window frame.
    RECT rect;
    ::GetClientRect(FindWindow(NULL, WINDOW_NAME), &rect);
    ImGui::SetWindowSize(ImVec2((float)(rect.right - rect.left), 
                                (float)(rect.bottom - rect.top)+20));
    ImGui::SetWindowPos(ImVec2(0, -20));

    Sleep(20);
}

void gui() {
    unlock_lua();  // place this in other place
    uint32_t config_flags = 0;
    imgui_app(frame, WINDOW_NAME, 500, 300, config_flags);
}
