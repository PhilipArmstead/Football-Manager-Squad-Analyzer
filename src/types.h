#pragma once

typedef unsigned char bool;
typedef unsigned char u8;

typedef struct {
	int fd;
	long attributeBase;
} Context;

typedef struct {
	unsigned long address;
	u8 nameLength;
	u8 forename[32];
	u8 surname[32];
} WatchedPlayer;

typedef struct {
	u8 length;
	WatchedPlayer player[32];
} WatchList;

