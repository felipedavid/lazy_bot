#include <windows.h>
#include "menu.h"
#include "bot.h"
#include "hacks.h"
#include "game.h"

void Menu::draw() {
	if (show) {
		ImGui::Begin(title);

		{
			if (!Bot::running && ImGui::Button("Start")) {
                Bot::running = true;
				CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Bot::update, NULL, 0, NULL);
			} else if (ImGui::Button("Stop")) {
                Bot::running = false;
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

void Menu::add_log(const char *log_message) {
    log_buffer.append(log_message);
    scroll_to_bottom = true;
}
