#pragma once

#include <unistd.h>

#include "types.h"


static inline void readFromMemory(const int fd, const long address, const int length, unsigned char *bytes) {
	lseek(fd, address, SEEK_SET);
	read(fd, bytes, length);
}

static inline void writeToMemory(const int fd, const long address, const int length, const unsigned char *bytes) {
	lseek(fd, address, SEEK_SET);
	write(fd, bytes, length);
}

void openMemory(Context *ctx);
