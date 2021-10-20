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
State Bot::state;

Bot::Bot() {
    unlock_lua();
    hook_event_signal();
    running = false;
}

void Bot::main_loop() {
    state = GRIND_STATE;
    while (running) {
        run_procedure_on_main_thread((void*)Bot::update);
        Sleep(300);
    }
}

// This mess is temporary. Just for testing.
void Bot::update() {
    static Vec3 prev_pos;
    entity_manager.populate_lists();
    player.base_addr = entity_manager.local_player.base_addr;
    player.refresh_spells();

    static Unit enemy = player.select_closest_enemy(&Entity_Manager::units);
    static u64 prev_enemy = enemy.get_guid();
    if (enemy.get_guid() != prev_enemy) {
        prev_enemy = enemy.get_guid();
        prev_pos = player.get_position();
    }
    switch (state) {
        case GRIND_STATE: {
            log("Looking for enemy...");
            enemy = player.select_closest_enemy(&Entity_Manager::units);
            player.face_entity(enemy.get_guid());
            if (enemy.base_addr != 0) {
                state = MOVE_STATE;
            }
        } break;
        case MOVE_STATE: {
            if (player.distance_to(enemy.get_position()) > 5.0) {
                log("Moving to enemy...");
                player.click_to_move(enemy.get_position());
            } else {
                if (player.get_position().x == prev_pos.x && player.get_position().y == prev_pos.y) 
                    player.click_to_move(enemy.get_position());
                else {
                    player.click_to_stop();
                    state = COMBAT_STATE;
                }
            }
        } break;
        case COMBAT_STATE: {
            player.try_use_ability("War Stomp", 0);
            player.try_use_ability("Heroic Strike", 30);
            player.try_use_ability("Attack", 0);

            if (enemy.get_health() == 0) {
                if (enemy.can_be_looted()) {
                    if (player.distance_to(enemy.get_position()) > 5) {
                        player.click_to_move(enemy.get_position());
                    } else {
                        log("Looting...");
                        Game::right_click_unit(enemy.base_addr, enemy.base_addr, 1);
                    }
                } else {
                    state = GRIND_STATE;
                }
            }
            log("In combat...");
            if (enemy.get_health() > 0 && player.distance_to(enemy.get_position()) < 5) {
                state = MOVE_STATE;
            }
        } break;
    }
}

void Bot::test() {
    entity_manager.populate_lists();
    player.base_addr = entity_manager.local_player.base_addr;
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
            ImGui::SameLine();
            if (ImGui::Button("Test")) {
                test();
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

void Bot::log(const char *log_message) {
    log_buffer.append(log_message);
    log_buffer.append("\n");
    scroll_to_bottom = true;
}
