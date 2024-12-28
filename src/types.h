#pragma once

typedef unsigned char bool;
typedef unsigned char u8;

typedef struct {
	int fd;
	char memoryPath[32];
	long attributeBase;
} Context;

typedef struct {
	u8 length;
	unsigned long values[32];
} WatchList;

