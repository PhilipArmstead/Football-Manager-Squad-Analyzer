#include "watch-list.h"

#include <string.h>

#include "club.h"
#include "constants.h"
#include "date-time.h"
#include "memory.h"


void addToClubList(const int fd, Club *watchedClub, const Club *club) {
	watchedClub->address = club->address;
	watchedClub->teamList = (TeamList){0};
	strncpy(watchedClub->name, club->name, 32);

	u8 bytes[4];
	// TODO: add offset to constants header file
	readFromMemory(fd, club->address + 0x18, 4, bytes);
	unsigned long squadListAddress = hexBytesToInt(bytes, 4);
	readFromMemory(fd, squadListAddress, 4, bytes);
	unsigned long teamAddress = hexBytesToInt(bytes, 4);

	while (teamAddress > 255 && teamAddress < 0x80000000) {
		readFromMemory(fd, teamAddress + 0x38, 4, bytes);
		const unsigned long playerStartAddress = hexBytesToInt(bytes, 4);

		if (playerStartAddress) {
			readFromMemory(fd, teamAddress + 0x40, 4, bytes);
			const unsigned long playerEndAddress = hexBytesToInt(bytes, 4);

			u8 teamType;
			readFromMemory(fd, teamAddress + 0x28, 1, &teamType);
			watchedClub->teamList.teams[watchedClub->teamList.length++] = (Team){
				playerStartAddress,
				(playerEndAddress - playerStartAddress) >> 3,
				teamType
			};
		}

		squadListAddress += 8;
		readFromMemory(fd, squadListAddress, 4, bytes);
		teamAddress = hexBytesToInt(bytes, 4);
	}
}

PlayerList getPlayersFromTeamList(const int fd, const TeamList *teamList, const u8 indexList[5]) {
	u16 playerCount = 0;
	for (u8 n = 0; n < 5; ++n) {
		const u8 i = indexList[n];
		if (i == '\n') {
			break;
		}
		playerCount += teamList->teams[i].playerCount;
	}

	const Date date = getDate(fd);
	const PlayerList playerList = {malloc(playerCount * sizeof(Player)), playerCount, playerCount};
	u16 playerIndex = 0;
	for (u8 n = 0; n < 5; ++n) {
		const u8 i = indexList[n];
		if (i == '\n') {
			break;
		}

		unsigned long address = teamList->teams[i].address;
		for (u8 j = 0; j < teamList->teams[i].playerCount; ++j) {
			u8 bytes[5];
			readFromMemory(fd, address, 4, bytes);
			address += 0x08;
			const unsigned long playerAddress = hexBytesToInt(bytes, 4);
			unsigned long personAddress = playerAddress + PLAYER_OFFSET_PERSON;
			readFromMemory(fd, personAddress, 5, bytes);
			while (bytes[3] != 0x45 || bytes[4] != 0x01 || readByte(fd, personAddress + 0x14)) {
				personAddress += 16;
				readFromMemory(fd, personAddress, 5, bytes);
			}

			playerList.player[playerIndex] = getPlayer(fd, personAddress, playerAddress, date);
			++playerIndex;
		}
	}

	return playerList;
}
