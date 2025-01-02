#pragma once

typedef unsigned char bool;
typedef unsigned char u8;
typedef unsigned short u16;

#define false 0
#define true 1

typedef struct {
	int fd;
	long attributeBase;
} Context;

typedef struct {
	unsigned long address;
	u8 nameLength;
	u8 forename[32];
	u8 surname[32];
} Player;

typedef struct {
	unsigned long address;
	u8 playerCount;
} WatchedTeam;

typedef struct {
	u8 length;
	WatchedTeam teams[16];
} WatchList;

typedef struct {
	u16 days;
	u16 year;
} Date;
