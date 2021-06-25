struct ObjectManager {
private:
    const uint32_t OBJECT_TYPE_OFFSET = 0x14;
public:
    ObjectManager() {
    }

    void enumerate_visible_objects();
    void objects_callback(uint64_t 
};
