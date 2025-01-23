#include "club.h"

#include "maths.h"
#include "memory.h"


Club getClubFromPerson(const int fd, const unsigned long personAddress) {
	u8 pointer[4];
	// TODO: put these offsets in constants.h
	readFromMemory(fd, personAddress + 0xC8, 4, pointer);
	const unsigned long contractAddress = hexBytesToInt(pointer, 4);
	readFromMemory(fd, contractAddress + 0x10, 4, pointer);
	const unsigned long clubAddress = hexBytesToInt(pointer, 4);
	readFromMemory(fd, clubAddress + 0x30, 4, pointer);
	const unsigned long teamsAddress = hexBytesToInt(pointer, 4);
	readFromMemory(fd, teamsAddress + 0xC0, 4, pointer);
	const unsigned long longNameAddress = hexBytesToInt(pointer, 4);

	Club club = {teamsAddress};
	readFromMemory(fd, longNameAddress + 0x04, 32, club.name);

	return club;
}
