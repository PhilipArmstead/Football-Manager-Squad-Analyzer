#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "maths.h"


void openMemory(Context *ctx) {
	if (ctx->fd) {
		close(ctx->fd);
	}

	ctx->fd = open(ctx->memoryPath, O_RDWR);
	if (ctx->fd == -1) {
		printf("Could not open %s\n", ctx->memoryPath);
		exit(1);
	}

	// FIXME: this fails to work when the player is also staff
	const long pointerAttributes = 0x15DCD9415;
	unsigned char bytes[4];
	readFromMemory(ctx->fd, pointerAttributes, 4, bytes);
	ctx->attributeBase = hexBytesToInt(bytes, 4);
}
