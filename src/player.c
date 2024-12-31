#include "player.h"

#include "constants.h"
#include "maths.h"
#include "memory.h"


u8 getAge(const int fd, const unsigned long address, const Date date) {
	u8 bytes[4];
	readFromMemory(fd, address + OFFSET_DOB, 4, bytes);
	const u8 yearBytes[2] = {bytes[2], bytes[3]};
	const u16 yearOfBirth = hexBytesToInt(yearBytes, 2);
	const u16 dayOfBirth = hexBytesToInt(bytes, 2);

	u8 age = date.year - yearOfBirth;
	if (date.days < dayOfBirth) {
		--age;
	}

	return age;
}
