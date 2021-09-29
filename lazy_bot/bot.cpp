#include <windows.h>

#include "bot.h"

void Bot::toggle_running_state() {
    running = !running;
}

void Bot::print_entity_list() {
    entity_manager.populate_lists();
    system("cls");
    printf("Player list:");
    int i = 1;
    for (auto& player : entity_manager.units) {
        printf("Player %d\nName: %s\nGuid: %llu\nPointer: %u\nHealth: %d\n Distance: %.1f\n\n",
            i, player.second.get_name(), player.second.get_guid(), player.second.base_addr, player.second.get_health(),
            entity_manager.local_player.distance_to(player.second.get_position()));
        i++;
    }

    printf("Local player:");
    auto player = entity_manager.local_player;
    printf("Unit %d\nName: %s\nGuid: %llu\nPointer: %u\nHealth: %d\n\n",
        i, player.get_name(), player.get_guid(), player.base_addr, player.get_health());
}

void Bot::Draw(const char* title) {
    ImGui::Begin(title);
    if (!running) {
        if (ImGui::Button("Start")) {
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot_thread, this, 0, NULL);
        }
    }
    else {
        if (ImGui::Button("Stop")) {
            running = false;
        }
    }

    ImGui::Separator();
    ImGui::TextUnformatted(Buf.begin());
    if (ScrollToBottom)
        ImGui::SetScrollHere(1.0f);
    ScrollToBottom = false;
    ImGui::End();
}


int bot_thread(Bot *n) {
    //FILE* dummy_file;
    //AllocConsole();
    //freopen_s(&dummy_file, "CONOUT$", "w", stdout);

    /*Bot bot;
    char* to_print = (char*)malloc(200 * sizeof(char));

    for (;;) {
        bot.entity_manager.populate_lists();
        for (auto& unit : bot.entity_manager.units) {
            sprintf(to_print, "Unit %d\nName: %s\nGuid: %llu\nPointer: %u\nHealth: %d\n Distance: %.1f\n\n",
                unit.second.get_name(), unit.second.get_guid(), unit.second.base_addr, unit.second.get_health(),
                bot.entity_manager.local_player.distance_to(unit.second.get_position()));
             
        }
        Sleep(5000);
    }*/
    return 0;
}