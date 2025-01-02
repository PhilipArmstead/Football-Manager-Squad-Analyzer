#pragma once

#include "player.h"


static inline void removeFromWatchList(WatchList *watchList, const u8 index) {
	for (u8 i = index; i < watchList->length - 1; ++i) {
		watchList->teams[i].address = watchList->teams[i + 1].address;
	}
	--watchList->length;
}

static inline void addToWatchList(const Context *ctx, WatchList *watchList) {
	unsigned long address = POINTER_TO_CURRENT_TEAM;
	u8 pointer[4];
	u8 pointer2[4];
	readFromMemory(ctx->fd, address, 4, pointer);
	address = hexBytesToInt(pointer, 4);
	readFromMemory(ctx->fd, address + 0x38, 4, pointer);
	readFromMemory(ctx->fd, address + 0x40, 4, pointer2);
	address = hexBytesToInt(pointer, 4);
	const u8 playerCount = (hexBytesToInt(pointer2, 4) - address) / 8;

	u8 index = watchList->length;
	// TODO: we _can_ get this value when we check if this exists in the array initially
	for (u8 i = 0; i < watchList->length; ++i) {
		if (watchList->teams[i].address > address) {
			index = i;
			break;
		}
	}

	for (u8 i = watchList->length; i > index; --i) {
		watchList->teams[i] = watchList->teams[i - 1];
	}

	watchList->teams[index] = (WatchedTeam){address, playerCount};
	++watchList->length;
}
