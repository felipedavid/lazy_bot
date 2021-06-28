#include <windows.h>
#include <cstdlib>
#include <cstdio>

#include "imgui.h"
#include "../game/object_manager.hpp"

#define WINDOW_TITLE "Lazy Bot"

FILE *dummy_file;

void window() {
    static bool console_open = false;
    static bool bot_running = false;
    
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("#tabs", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Main")) {
            if (!bot_running) {
                if (ImGui::Button("Start")) {
                    printf("Starting...\n");
                    bot_running = true;
                }
            } else {
                if (ImGui::Button("Stop")) {
                    printf("Stopping...\n");
                    bot_running = false;
                }
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Debug")) {
            if (!console_open) {
                if (ImGui::Button("Open console")) {
                    AllocConsole();
                    freopen_s(&dummy_file, "CONOUT$", "w", stdout);
                    console_open = true;
                }
            } else {
                if (ImGui::Button("Close console")) {
                    fclose(dummy_file);
                    FreeConsole();
                    console_open = false;
                }
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Lua")) {
            static char lua_input[256];
            ImGui::InputText("Lua command", lua_input, 256);
            if (ImGui::Button("Run")) {
            //    call_lua(lua_input);
            }
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();

    // Reformat the imgui's window frame to match Windows's window frame.
    RECT rect;
    ::GetClientRect(FindWindow(NULL, WINDOW_TITLE), &rect);
    ImGui::SetWindowSize(ImVec2((float)(rect.right - rect.left), 
                                (float)(rect.bottom - rect.top)+20));
    ImGui::SetWindowPos(ImVec2(0, -20));

    Sleep(20);
}

int start_gui(HMODULE module_handle) {
    int imguiConfigFlags = 0;

    // will return only when the window is closed
    imgui_app(window, WINDOW_TITLE, 500, 250, imguiConfigFlags);    
    FreeLibraryAndExitThread(module_handle, 0);
    return 0;
}
