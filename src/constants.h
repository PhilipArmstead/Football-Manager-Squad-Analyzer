#pragma once

// #define ADDRESS_OF_GLOBAL_POINTERS 0x4306730
// #define OFFSET_GLOBAL_POINTERS_PERSON 0x68
// #define OFFSET_GLOBAL_POINTERS_PLAYER 0x80
// #define OFFSET_GLOBAL_POINTERS_STAFF_PLAYER -0x70
// #define OFFSET_GLOBAL_POINTERS_STAFF_PLAYER_CHECK -0x98

#define POINTER_TO_CURRENT_PERSON 0x15DCD9415
// #define POINTER_TO_MY_TEAM 0x42f8ac8
// #define POINTER_TO_MY_TEAM 0x42f8bb8
// #define POINTER_TO_MY_TEAM 0x42f9508
// #define POINTER_TO_CURRENT_TEAM 0x4302588
// #define POINTER_TO_CURRENT_TEAM 0x43025c8
#define POINTER_TO_CURRENT_TEAM 0x43025f0
#define POINTER_TO_CURRENT_DATETIME 0x14631D5BC

#define POINTER_TO_CURRENT_PLAYER_ID 0x14B1C38E2 // + 0xCC to get player ID
#define POINTER_TO_ALL_PLAYERS 0x14642EDD0
#define PLAYER_COUNT_1 0x14642C034
// #define PLAYER_COUNT_2 0x147971F79

#define OFFSET_ID 0x0C
#define OFFSET_DOB 0x44
#define OFFSET_FORENAME 0x58
#define OFFSET_SURNAME 0x60
#define OFFSET_PERSONALITY 0x78

#define PLAYER_OFFSET_GUIDE_VALUE 0x1D0
#define PLAYER_OFFSET_ABILITY 0x200
#define PLAYER_OFFSET_POTENTIAL_ABILITY 0x202
#define PLAYER_OFFSET_POSITIONS 0x208
#define PLAYER_OFFSET_ATTRIBUTES 0x217
#define PLAYER_OFFSET_DIRTINESS 0x240
#define PLAYER_OFFSET_BRAVERY 0x242
#define PLAYER_OFFSET_CONSISTENCY 0x243
#define PLAYER_OFFSET_HIDDEN_ATTRIBUTES 0x246
#define PLAYER_OFFSET_PERSON 0x278

#define ABILITY_CA 0
#define ABILITY_PA 2

#define ATTRIBUTES_INJURY_PRONENESS 48
#define ATTRIBUTES_DETERMINATION 51

#define PERSONALITY_ADAPTABILITY 0
#define PERSONALITY_AMBITION 1
#define PERSONALITY_LOYALTY 2
#define PERSONALITY_PRESSURE 3
#define PERSONALITY_PROFESSIONALISM 4
#define PERSONALITY_SPORTSMANSHIP 5
#define PERSONALITY_TEMPERAMENT 6
#define PERSONALITY_CONTROVERSY 7
