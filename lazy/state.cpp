#include <stdio.h>
#include "state.h"

state_stack_t bot_state = {0};

void grind_state_handler() {
    printf("Grinding...\n");
}

void move_to_target_state_handler() {
    printf("Moving to target.\n");
}

void combat_state_handler() {
    printf("In combat.\n");
}

void push_state(state_t state) {
    if (bot_state.n_states <= 10) {
        bot_state.stack[bot_state.n_states++] = state;
    } else {
        printf("State stack is full.\n");
    }
}

void pop_state() {
    if (bot_state.n_states) {
        bot_state.n_states--;
    } else {
        printf("Bot state stack is already empty.\n");
    }
}

state_t top_state() {
    if (bot_state.n_states == 0) {
        return NO_STATE;
    }
    return bot_state.stack[bot_state.n_states - 1];
}
