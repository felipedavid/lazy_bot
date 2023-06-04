#pragma once

typedef enum {
	APT_IGNORE, // To see a player just keep going
	APT_AFK,    // Wait until he is gone
	APT_LOGOUT, // Stops everything and log out
} Anti_Player_Tatic;

typedef enum {
	OFI_LOGOUT,
	OFI_STORE_IN_BANK,
} On_Full_Inventary;

typedef enum {
	OFB_LOGOUT,
} On_Full_Bank;

typedef struct Mods {
	b32 anti_afk;
	Anti_Player_Tatic anti_player_tatic;
	On_Full_Inventary on_full_inventary;
	On_Full_Bank on_full_bank;
} Bot_Options;

typedef struct {
	struct Bot_Options;
	Object_Manager object_manager;
	Fisher fisher;
} Bot;
