#include <unistd.h>

#include "wonderkid.h"


// TODO: this needs work before it becomes the final Wonderkid generator.
//  It's pretty naive right now
void makePerfect(const int fd, const long address) {
	const char max = 100;
	const char min = 1;

	lseek(fd, address - 0x61, SEEK_SET);
	for (short i = 0; i < 41; ++i) {
		write(fd, &max, 1);
	}

	write(fd, &min, 1);
	for (short i = 0; i < 6; ++i) {
		write(fd, &max, 1);
	}
	write(fd, &min, 1);
	for (short i = 0; i < 5; ++i) {
		write(fd, &max, 1);
	}

	lseek(fd, address + 0x78, SEEK_SET);
	const char twenty = 20;
	for (short i = 0; i < 8; ++i) {
		write(fd, &twenty, 1);
	}
}
