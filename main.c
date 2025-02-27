#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "analyse.h"
#include "club.h"
#include "types.h"
#include "wonderkid.h"


int main() {
	FILE *fp = popen("pidof 'Main Thread'", "r");
	char path[64];
	fgets(path, sizeof(path), fp);
	const long pid = strtol(path, NULL, 10);
	fclose(fp);
	if (!pid) {
		printf("Couldn't find process; is it running?\n");
		exit(1);
	}

	char memoryPath[32];
	sprintf(memoryPath, "/proc/%ld/mem", pid);
	const int fd = open(memoryPath, O_RDWR);
	if (fd == -1) {
		printf("Couldn't open %s\n", memoryPath);
		exit(2);
	}

	srand(time(NULL));

	Club watchedClub = {0};
	while (1) {
		printf("\n");
		printf("show current (p)layer\n");
		if (watchedClub.address) {
			printf("(l)ist %s squads\n", watchedClub.name);
		}
		printf("(f)ind wonderkids\n");
		printf("e(x)it\n");
		const u8 c = getchar();
		if (c == 'x') {
			break;
		}

		if (c != '\n') {
			getchar(); // swallow newline
		}

		switch (c) {
			case 'f': {
				showWonderkids(fd);
				break;
			}
			case 'l': {
				if (watchedClub.address) {
					showClubPrompt(fd, &watchedClub);
				}
				break;
			}
			case 'p': {
				showPlayerScreen(fd, &watchedClub);
				break;
			}
			default:
				break;
		}
	}
}
