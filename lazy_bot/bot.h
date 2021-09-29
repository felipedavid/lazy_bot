#pragma once
#include "entity_manager.h"
#include "imgui/imgui.h"




struct Bot {
    int running = false;
    Entity_Manager entity_manager;

    void toggle_running_state();
    void print_entity_list(); 
	
	ImGuiTextBuffer Buf;
	bool ScrollToBottom;

	void Clear() { Buf.clear(); }

	void AddLog(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		Buf.append(fmt, args);
		va_end(args);
		ScrollToBottom = true;
	}

	void Draw(const char* title);
};

int bot_thread(Bot* n);