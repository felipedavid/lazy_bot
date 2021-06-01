#include <windows.h>
#include <cstdlib>
#include <stdio.h>

#include "imgui\imgui.h"
#include "bot.h"
#include "utils.h"
#include "gui.h"
#include "sync_thread.h"
#include "game_functions.h"
#include "state.h"
#include "hacks.h"

#define WINDOW_NAME "Lazy Bot"

char input[256];

void frame() {
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("#tabs", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Main")) {
            if (!running) {
                if (ImGui::Button("Start")) {
                    if (player_logged_in()) {
                        start();
                    }
                }
            } else {
                if (ImGui::Button("Stop")) {
                    stop();
                }
            }
            if (running) {
                ImGui::Text("Running...");
            } else {
                ImGui::Text("Not running.");
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Fish")) {
            ImGui::Text("Not Implemented.\n");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Combat")) {
            ImGui::Text("Not Implemented.\n");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Gather")) {
            ImGui::Text("Not Implemented.\n");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Mount")) {
            ImGui::Text("Not Implemented.\n");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Vendor")) {
            ImGui::Text("Not Implemented.\n");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Hacks")) {
            if (ImGui::Button("Click to Teleport")) {
                toggle_click_to_teleport();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("LUA Test")) {
            ImGui::InputText("Lua command: ", input, 256);
            if (ImGui::Button("Run")) {
                run_lua_on_main_thread(input);
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Debug")) {
            if (ImGui::Button("Push GRIND_STATE")) {
                push_state(GRIND_STATE);
            }
            ImGui::SameLine();
            if (ImGui::Button("Push MOVE_TO_TARGET_STATE")) {
                push_state(MOVE_TO_TARGET_STATE);
            }
            ImGui::SameLine();
            if (ImGui::Button("Push COMBAT_STATE")) {
                push_state(COMBAT_STATE);
            }
            ImGui::SameLine();
            if (ImGui::Button("Pop state")) {
                pop_state();
            }
            if (ImGui::Button("Clear Log Console")) system("cls");
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();
    ImGui::SetWindowPos(ImVec2(0, -20));

    RECT rect;
    ::GetClientRect(FindWindow(NULL, WINDOW_NAME), &rect);
    ImGui::SetWindowSize(ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top)+20));

    Sleep(20);
}

int start_gui() {
    setup_client();

    int imguiConfigFlags = 0;
    //imguiConfigFlags = imguiConfigFlags | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    imgui_app(frame, WINDOW_NAME, 500, 600, imguiConfigFlags);    
    return 0;
}
