
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

typedef struct CGObject_C {
    u8 padding[0x9b8];
} CGObject_C;

typedef struct CGUnit_C {
    CGObject_C base;
    C3Vector m_currentPosition; // unknown real name
} CGUnit_C;

typedef struct CGPlayer_C {
    CGUnit_C base;
} CGPlayer_C;