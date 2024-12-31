#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analyse.h"
#include "./src/types.h"


int main(const int argc, const char *argv[]) {
	// Get process ID for game
	FILE *fp = popen("pidof 'Main Thread'", "r");
	char path[64];
	fgets(path, sizeof(path), fp);
	const long pid = strtol(path, NULL, 10);
	fclose(fp);

	// Get file descriptor for process's memory
	char memoryPath[32];
	sprintf(memoryPath, "/proc/%ld/mem", pid);
	Context ctx = {open(memoryPath, O_RDWR), 0};
	if (ctx.fd == -1) {
		printf("Could not open %s\n", memoryPath);
		exit(1);
	}

	// Parse command line args
	bool autoShow = false;
	for (unsigned int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0) {
			autoShow = true;
			break;
		}
	}

	// Searched for 1152962544
	// unsigned long address = 0x3bc91e00;
	// for (u8 i = 0; i < 23; ++i) {
	// 	u8 pointer[4];
	// 	readFromMemory(ctx->fd, address, 4, pointer);
	// 	address += 0x08;
	// 	const unsigned long pAddress = hexBytesToInt(pointer, 4);
	//
	// 	u8 forename[32] = {0};
	// 	getPlayerForename(ctx->fd, pAddress, forename);
	// 	u8 surname[32] = {0};
	// 	getPlayerSurname(ctx->fd, pAddress, surname);
	//
	// 	printf("%d: %s %s\n", i, forename, surname);
	// }

	WatchList watchList = {0};

	if (autoShow) {
		showPlayerScreen(&ctx, &watchList);
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
			showPlayerScreen(&ctx, &watchList);
		} else if (c == 'l') {
			getchar(); // swallow newline
			showSquadList(&ctx, &watchList);
		}
	}

	// FILE *f = fopen("./watch-list.txt", "w");
	// for (u8 i = 0; i < watchList.length; ++i) {
	// fprintf(f, "%ld\n", watchList.values[i]);
	// }
	// fclose(f);
}
