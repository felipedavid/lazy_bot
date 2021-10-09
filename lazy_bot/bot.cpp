#include <cstdio>
#include <Windows.h>

#include "bot.h"
#include "hacks.h"
#include "event_handler.h"
#include "utils.h"

Entity_Manager Bot::entity_manager;
Local_Player Bot::player = 0;
bool Bot::running;
bool Bot::scroll_to_bottom = false;
ImGuiTextBuffer Bot::log_buffer;

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

    static Unit enemy = player.select_closest_enemy(&Entity_Manager::units);
    switch (player.state) {
        case GRIND_STATE: {
            add_log("Looking for enemy...");
            enemy = player.select_closest_enemy(&Entity_Manager::units);
            if (enemy.base_addr != 0) {
                player.state = MOVE_STATE;
            }
        } break;
        case MOVE_STATE: {
            if (player.distance_to(enemy.get_position()) > 5.0) {
                add_log("Moving to enemy...");
                player.click_to_move(enemy.get_position());
            } else {
                player.click_to_stop();
                player.cast_spell("Attack");
                player.cast_spell("Fireball");
                player.state = COMBAT_STATE;
            }
        } break;
        case COMBAT_STATE: {
            add_log("In combat...");
            if (enemy.get_health() == 0) {
                if (enemy.can_be_looted()) {
                    Game::right_click_unit(enemy.base_addr, enemy.base_addr, 1);
                    Sleep(300);
                }
                player.state = GRIND_STATE;
            }
        } break;
    }
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
