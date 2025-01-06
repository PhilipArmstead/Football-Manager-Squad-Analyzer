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
		// TODO: fix this offset nonsense; we should use the player base where appropriate
		readFromMemory(fd, allPlayers + 8 * i, 4, bytes);
		const unsigned long playersAddress = hexBytesToInt(bytes, 4) + 632;
		u8 potentialAbility;
		readFromMemory(fd, playersAddress + OFFSET_ABILITY + 2, 1, &potentialAbility);
		if (potentialAbility < 160) {
			continue;
		}

		const u8 age = getAge(fd, playersAddress, date);
		if (age >= 20) {
			continue;
		}

		playerList.player[playerList.playerCount++] = getPlayer(fd, playersAddress, date);
		if (playerList.playerCount == playerList.capacity) {
			Player *tmp = realloc(playerList.player, playerList.capacity * 2);
			if (tmp != NULL) {
				free(playerList.player);
				playerList.player = tmp;
				playerList.capacity *= 2;
			}
		}
	}

	// TODO: this heavily duplicates showTeamList
	//  refactor that to take an array of players like this
	//  then combine the functions
	u8 longestName = 0;
	for (unsigned int i = 0; i < playerList.playerCount; ++i) {
		Player *p = &playerList.player[i];
		// TODO: diacritics break this
		p->nameLength = strlen(p->forename) + strlen(p->surname);
		if (p->nameLength > longestName) {
			longestName = p->nameLength;
		}
	}

	for (u8 i = 0; i < longestName + 5; ++i) {
		printf(" ");
	}
	printf(" Age  Ability Inf ");

	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		printf("| %s ", roles[i].name);
		for (u8 j = roles[i].nameLength; j < 6; ++j) {
			printf(" ");
		}
	}
	printf("\n");

	for (unsigned int i = 0; i < playerList.playerCount; ++i) {
		Player *p = &playerList.player[i];

		printf(" %s, %s ", p->surname, p->forename);
		for (u8 j = p->nameLength; j < longestName + 1; ++j) {
			printf(" ");
		}

		printf(" %3d ", p->age);
		printf(" %3d/%3d ", p->ca, p->pa);

		u8 attributes[56];
		readFromMemory(fd, p->address + OFFSET_ATTRIBUTES, 54, attributes);
		u8 personality[8];
		readFromMemory(fd, p->address + OFFSET_PERSONALITY, 8, personality);

		const char fastLearnerString = p->canDevelopQuickly ? 'Q' : ' ';
		const char hotProspectString = p->isHotProspect ? 'H' : ' ';
		printf(" %c%c ", hotProspectString, fastLearnerString);

		u8 positions[15];
		readFromMemory(fd, p->address + OFFSET_POSITIONS, 15, positions);

		for (u8 j = 0; j < ROLE_COUNT; ++j) {
			const short familiarity = positions[roles[j].positionIndex];
			if (familiarity >= 10) {
				double raw = calculateRoleScores(attributes, roles[j].weights);
				raw -= raw * 0.025 * (20 - familiarity);
				char s[8];
				sprintf(s, "%.4g%%", raw);
				printf("| %-6s ", s);
				for (u8 k = 6; k < roles[j].nameLength; ++k) {
					printf(" ");
				}
			} else {
				printf("|");
				const u8 min = roles[j].nameLength < 6 ? 6 : roles[j].nameLength;
				for (u8 k = 0; k < min + 2; ++k) {
					printf(" ");
				}
			}
		}
		printf("\n");
	}

	free(playerList.player);
}
