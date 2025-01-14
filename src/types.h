#pragma once

typedef unsigned char bool;
typedef unsigned char u8;
typedef unsigned short u16;

#define false 0
#define true 1

typedef struct {
	unsigned long personAddress;
	unsigned long playerAddress;
	u8 age;
	u8 ca;
	u8 pa;
	u8 nameLength;
	u8 forename[32];
	u8 surname[32];
	u8 personality[8];
	u8 attributes[56];
	u8 positions[15];
	bool canDevelopQuickly;
	bool isHotProspect;
	unsigned int guideValue;
	unsigned int annualWage;
} Player;

typedef struct {
	Player *player;
	int playerCount;
	int capacity;
} PlayerList;

typedef struct {
	unsigned long address;
	u8 playerCount;
	u8 teamType;
} Team;

typedef struct {
	u8 length;
	Team teams[5];
} TeamList;

typedef struct {
	unsigned long address;
	TeamList teamList;
	u8 name[32];
} Club;

typedef struct {
	u16 days;
	u16 year;
} Date;
