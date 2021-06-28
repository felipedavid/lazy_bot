#include <stdint.h>
#include <vector>

#include "objects/object.hpp"

class ObjectManager {
    std::vector<WowObject> object_list;

    int enumerate_objects_callback(int filter, uint64_t guid);
public:
    void populate_list();
    void log_objects();
};
