#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER
#include <cstdint>
#include <vector>

#include "objects/object.h"
#include "objects/unit.h"
#include "objects/local_player.h"

struct ObjectManager {
    std::vector<Unit> units;
    LocalPlayer local_player{};

    void update();
    void populate_lists();
    Unit get_closest_unit();
    void log_info();
};
#endif
