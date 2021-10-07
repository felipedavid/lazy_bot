#include "windows.h"
#include "utils.h"

const char *entity_type_to_str(Entity_Type type) {
    switch(type) {
        case ET_NONE:      return "None";
        case ET_ITEM:      return "Item";
        case ET_CONTAINER: return "Container";
        case ET_UNIT:      return "Unit";
        case ET_PLAYER:    return "Player";
        case ET_GAMEOBJ:   return "GameObject";
        case ET_DYNOBJ:    return "DynamicObject";
        case ET_CORPSE:    return "Corpse";
    }
    return "Undefined";
}

void write_to_memory(char *dst, char *src, int size) {
    DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void run_procedure_on_main_thread(void* procedure) {
    HWND window_handle = FindWindow(NULL, "World of Warcraft");
    SendMessage(window_handle, WM_USER, (WPARAM)procedure, 0);
}