#include <stdio.h>
#include <windows.h>
#include <stdint.h>

#include "imgui\imgui.h"
#include "utils.h"
#include "objects.h"
#include "local_player.h"
#include "game_functions.h"
#include "hacks.h"
#include "sync_thread.h"
#include "bot.h"
#include "gui.h"

#define WINDOW_NAME "Kenny Bot"

void frame() {
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("#tabs", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Main")) {
            if (!running) {
                if (ImGui::Button("Start")) {
                    toggle_bot_running_state();
                }
            } else {
                if (ImGui::Button("Stop")) {
                    toggle_bot_running_state();
                }
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Debug")) {
            if (ImGui::Button("Show Console")) {
                create_console();
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
    hook_window_proc();
    fix_click_to_move();

    uint32_t config_flags = 0;
    imgui_app(frame, WINDOW_NAME, 500, 300, config_flags);
}
