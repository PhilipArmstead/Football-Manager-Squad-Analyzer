#include <stdio.h>

#include "squad-analyser.h"
#include "analyse.h"
#include "constants.h"
#include "maths.h"
#include "memory.h"
#include "roles.h"


extern const Role roles[ROLE_COUNT];

static inline void removeFromWatchList(WatchList *watchList, const u8 index) {
	for (u8 i = index; i < watchList->length - 1; ++i) {
		watchList->values[i] = watchList->values[i + 1];
	}
	--watchList->length;
}

static inline void addToWatchList(const unsigned long attributeBase, WatchList *watchList) {
	u8 index = watchList->length;
	// TODO: we _can_ get this value when we check if this exists in the array initially
	for (u8 i = 0; i < watchList->length; ++i) {
		if (watchList->values[i] > attributeBase) {
			index = i;
			break;
		}
	}

	for (u8 i = watchList->length; i > index; --i) {
		watchList->values[i] = watchList->values[i - 1];
	}

	watchList->values[index] = attributeBase;
	++watchList->length;
}

void showSquadList(const Context *ctx, const WatchList *watchList) {
	printf("             ");
	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		printf("| %s ", roles[i].name);
	}
	printf("|\n");

	for (u8 i = 0; i < watchList->length; ++i) {
		const unsigned long address = watchList->values[i];

		u8 idString[4];
		readFromMemory(ctx->fd, address + OFFSET_ID, 4, idString);
		printf("| %ld ", hexBytesToInt(idString, 4));

		u8 positions[15];
		readFromMemory(ctx->fd, address + OFFSET_POSITIONS, 15, positions);
		u8 attributes[56];
		readFromMemory(ctx->fd, address + OFFSET_ATTRIBUTES, 54, attributes);

		for (u8 j = 0; j < ROLE_COUNT; ++j) {
			const short familiarity = positions[roles[j].positionIndex];
			if (familiarity >= 10) {
				double raw = calculateRoleScores(attributes, *roles[j].weights);
				raw -= raw * 0.025 * (20 - familiarity);
				char s[8];
				sprintf(s, "%.4g%%", raw);
				printf("| %-6s    ", s);
			} else {
				printf("|           ");
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

	u8 idString[4];
	readFromMemory(ctx->fd, attributeBase + OFFSET_ID, 4, idString);
	const unsigned long id = hexBytesToInt(idString, 4);
	u8 ability[3];
	readFromMemory(ctx->fd, attributeBase + OFFSET_ABILITY, 3, ability);
	u8 personality[8];
	readFromMemory(ctx->fd, attributeBase + OFFSET_PERSONALITY, 8, personality);
	u8 attributes[56];
	readFromMemory(ctx->fd, attributeBase + OFFSET_ATTRIBUTES, 54, attributes);

	printPlayer(id, ability, attributes, personality, positions);

	u8 watchIndex;
	bool isBeingWatched = 0;
	for (u8 i = 0; i < watchList->length; ++i) {
		if (watchList->values[i] < i) {
			continue;
		}

		if (watchList->values[i] == attributeBase) {
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
				addToWatchList(attributeBase, watchList);
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
