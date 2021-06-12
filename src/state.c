#include <stdio.h>

#include "objects.h"
#include "local_player.h"
#include "state.h"

state_stack_t state_stack;

object_t target;

void push_state(state_t state) {
    if (state_stack.top_index == state_stack.max_size) {
        printf("Stack full.\n");
    } else {
        state_stack.top_index++;
        state_stack.stack[state_stack.top_index] = state;
    }
}

void pop_state() {
    if (state_stack.top_index == -1) {
        printf("Stack empty.\n");
    } else {
        state_stack.top_index--;
    }
}

state_t get_top_state() {
    if (state_stack.top_index == -1)
        return NoState;
    return state_stack.stack[state_stack.top_index];
}

void handle_grind_state() {
    target = get_new_target();
    if (target.guid) {
        set_target(target);
        push_state(MoveToTargetState);
    }
}

void handle_move_to_target_state() {
    position_t target_position = get_object_position(target);
    if (get_distance_from_object(target) >= 4) {
        click_to_move(target_position, MoveClick);
    } else {
        click_to_move(get_object_position(*local_player), NoneClick);
        call_lua("CastSpellByName(\"Attack\")"); // temporary
        push_state(CombatState);
    }
}

void handle_combat_state() {
    if (get_distance_from_object(target) >= 4) {
        pop_state();
    } else if (get_object_health(target) > 0) {
    } else {
        pop_state();
        pop_state();
    }
}

void handle_loot_state() {
    printf("LootState");
    pop_state();
}
