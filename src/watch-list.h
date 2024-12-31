#pragma once

#include "player.h"


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
