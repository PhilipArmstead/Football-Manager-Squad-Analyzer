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

// FIXME: this fails to work when the player is also staff
Player getPlayer(const int fd, const unsigned long address, const Date date) {
	u8 ability[3];
	readFromMemory(fd, address + OFFSET_ABILITY, 3, ability);

	Player player = {
		address,
		getAge(fd, address, date),
		ability[ABILITY_CA],
		ability[ABILITY_PA],
		0
	};
	getPlayerForename(fd, address, player.forename);
	getPlayerSurname(fd, address, player.surname);
	readFromMemory(fd, address + OFFSET_PERSONALITY, 8, player.personality);
	readFromMemory(fd, address + OFFSET_ATTRIBUTES, 54, player.attributes);
	readFromMemory(fd, address + OFFSET_POSITIONS, 15, player.positions);

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

	return player;
}

bool isPlayerValid(const int fd, const unsigned long address) {
	for (u8 i = 0; i < 5; ++i) {
		const u8 attribute = readByte(fd, address + OFFSET_HIDDEN_ATTRIBUTES + i);
		if (!attribute || attribute > 100) {
			return false;
		}
	}
	for (u8 i = 0; i < 8; ++i) {
		const u8 attribute = readByte(fd, address + OFFSET_PERSONALITY + i);
		if (!attribute || attribute > 20) {
			return false;
		}
	}

	return true;
}

// TODO: add option to sort by columns
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
}
