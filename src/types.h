#pragma once

typedef unsigned char bool;
typedef unsigned char u8;
typedef unsigned short u16;

#define false 0
#define true 1

typedef struct {
	unsigned long address;
	u8 age;
	u8 ca;
	u8 pa;
	u8 nameLength;
	u8 forename[32];
	u8 surname[32];
	u8 personality[8];
	u8 attributes[56];
	u8 positions[56];
	bool canDevelopQuickly;
	bool isHotProspect;
} Player;

typedef struct {
	Player *player;
	int playerCount;
	int capacity;
} PlayerList;

typedef struct {
	unsigned long address;
	u8 playerCount;
} Team;

typedef struct {
	u8 length;
	Team teams[16];
} TeamList;

typedef struct {
	u16 days;
	u16 year;
} Date;
