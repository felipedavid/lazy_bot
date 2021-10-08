#include <cstdio>
#include <Windows.h>

#include "bot.h"
#include "hacks.h"
#include "event_handler.h"
#include "utils.h"

Entity_Manager Bot::entity_manager;
Local_Player Bot::player = 0;
bool Bot::running;

Bot::Bot() {
    unlock_lua();
    hook_event_signal();
    running = false;
}

void Bot::main_loop() {
    player.state = GRIND_STATE;
    while (running) {
        run_procedure_on_main_thread((void*)Bot::update);
        Sleep(700);
    }
}

void Bot::update() {
    entity_manager.populate_lists();
    player.base_addr = entity_manager.local_player.base_addr;
    player.update();
}

void Bot::draw_menu() {
	if (show_menu) {
		ImGui::Begin("Lazy Bot");

		{
			if (!Bot::running) {
                if (ImGui::Button("Start")) {
                    Bot::running = true;
                    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Bot::main_loop, NULL, 0, NULL);
                }
			} else if (ImGui::Button("Stop")) {
                Bot::running = false;
            }
			ImGui::SameLine();
			if (ImGui::Button("Clear logs")) {
				log_buffer.clear();
			}
		}

		ImGui::Separator();

		{
			ImGui::BeginChild("scrolling");
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
			ImGui::TextUnformatted(log_buffer.begin());
			if (scroll_to_bottom) ImGui::SetScrollHere(1.0f);
			scroll_to_bottom = false;
			ImGui::PopStyleVar();
			ImGui::EndChild();
		}

		ImGui::End();
	}
}

void Bot::add_log(const char *log_message) {
    log_buffer.append(log_message);
    log_buffer.append("\n");
    scroll_to_bottom = true;
}
