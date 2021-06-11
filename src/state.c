#include <stdio.h>

#include "objects.h"
#include "local_player.h"
#include "state.h"

state_stack_t state_stack;

object_t enemy;

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
    enemy = get_closest_enemy_named("Mindless Zombie");
    if (enemy.guid) {
        set_target(enemy);
        push_state(MoveToTargetState);
    }
    //printf("GrindState\n");
}

void handle_move_to_target_state() {
    position_t enemy_position = get_object_position(enemy);
    if (get_distance_from_object(enemy) >= 4) {
        click_to_move(enemy_position, MoveClick);
    } else {
        click_to_move(get_object_position(*local_player), NoneClick);
        call_lua("CastSpellByName(\"Attack\")"); // temporary
        push_state(CombatState);
    }
    //printf("MoveToTargetState\n");
}

void handle_combat_state() {
    if (get_distance_from_object(enemy) >= 4) {
        pop_state();
    } else if (get_object_health(enemy) > 0) {
    } else {
        pop_state();
        pop_state();
    }
    //printf("CombatState\n");
}

void handle_loot_state() {
    printf("LootState");
    pop_state();
}
