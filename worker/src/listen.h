#pragma once
#include "common.h"

typedef enum {
    evStart = 0,
    evListEntities = 1,
} Event_Type;

void listen_to_master();