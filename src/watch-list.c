#include "watch-list.h"


void addToTeamList(const int fd, TeamList *teamList) {
	unsigned long address = POINTER_TO_CURRENT_TEAM;
	u8 pointer[4];
	u8 pointer2[4];
	readFromMemory(fd, address, 4, pointer);
	address = hexBytesToInt(pointer, 4);
	readFromMemory(fd, address + 0x38, 4, pointer);
	readFromMemory(fd, address + 0x40, 4, pointer2);
	address = hexBytesToInt(pointer, 4);
	const u8 playerCount = (hexBytesToInt(pointer2, 4) - address) / 8;

	u8 index = teamList->length;
	// TODO: we _can_ get this value when we check if this exists in the array initially
	for (u8 i = 0; i < teamList->length; ++i) {
		if (teamList->teams[i].address > address) {
			index = i;
			break;
		}
	}

	for (u8 i = teamList->length; i > index; --i) {
		teamList->teams[i] = teamList->teams[i - 1];
	}

	teamList->teams[index] = (Team){address, playerCount};
	++teamList->length;
}
