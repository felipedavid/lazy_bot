enum TypeMask : u32 {
    TYPEMASK_OBJECT        = 0b00000001,
    TYPEMASK_ITEM          = 0b00000010,
    TYPEMASK_CONTAINER     = 0b00000100,
    TYPEMASK_UNIT          = 0b00001000,
    TYPEMASK_PLAYER        = 0b00010000,
    TYPEMASK_GAMEOBJECT    = 0b00100000,
    TYPEMASK_DYNAMICOBJECT = 0b01000000,
    TYPEMASK_CORPSE        = 0b10000000,
    TYPEMASK_ALL           = 0b11111111,
};

enum ObjectType : u32 {
    OT_NONE,
    OT_ITEM,
    OT_CONTAINER,
    OT_UNIT,
    OT_PLAYER,
    OT_GAMEOBJECT,
    OT_DYNAMICOBJECT,
    OT_CORPSE,
};

const char *obj_type_str[8] = {
    "None",
    "Item",
    "Container",
    "Unit",
    "Player",
    "GameObject",
    "DynamicObject",
    "Corpse",
};

struct WoWObject {
    u8 unk1[0x14];
    ObjectType type; 
    u8 unk2[0x780];
};

struct Item : WoWObject {
};

struct Container : Item {
};

struct DynamicObject : WoWObject {
};

struct GameObject : WoWObject {
};

struct Corpse : WoWObject {
};

struct Unit : WoWObject {
    Vec3 position;
};

struct Player : Unit {
};
