#include "watch-list.h"

#include "club.h"
#include "constants.h"
#include "date-time.h"
#include "memory.h"


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

	teamList->teams[index] = (Team)
	{
		address, playerCount
	};
	++teamList->length;
}

void addToClubList(const int fd, ClubList *clubList, const Club club) {
	clubList->clubs[clubList->length] = club;

	u8 bytes[4];
	// TODO: add offset to constants header file
	readFromMemory(fd, club.address + 0x18, 4, bytes);
	unsigned long squadListAddress = hexBytesToInt(bytes, 4);
	readFromMemory(fd, squadListAddress, 4, bytes);
	unsigned long teamAddress = hexBytesToInt(bytes, 4);

	TeamList *teamList = &clubList->clubs[clubList->length].teamList;
	while (teamAddress) {
		readFromMemory(fd, teamAddress + 0x38, 4, bytes);
		const unsigned long playerStartAddress = hexBytesToInt(bytes, 4);

		if (playerStartAddress) {
			readFromMemory(fd, teamAddress + 0x40, 4, bytes);
			const unsigned long playerEndAddress = hexBytesToInt(bytes, 4);

			u8 teamType;
			readFromMemory(fd, teamAddress + 0x28, 1, &teamType);
			teamList->teams[teamList->length++] = (Team){
				playerStartAddress,
				playerEndAddress - playerStartAddress >> 3,
				teamType
			};
		}

		squadListAddress += 8;
		readFromMemory(fd, squadListAddress, 4, bytes);
		teamAddress = hexBytesToInt(bytes, 4);
	}

	clubList->length++;
}

PlayerList getPlayersFromTeamList(const int fd, const TeamList *teamList) {
	u16 playerCount = 0;
	for (u8 i = 0; i < teamList->length; ++i) {
		playerCount += teamList->teams[i].playerCount;
	}

	const Date date = getDate(fd);
	const PlayerList playerList = {malloc(playerCount * sizeof(Player)), playerCount, playerCount};
	u16 playerIndex = 0;
	for (u8 i = 0; i < teamList->length; ++i) {
		unsigned long address = teamList->teams[i].address;
		for (u8 j = 0; j < teamList->teams[i].playerCount; ++j) {
			u8 pointer[4];
			readFromMemory(fd, address, 4, pointer);
			address += 0x08;
			const unsigned long pAddress = hexBytesToInt(pointer, 4) + 632;

			playerList.player[playerIndex] = getPlayer(fd, pAddress, date);
			++playerIndex;
		}
	}

	return playerList;
}
