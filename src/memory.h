#pragma once

#include <unistd.h>


static inline void readFromMemory(const int fd, const unsigned long address, const int length, u8 *bytes) {
	lseek(fd, address, SEEK_SET);
	read(fd, bytes, length);
}

static inline void writeToMemory(
	const int fd,
	const unsigned long address,
	const int length,
	const u8 *bytes
) {
	lseek(fd, address, SEEK_SET);
	write(fd, bytes, length);
}
