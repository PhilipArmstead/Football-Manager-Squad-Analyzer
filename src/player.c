#include "player.h"
#include "analyse.h"
#include "constants.h"
#include "maths.h"
#include "memory.h"
#include "strings.h"
#include "roles.h"


extern const Role roles[ROLE_COUNT];


static inline void getPlayerName(const int fd, u8 pointer[4], u8 str[32]) {
	unsigned long a = hexBytesToInt(pointer, 4);
	readFromMemory(fd, a, 4, pointer);
	a = hexBytesToInt(pointer, 4);
	readFromMemory(fd, a + 4, 32, str);
}

static inline void getPlayerForename(const int fd, const unsigned long attributeBase, u8 str[32]) {
	u8 pointer[4];
	readFromMemory(fd, attributeBase + OFFSET_FORENAME, 4, pointer);
	getPlayerName(fd, pointer, str);
}

static inline void getPlayerSurname(const int fd, const unsigned long attributeBase, u8 str[32]) {
	u8 pointer[4];
	readFromMemory(fd, attributeBase + OFFSET_SURNAME, 4, pointer);
	getPlayerName(fd, pointer, str);
}

Player getPlayer(const int fd, const unsigned long peronAddress, const unsigned long playerAddress, const Date date) {
	u8 ability[3];
	readFromMemory(fd, playerAddress + PLAYER_OFFSET_ABILITY, 3, ability);

	Player player = {
		peronAddress,
		playerAddress,
		getAge(fd, peronAddress, date),
		ability[ABILITY_CA],
		ability[ABILITY_PA],
		0
	};
	getPlayerForename(fd, peronAddress, player.forename);
	getPlayerSurname(fd, peronAddress, player.surname);
	readFromMemory(fd, peronAddress + OFFSET_PERSONALITY, 8, player.personality);
	readFromMemory(fd, playerAddress + PLAYER_OFFSET_ATTRIBUTES, 54, player.attributes);
	readFromMemory(fd, playerAddress + PLAYER_OFFSET_POSITIONS, 15, player.positions);

	for (u8 j = 0; j < ROLE_COUNT; ++j) {
		const short familiarity = player.positions[roles[j].positionIndex];
		if (familiarity >= 10) {
			float raw = calculateRoleScores(player.attributes, roles[j].weights);
			raw -= raw * 0.025 * (20 - familiarity);
			player.roles[j] = raw;
		} else {
			player.roles[j] = 0;
		}
	}

	player.canDevelopQuickly = player.age <= 23 &&
		player.attributes[ATTRIBUTES_INJURY_PRONENESS] < 70 &&
		player.personality[PERSONALITY_AMBITION] > 10 &&
		player.personality[PERSONALITY_PROFESSIONALISM] > 10 &&
		player.attributes[ATTRIBUTES_DETERMINATION] > 50;

	if (player.age <= 19) {
		player.isHotProspect = player.ca >= 80 + 5 * (player.age - 15);
	} else if (player.age <= 23) {
		player.isHotProspect = player.ca >= 140;
	} else {
		player.isHotProspect = false;
	}

	u8 bytes[4];
	readFromMemory(fd, playerAddress + PLAYER_OFFSET_GUIDE_VALUE, 4, bytes);
	player.guideValue = hexBytesToInt(bytes, 4);

	return player;
}

bool isPlayerValid(const int fd, const unsigned long personAddress, const unsigned long playerAddress) {
	for (u8 i = 0; i < 5; ++i) {
		const u8 attribute = readByte(fd, playerAddress + PLAYER_OFFSET_HIDDEN_ATTRIBUTES + i);
		if (!attribute || attribute > 100) {
			return false;
		}
	}
	for (u8 i = 0; i < 8; ++i) {
		const u8 attribute = readByte(fd, personAddress + OFFSET_PERSONALITY + i);
		if (!attribute || attribute > 20) {
			return false;
		}
	}

	return true;
}

void healPlayer(const int fd, const unsigned long playerAddress) {
	u8 bytes[4];
	readFromMemory(fd, playerAddress + PLAYER_OFFSET_INJURY_POINTER, 4, bytes);
	const unsigned long injuryAddress = hexBytesToInt(bytes, 4);
	writeToMemory(fd, injuryAddress, 16, (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

	// Set sharpness to 10,000, fatigue to 0 and condition to 10,000
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_SHARPNESS, 6, (u8[]){0x10, 0x27, 0, 0, 0x10, 0x27});
}

void showPlayerList(const int fd, const PlayerList playerList) {
	u8 longestName = 0;
	for (unsigned int i = 0; i < playerList.playerCount; ++i) {
		Player *p = &playerList.player[i];
		p->nameLength = getNameLength(p->forename, p->surname);
		if (p->nameLength > longestName) {
			longestName = p->nameLength;
		}
	}

	for (u8 i = 0; i < longestName + 4; ++i) {
		printf(" ");
	}
	printf("Age  Ability Inf ");

	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		printf("| %s ", roles[i].name);
		for (u8 j = roles[i].nameLength; j < 6; ++j) {
			printf(" ");
		}
	}
	printf("\n");

	for (unsigned int i = 0; i < playerList.playerCount; ++i) {
		Player *p = &playerList.player[i];

		printf(" %s %s", p->forename, p->surname);
		for (u8 j = p->nameLength; j < longestName + 1; ++j) {
			printf(" ");
		}

		printf(" %3d ", p->age);
		printf(" %3d/%3d ", p->ca, p->pa);

		const char fastLearnerString = p->canDevelopQuickly ? 'Q' : ' ';
		const char hotProspectString = p->isHotProspect ? 'H' : ' ';
		printf(" %c%c ", hotProspectString, fastLearnerString);

		for (u8 j = 0; j < ROLE_COUNT; ++j) {
			const float rating = p->roles[j];
			if (rating) {
				char s[8];
				sprintf(s, "%.4g%%", rating);
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
}
