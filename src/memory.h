#pragma once

#include <unistd.h>


static inline void readFromMemory(const int fd, const unsigned long address, const int length, u8 *bytes) {
	lseek(fd, address, SEEK_SET);
	read(fd, bytes, length);
}

static inline u8 readByte(const int fd, const unsigned long address) {
	u8 byte;
	lseek(fd, address, SEEK_SET);
	read(fd, &byte, 1);

	return byte;
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
