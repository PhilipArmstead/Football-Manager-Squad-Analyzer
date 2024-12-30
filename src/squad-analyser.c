#include <stdio.h>
#include <string.h>

#include "squad-analyser.h"
#include "analyse.h"
#include "constants.h"
#include "date-time.h"
#include "maths.h"
#include "memory.h"
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

static inline void removeFromWatchList(WatchList *watchList, const u8 index) {
	for (u8 i = index; i < watchList->length - 1; ++i) {
		watchList->player[i] = watchList->player[i + 1];
	}
	--watchList->length;
}

static inline void addToWatchList(const Context *ctx, unsigned long attributeBase, WatchList *watchList) {
	u8 index = watchList->length;
	// TODO: we _can_ get this value when we check if this exists in the array initially
	for (u8 i = 0; i < watchList->length; ++i) {
		if (watchList->player[i].address > attributeBase) {
			index = i;
			break;
		}
	}

	for (u8 i = watchList->length; i > index; --i) {
		watchList->player[i] = watchList->player[i - 1];
	}

	watchList->player[index] = (WatchedPlayer){attributeBase, 0};
	getPlayerForename(ctx->fd, attributeBase, watchList->player[index].forename);
	getPlayerSurname(ctx->fd, attributeBase, watchList->player[index].surname);
	++watchList->length;
}

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

	for (u8 i = 0; i < longestName + 4; ++i) {
		printf(" ");
	}
	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		printf("| %s ", roles[i].name);
		for (u8 j = roles[i].nameLength; j < 6; ++j) {
			printf(" ");
		}
	}
	printf("|\n");


	for (u8 i = 0; i < watchList->length; ++i) {
		WatchedPlayer *p = &watchList->player[i];

		printf("| %s, %s ", p->surname, p->forename);
		for (u8 j = p->nameLength; j < longestName; ++j) {
			printf(" ");
		}

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

	printPlayer(ability, attributes, personality, positions, forename, surname);

	u8 watchIndex;
	bool isBeingWatched = 0;
	for (u8 i = 0; i < watchList->length; ++i) {
		if (watchList->player[i].address < i) {
			continue;
		}

		if (watchList->player[i].address == attributeBase) {
			watchIndex = i;
			isBeingWatched = 1;
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

void run(const Context *ctx, const bool autoShow) {
	WatchList watchList = {0};

	if (autoShow) {
		showPlayerScreen(ctx, &watchList);
	}

	while (1) {
		printf("\n(s)how player profile\n");
		if (watchList.length) {
			printf("(l)ist watched players\n");
		}
		printf("e(x)it\n");
		const u8 c = getchar();
		if (c == 'x') {
			break;
		}

		if (c == 's') {
			getchar(); // swallow newline
			showPlayerScreen(ctx, &watchList);
		} else if (c == 'l') {
			getchar(); // swallow newline
			showSquadList(ctx, &watchList);
		}
	}

	// FILE *f = fopen("./watch-list.txt", "w");
	// for (u8 i = 0; i < watchList.length; ++i) {
	// fprintf(f, "%ld\n", watchList.values[i]);
	// }
	// fclose(f);
}
