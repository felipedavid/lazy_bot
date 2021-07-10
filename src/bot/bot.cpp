#include <windows.h>
#include <stack>

#include "../game/object_manager.h"
#include "../game/objects/local_player.h"
#include "../game/objects/unit.h"
#include "../game/functions.h"
#include "../utils/sync_thread.h"
#include "bot.h"
#include "state_type.h"

std::stack<StateType> state;
ObjectManager object_manager;
LocalPlayer &player = object_manager.local_player;
bool running = false;
int update_delay = 300;
Unit target;

void update() {
    object_manager.populate_lists();
    switch(state.top()) {
        case GrindState:  handle_grind_state();  break;
        case MoveState:   handle_move_state();   break;
        case CombatState: handle_combat_state(); break;
    }
}

void bot() {
    while (true) {
        if (!running) break;
        run_procedure_on_main_thread(&update);
        Sleep(update_delay);
    }
}

void start() {
    if (!running) {
        running = true;
        state.push(GrindState);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, NULL, 0, 0);
    } else {
        running = false;
    }
}

void stop() {
    running = false;
}

void handle_grind_state() {
    target = object_manager.get_closest_unit();
    set_target(target);
    run_lua("CastSpellByName(\"Attack\")");
    state.push(MoveState);
}

void handle_move_state() {
    Position target_pos = target.get_position();
    if (target_pos.distance_from(player.get_position()) > 4.0) {
        player.move_to(target_pos);
    } else {
        state.push(CombatState);
    }
}

void handle_combat_state() {
    if (target.get_health() <= 0) {
        state.pop();
        state.pop();
    }
}
