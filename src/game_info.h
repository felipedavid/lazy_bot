#pragma once

enum Game_Functions {
    CAST_SPELL_FUN = 0x0080DA40,
};

enum Object_Manager_Offsets {
    CLIENT_CONNECTION = 0x00C79CE0,
    ENTITY_MANAGER    = 0x2ED0,
    FIRST_ENTITY      = 0xAC,
    NEXT_ENTITY       = 0x3C,
};

enum Entity_Offsets {
    ENT_TYPE       = 0x14,
    ENT_DESCRIPTOR = 0x8,
};

enum Game_Object_Offsets {
    GAME_OBJ_CREATED_BY = 0x18,
    GAME_OBJ_DISPLAY_ID = 0x20,
    GAME_OBJ_FLAGS      = 0x24,
    GAME_OBJ_POSITION   = 0xE8,
};

enum Unit_Offsets {
    UNIT_POSITION   = 0x798,
    UNIT_CHANNEL_ID = 0xA80,
};

enum Local_Player_Offsets {
    LOCAL_PLAYER_GUID = 0x00CA1238,
    LOCAL_PLAYER_NAME = 0x00C79D18,
};

enum VFT_Table_Indexes {
    INTERACT_INDEX = 44,
};

enum Spell_ID {
    SPELL_ID_FISHING = 7620,
};

enum Display_ID {
    DISPLAY_ID_FISHING_BOBBER = 668,
};
