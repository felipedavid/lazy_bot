#include <stdint.h>

class ObjectManager {
    std::vector<WowObject> object_list;
    int callback(uint32_t garbage, int filter, uint64_t guid);
public:
    void populate_lists();
    void log_objects();
}
