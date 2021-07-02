#ifndef PLAYER
#define PLAYER
#include "unit.h"

struct Player : Unit {
    char *get_name() override;
};
#endif
