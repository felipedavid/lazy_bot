#include <windows.h>
#include <cstdlib>
#include <stdio.h>

#include "imgui.h"
#include "bot.h"
#include "utils.h"

#define WINDOW_NAME "Lazy Bot"

void frame() {
    if (ImGui::Button("Start")) {
        start();
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop")) {
        stop();
    }
    ImGui::SetWindowPos(ImVec2(0, -20));

    RECT rect;
    ::GetClientRect(FindWindow(NULL, WINDOW_NAME), &rect);
    ImGui::SetWindowSize(ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top)+20));
}

int start_gui() {
    setup_client();

    int imguiConfigFlags = 0;
    //imguiConfigFlags = imguiConfigFlags | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    imgui_app(frame, WINDOW_NAME, 500, 250, imguiConfigFlags);    
    return 0;
}
