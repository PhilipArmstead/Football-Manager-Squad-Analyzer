#include <stdio.h>
#include <string.h>

#include "analyse.h"
#include "date-time.h"
#include "roles.h"
#include "watch-list.h"


extern const Role roles[ROLE_COUNT];

void showSquadList(const Context *ctx, WatchList *watchList) {
	// Get the length of the longest player name
	// Possibly cache the lengths too so we don't need to do this again
	u8 longestName = 0;
	for (u8 i = 0; i < watchList->length; ++i) {
		WatchedPlayer *p = &watchList->player[i];
		if (!p->nameLength) {
			// TODO: diacritics break this
			p->nameLength = strlen(p->forename) + strlen(p->surname);
		}
		if (p->nameLength > longestName) {
			longestName = p->nameLength;
		}
	}

	for (u8 i = 0; i < longestName + 5; ++i) {
		printf(" ");
	}
	printf("| Age ");
	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		printf("| %s ", roles[i].name);
		for (u8 j = roles[i].nameLength; j < 6; ++j) {
			printf(" ");
		}
	}
	printf("|\n");

	const Date date = getDate(ctx->fd);
	for (u8 i = 0; i < watchList->length; ++i) {
		WatchedPlayer *p = &watchList->player[i];

		printf("| %s, %s ", p->surname, p->forename);
		for (u8 j = p->nameLength; j < longestName; ++j) {
			printf(" ");
		}

		printf("| %3d ", getAge(ctx->fd, p->address, date));

		u8 positions[15];
		readFromMemory(ctx->fd, p->address + OFFSET_POSITIONS, 15, positions);
		u8 attributes[56];
		readFromMemory(ctx->fd, p->address + OFFSET_ATTRIBUTES, 54, attributes);

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

void showPlayerScreen(const Context *ctx, WatchList *watchList) {
	// FIXME: this fails to work when the player is also staff
	u8 bytes[4];
	readFromMemory(ctx->fd, POINTER_TO_ATTRIBUTES, 4, bytes);
	const unsigned long attributeBase = hexBytesToInt(bytes, 4);

	u8 positions[15];
	readFromMemory(ctx->fd, attributeBase + OFFSET_POSITIONS, 15, positions);

	// Verify player is valid
	for (u8 i = 0; i < 15; ++i) {
		if (positions[i] > 20) {
			printf("Cannot see player.\n");
			return;
		}
	}

	u8 ability[3];
	readFromMemory(ctx->fd, attributeBase + OFFSET_ABILITY, 3, ability);
	u8 personality[8];
	readFromMemory(ctx->fd, attributeBase + OFFSET_PERSONALITY, 8, personality);
	u8 attributes[56];
	readFromMemory(ctx->fd, attributeBase + OFFSET_ATTRIBUTES, 54, attributes);
	u8 forename[32];
	getPlayerForename(ctx->fd, attributeBase, forename);
	u8 surname[32];
	getPlayerSurname(ctx->fd, attributeBase, surname);
	u8 age = getAge(ctx->fd, attributeBase, getDate(ctx->fd));

	printPlayer(ability, attributes, personality, positions, forename, surname, age);

	u8 watchIndex;
	bool isBeingWatched = false;
	for (u8 i = 0; i < watchList->length; ++i) {
		if (watchList->player[i].address < i) {
			continue;
		}

		if (watchList->player[i].address == attributeBase) {
			watchIndex = i;
			isBeingWatched = true;
		}

		break;
	}

	// TODO: don't offer to watch if the list is full
	// TODO: make a linked list?
	printf(isBeingWatched ? "Un(w)atch player? " : "(w)atch player? ");
	u8 c;
	while ((c = getchar()) != '\n' && c != EOF) {
		if (c == 'w') {
			if (isBeingWatched) {
				removeFromWatchList(watchList, watchIndex);
			} else {
				addToWatchList(ctx, attributeBase, watchList);
			}
		}
	}
}

void printPlayer(
	const u8 ability[3],
	const u8 attributes[56],
	const u8 personality[8],
	const u8 positions[15],
	const u8 forename[32],
	const u8 surname[32],
	const u8 age
) {
	const bool canDevelopQuickly = getCanDevelopQuickly(
		age,
		attributes[ATTRIBUTES_INJURY_PRONENESS],
		personality[PERSONALITY_AMBITION],
		personality[PERSONALITY_PROFESSIONALISM],
		attributes[ATTRIBUTES_DETERMINATION]
	);
	const bool isHotProspect = getIsHotProspect(age, ability[ABILITY_CA]);
	char *fastLearnerString = canDevelopQuickly ? "Fast learner  " : "";
	char *hotProspectString = isHotProspect ? "Hot prospect  " : "";

	printf("\n\n\n\n\n\n\n\n");

	// TODO: fix positions
	printf(".------------------------------------------.------------------------------------------.\n");
	printf("| %s %s (%d yrs): GK, DL/R, ST\n", forename, surname, age);
	printf("| Ability: %d/%d  %s%s\n", ability[ABILITY_CA], ability[ABILITY_PA], fastLearnerString, hotProspectString);
	printf(".------------------------------------------.------------------------------------------.\n");

	printf("| Adaptability:  %2d", personality[PERSONALITY_ADAPTABILITY]);
	printf("  Professionalism:  %2d", personality[PERSONALITY_PROFESSIONALISM]);
	printf("  | Consistency:    %2d", attributes[44]);
	printf("  Injury proneness:  %2d", attributes[48]);
	printf("\n| Ambition:      %2d", personality[PERSONALITY_AMBITION]);
	printf("  Sportsmanship:    %2d", personality[PERSONALITY_SPORTSMANSHIP]);
	printf("  | Determination:  %2d", attributes[51]);
	printf("  Versatility:       %2d", attributes[49]);
	printf("\n| Loyalty:       %2d", personality[PERSONALITY_LOYALTY]);
	printf("  Temperament:      %2d", personality[PERSONALITY_TEMPERAMENT]);
	printf("  | Dirtiness:      %2d", attributes[41]);
	printf("\n| Pressure:      %2d", personality[PERSONALITY_PRESSURE]);
	printf("  Controversy:      %2d", personality[PERSONALITY_CONTROVERSY]);
	printf("  | Imp. Matches:   %2d", attributes[47]);

	printf("\n");
	printf(".------------------------------------------.------------------------------------------.\n");

	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		const short familiarity = positions[roles[i].positionIndex];
		if (familiarity >= 10) {
			double raw = calculateRoleScores(attributes, roles[i].weights);
			raw -= raw * 0.025 * (20 - familiarity);
			printf("| %s: %.4g%%\n", roles[i].name, raw);
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
