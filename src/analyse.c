#include <stdio.h>
#include <string.h>

#include "analyse.h"
#include "date-time.h"
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

			u8 ability[3];
			readFromMemory(fd, pAddress + OFFSET_ABILITY, 3, ability);

			players[playerIndex] = (Player){
				pAddress,
				getAge(fd, pAddress, date),
				ability[ABILITY_CA],
				ability[ABILITY_PA]
			};

			getPlayerForename(fd, pAddress, players[playerIndex].forename);
			getPlayerSurname(fd, pAddress, players[playerIndex].surname);

			Player *p = &players[playerIndex];
			// TODO: diacritics break this
			p->nameLength = strlen(p->forename) + strlen(p->surname);
			if (p->nameLength > longestName) {
				longestName = p->nameLength;
			}

			// TODO: cache attributes
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

		const bool canDevelopQuickly = getCanDevelopQuickly(
			p->age,
			attributes[ATTRIBUTES_INJURY_PRONENESS],
			personality[PERSONALITY_AMBITION],
			personality[PERSONALITY_PROFESSIONALISM],
			attributes[ATTRIBUTES_DETERMINATION]
		);
		const bool isHotProspect = getIsHotProspect(p);
		const char fastLearnerString = canDevelopQuickly ? 'Q' : ' ';
		const char hotProspectString = isHotProspect ? 'H' : ' ';
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
	// FIXME: this fails to work when the player is also staff
	u8 bytes[4];
	readFromMemory(fd, POINTER_TO_ATTRIBUTES, 4, bytes);
	const unsigned long attributeBase = hexBytesToInt(bytes, 4);

	u8 positions[15];
	readFromMemory(fd, attributeBase + OFFSET_POSITIONS, 15, positions);

	// Verify player is valid
	for (u8 i = 0; i < 15; ++i) {
		if (positions[i] > 20) {
			printf("Cannot see player.\n");
			return;
		}
	}

	u8 ability[3];
	readFromMemory(fd, attributeBase + OFFSET_ABILITY, 3, ability);
	u8 personality[8];
	readFromMemory(fd, attributeBase + OFFSET_PERSONALITY, 8, personality);
	u8 attributes[56];
	readFromMemory(fd, attributeBase + OFFSET_ATTRIBUTES, 54, attributes);

	Player player = {
		attributeBase,
		getAge(fd, attributeBase, getDate(fd)),
		ability[ABILITY_CA],
		ability[ABILITY_PA],
		0
	};
	getPlayerForename(fd, attributeBase, player.forename);
	getPlayerForename(fd, attributeBase, player.surname);

	printPlayer(&player, attributes, personality, positions);
}

void printPlayer(const Player *player, const u8 attributes[56], const u8 personality[8], const u8 positions[15]) {
	const bool canDevelopQuickly = getCanDevelopQuickly(
		player->age,
		attributes[ATTRIBUTES_INJURY_PRONENESS],
		personality[PERSONALITY_AMBITION],
		personality[PERSONALITY_PROFESSIONALISM],
		attributes[ATTRIBUTES_DETERMINATION]
	);
	const bool isHotProspect = getIsHotProspect(player);
	char *fastLearnerString = canDevelopQuickly ? "Fast learner  " : "";
	char *hotProspectString = isHotProspect ? "Hot prospect  " : "";

	printf("\n\n\n\n\n\n\n\n");

	// TODO: fix positions
	printf(".------------------------------------------.------------------------------------------.\n");
	printf("| %s %s (%d yrs): GK, DL/R, ST\n", player->forename, player->surname, player->age);
	printf("| Ability: %d/%d  %s%s\n", player->ca, player->pa, fastLearnerString, hotProspectString);
	printf(".------------------------------------------.------------------------------------------.\n");

	printf("| Adaptability:  %2d", personality[PERSONALITY_ADAPTABILITY]);
	printf("  Professionalism:  %2d", personality[PERSONALITY_PROFESSIONALISM]);
	printf("  | Consistency:    %2d", (attributes[44] + 4) / 5);
	printf("  Injury proneness:  %2d", (attributes[48] + 4) / 5);
	printf("\n| Ambition:      %2d", personality[PERSONALITY_AMBITION]);
	printf("  Sportsmanship:    %2d", personality[PERSONALITY_SPORTSMANSHIP]);
	printf("  | Determination:  %2d", (attributes[51] + 4) / 5);
	printf("  Versatility:       %2d", (attributes[49] + 4) / 5);
	printf("\n| Loyalty:       %2d", personality[PERSONALITY_LOYALTY]);
	printf("  Temperament:      %2d", personality[PERSONALITY_TEMPERAMENT]);
	printf("  | Dirtiness:      %2d", (attributes[41] + 4) / 5);
	printf("\n| Pressure:      %2d", personality[PERSONALITY_PRESSURE]);
	printf("  Controversy:      %2d", personality[PERSONALITY_CONTROVERSY]);
	printf("  | Imp. Matches:   %2d", (attributes[47] + 4) / 5);

	printf("\n");
	printf(".------------------------------------------.------------------------------------------.\n");

	u8 c = 0;
	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		const short familiarity = positions[roles[i].positionIndex];
		if (familiarity >= 10) {
			double raw = calculateRoleScores(attributes, roles[i].weights);
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
