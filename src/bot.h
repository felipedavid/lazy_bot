#include "entity_manager.h"

struct Bot {
    int running = false;
    Entity_Manager entity_manager;

    void toggle_running_state();
    void print_visible_objects();
};
