
typedef enum COLOR_T {
    DEFAULT_COLOR    = 0,
    INPUT_COLOR      = 1,
    ECHO_COLOR       = 2,
    ERROR_COLOR      = 3,
    WARNING_COLOR    = 4,
    GLOBAL_COLOR     = 5,
    ADMIN_COLOR      = 6,
    HIGHLIGHT_COLOR  = 7,
    BACKGROUND_COLOR = 8,
    NUM_COLORTYPES   = 9
} COLOR_T;

typedef struct C3Vector {
    f32 x;
    f32 y;
    f32 z;
} C3Vector;

typedef enum OBJECT_TYPE_ID {
    ID_OBJECT               = 0,
    ID_ITEM                 = 1,
    ID_CONTAINER            = 2,
    ID_UNIT                 = 3,
    ID_PLAYER               = 4,
    ID_GAMEOBJECT           = 5,
    ID_DYNAMICOBJECT        = 6,
    ID_CORPSE               = 7,
    NUM_CLIENT_OBJECT_TYPES = 8,
    ID_AIGROUP              = 8,
    ID_AREATRIGGER          = 9,
    NUM_OBJECT_TYPES        = 10
} OBJECT_TYPE_ID;

const char *OBJECT_TYPE_ID_STR[NUM_OBJECT_TYPES] = {
    [ID_OBJECT]        = "ID_OBJECT",
    [ID_ITEM]          = "ID_ITEM",
    [ID_CONTAINER]     = "ID_CONTAINER",
    [ID_UNIT]          = "ID_UNIT",
    [ID_PLAYER]        = "ID_PLAYER",
    [ID_GAMEOBJECT]    = "ID_GAMEOBJECT",
    [ID_DYNAMICOBJECT] = "ID_DYNAMICOBJECT",
    [ID_CORPSE]        = "ID_CORPSE",
    [ID_AIGROUP]       = "ID_AIGROUP",
    [ID_AREATRIGGER]   = "ID_AREATRIGGER"
};

typedef struct CGObject_C {
    u8 padding1[0x14];
    OBJECT_TYPE_ID type;
    u8 padding2[0x9a0];
} CGObject_C;

typedef struct CGUnit_C {
    CGObject_C base;
    C3Vector m_currentPosition; // unknown real name
} CGUnit_C;

typedef struct CGPlayer_C {
    CGUnit_C base;
} CGPlayer_C;