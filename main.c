#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <watch-list.h>

#include "analyse.h"
#include "types.h"


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

	WatchList watchList = {0};

	if (autoShow) {
		showPlayerScreen(&ctx);
	}

	while (1) {
		printf("\n(s)how player profile\n");
		if (watchList.length) {
			printf("(l)ist watched teams\n");
		}
		printf("(w)atch current team\n");
		printf("e(x)it\n");
		const u8 c = getchar();
		if (c == 'x') {
			break;
		}

		getchar(); // swallow newline
		switch (c) {
		case 'l': {
			showSquadList(&ctx, &watchList);
			break;
		}
		case 's': {
			showPlayerScreen(&ctx);
			break;
		}
		case 'w': {
			// TODO: ad error checking around this
			addToWatchList(&ctx, &watchList);
			break;
		}
		}
	}
}
