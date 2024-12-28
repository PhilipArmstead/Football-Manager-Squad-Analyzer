#include <stdio.h>

#include "squad-analyser.h"
#include "analyse.h"

extern const Role roles[ROLE_COUNT];

static inline void removeFromWatchList(Context *ctx, WatchList *watchList, const unsigned char index) {
	for (unsigned char i = index; i < watchList->length - 1; ++i) {
		watchList->values[i] = watchList->values[i + 1];
	}
	--watchList->length;
}

static inline void addToWatchList(Context *ctx, WatchList *watchList, const unsigned long value) {
	unsigned char index = watchList->length;
	// TODO: we _can_ get this value when we check if this exists in the array initially
	for (unsigned char i = 0; i < watchList->length; ++i) {
		if (watchList->values[i] > value) {
			index = i;
			break;
		}
	}

	for (unsigned char i = watchList->length; i > index; --i) {
		watchList->values[i] = watchList->values[i - 1];
	}

	watchList->values[index] = value;
	++watchList->length;
}

void showSquadList(Context *ctx, WatchList *watchList) {}

void showPlayerScreen(Context *ctx, WatchList *watchList) {
	const unsigned long id = printPlayer(ctx);

	unsigned char watchIndex;
	bool isBeingWatched = 0;
	for (unsigned char i = 0; i < watchList->length; ++i) {
		if (watchList->values[i] < i) {
			continue;
		}

		if (watchList->values[i] == id) {
			watchIndex = i;
			isBeingWatched = 1;
		}

		break;
	}

	// TODO: fix this being logged twice
	// TODO: don't offer to watch if the list is full
	// TODO: make a linked list?
	printf(isBeingWatched ? "Un(w)atch player? " : "(w)atch player? ");
	u8 c;
	while ((c = getchar()) != '\n' && c != EOF) {
		if (c == 'w') {
			if (isBeingWatched) {
				removeFromWatchList(ctx, watchList, watchIndex);
			} else {
				addToWatchList(ctx, watchList, id);
			}
		}
	}
}

void run(Context *ctx, const bool autoShow) {
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
