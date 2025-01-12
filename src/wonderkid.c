#include "wonderkid.h"

#include <player.h>
#include <stdlib.h>
#include <string.h>

#include "analyse.h"
#include "constants.h"
#include "date-time.h"
#include "maths.h"
#include "memory.h"
#include "types.h"
#include "roles/roles.h"


extern const Role roles[ROLE_COUNT];


/** A wonderkid is under 20 years old with a PA >= 160 */
void showWonderkids(const int fd) {
	u8 bytes[4];
	readFromMemory(fd, PLAYER_COUNT_1, 4, bytes);
	const unsigned int playerCount = hexBytesToInt(bytes, 4);

	const Date date = getDate(fd);
	PlayerList playerList = {malloc(50 * sizeof(Player)), 0, 50};

	readFromMemory(fd, POINTER_TO_ALL_PLAYERS, 4, bytes);
	const unsigned long allPlayers = hexBytesToInt(bytes, 4);
	for (unsigned int i = 0; i < playerCount; ++i) {
		readFromMemory(fd, allPlayers + 8 * i, 4, bytes);
		const unsigned long playerAddress = hexBytesToInt(bytes, 4);
		const unsigned long peronAddress = playerAddress + PLAYER_OFFSET_PERSON;
		u8 potentialAbility;
		readFromMemory(fd, playerAddress + PLAYER_OFFSET_ABILITY + 2, 1, &potentialAbility);
		if (potentialAbility < 160) {
			continue;
		}

		const u8 age = getAge(fd, peronAddress, date);
		if (age >= 20) {
			continue;
		}

		playerList.player[playerList.playerCount++] = getPlayer(fd, peronAddress, playerAddress, date);
		if (playerList.playerCount == playerList.capacity) {
			Player *tmp = realloc(playerList.player, playerList.capacity * 2);
			if (tmp != NULL) {
				playerList.player = tmp;
				playerList.capacity *= 2;
			}
		}
	}

	showPlayerList(fd, playerList);

	free(playerList.player);
}
