#include <stdio.h>

#include "state.h"

state_stack_t state_stack;

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
