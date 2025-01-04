#include <stdio.h>
#include <string.h>

#include "analyse.h"
#include "constants.h"
#include "date-time.h"
#include "memory.h"
#include "roles.h"
#include "watch-list.h"


extern const Role roles[ROLE_COUNT];

// TODO: add option to sort by columns
void showTeamList(const int fd, const TeamList *teamList) {
	u16 playerCount = 0;
	for (u8 i = 0; i < teamList->length; ++i) {
		playerCount += teamList->teams[i].playerCount;
	}

	u8 longestName = 0;
	const Date date = getDate(fd);
	Player players[playerCount];
	u16 playerIndex = 0;
	for (u8 i = 0; i < teamList->length; ++i) {
		unsigned long address = teamList->teams[i].address;
		for (u8 j = 0; j < teamList->teams[i].playerCount; ++j) {
			u8 pointer[4];
			readFromMemory(fd, address, 4, pointer);
			address += 0x08;
			const unsigned long pAddress = hexBytesToInt(pointer, 4) + 632;

			players[playerIndex] = getPlayer(fd, pAddress, date);

			Player *p = &players[playerIndex];
			// TODO: diacritics break this
			p->nameLength = strlen(p->forename) + strlen(p->surname);
			if (p->nameLength > longestName) {
				longestName = p->nameLength;
			}

			++playerIndex;
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

	for (u16 i = 0; i < playerCount; ++i) {
		Player *p = &players[i];

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
}

void showPlayerScreen(const int fd) {
	u8 bytes[4];
	readFromMemory(fd, POINTER_TO_ATTRIBUTES, 4, bytes);
	const unsigned long attributeBase = hexBytesToInt(bytes, 4);
	Player player = getPlayer(fd, attributeBase, getDate(fd));

	while (true) {
		printPlayer(&player);

		u8 c = '\n';
		if (isPlayerValid(fd, player.address)) {
			printf("\nMake (w)onderkid\n");
			printf("(d)estroy player\n");
			printf("Press anything else to return\n");
			c = getchar();
		}

		const u8 a = c;

		// swallow newline
		while (c != '\n') {
			c = getchar();
		}

		if (a == 'w') {
			makeWonderkid(fd, player.address);
			player = getPlayer(fd, player.address, getDate(fd));
		} else if (a == 'd') {
			destroyPlayer(fd, player.address);
			player = getPlayer(fd, player.address, getDate(fd));
		} else {
			break;
		}
	}
}

void printPlayer(const Player *p) {
	char *fastLearnerString = p->canDevelopQuickly ? "Fast learner  " : "";
	char *hotProspectString = p->isHotProspect ? "Hot prospect  " : "";

	printf("\n\n\n\n\n\n\n\n");

	printf(".------------------------------------------.------------------------------------------.\n");
	printf("| %s %s (%d yrs): ", p->forename, p->surname, p->age);
	printPlayerPositions(p);
	printf("\n");

	printf("| Ability: %d/%d  %s%s\n", p->ca, p->pa, fastLearnerString, hotProspectString);
	printf(".------------------------------------------.------------------------------------------.\n");

	printf("| Adaptability:  %2d", p->personality[PERSONALITY_ADAPTABILITY]);
	printf("  Professionalism:  %2d", p->personality[PERSONALITY_PROFESSIONALISM]);
	printf("  | Consistency:    %2d", (p->attributes[44] + 4) / 5);
	printf("  Injury proneness:  %2d", (p->attributes[48] + 4) / 5);
	printf("\n| Ambition:      %2d", p->personality[PERSONALITY_AMBITION]);
	printf("  Sportsmanship:    %2d", p->personality[PERSONALITY_SPORTSMANSHIP]);
	printf("  | Determination:  %2d", (p->attributes[51] + 4) / 5);
	printf("  Versatility:       %2d", (p->attributes[49] + 4) / 5);
	printf("\n| Loyalty:       %2d", p->personality[PERSONALITY_LOYALTY]);
	printf("  Temperament:      %2d", p->personality[PERSONALITY_TEMPERAMENT]);
	printf("  | Dirtiness:      %2d", (p->attributes[41] + 4) / 5);
	printf("\n| Pressure:      %2d", p->personality[PERSONALITY_PRESSURE]);
	printf("  Controversy:      %2d", p->personality[PERSONALITY_CONTROVERSY]);
	printf("  | Imp. Matches:   %2d", (p->attributes[47] + 4) / 5);

	printf("\n");
	printf(".------------------------------------------.------------------------------------------.\n");

	u8 c = 0;
	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		const short familiarity = p->positions[roles[i].positionIndex];
		if (familiarity >= 10) {
			double raw = calculateRoleScores(p->attributes, roles[i].weights);
			raw -= raw * 0.025 * (20 - familiarity);
			if (!i) {
				printf("| %s: %.4g%% ", roles[i].name, raw);
			} else {
				printf("| %-9s: %.4g%% ", roles[i].name, raw);
			}
			++c;
		}

		if (c == 2 || i == ROLE_COUNT - 1) {
			printf("\n");
			c = 0;
		}
	}
}

float calculateRoleScores(const u8 attributes[54], const u8 weights[54]) {
	float totalScore = 0;
	float totalWeight = 0;
	for (u8 i = 0; i < 54; ++i) {
		totalScore += (float)(attributes[i] * weights[i]);
		totalWeight += (float)weights[i];
	}

	return totalWeight ? totalScore / totalWeight : 0;
}
