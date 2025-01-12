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
#define POINTER_TO_CURRENT_PLAYER_ROW_ID 0x4EB0F8E8 // Look up in all player pointer
#define POINTER_TO_ALL_PLAYERS 0x14642EDD0
#define PLAYER_COUNT_1 0x14642C034
// #define PLAYER_COUNT_2 0x147971F79

#define OFFSET_DOB 0x44
#define OFFSET_FORENAME 0x58
#define OFFSET_SURNAME 0x60
#define OFFSET_ABILITY -0x78
#define OFFSET_POTENTIAL_ABILITY -0x76
#define OFFSET_POSITIONS -0x70
#define OFFSET_ATTRIBUTES -0x61
#define OFFSET_DIRTINESS -0x38
#define OFFSET_BRAVERY -0x36
#define OFFSET_CONSISTENCY -0x35
#define OFFSET_HIDDEN_ATTRIBUTES -0x32
#define OFFSET_ID 0x0C
#define OFFSET_PERSONALITY 0x78

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
