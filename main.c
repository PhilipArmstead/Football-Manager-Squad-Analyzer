#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <watch-list.h>

#include "analyse.h"
#include "types.h"


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

	TeamList teamList = {0};
	while (1) {
		printf("\nshow current (p)layer\n");
		printf("show current (t)eam\n");
		if (teamList.length) {
			printf("(l)ist watched teams\n");
		}
		printf("(w)atch current team\n");
		printf("e(x)it\n");
		const u8 c = getchar();
		if (c == 'x') {
			break;
		}

		if (c != '\n') {
			getchar(); // swallow newline
		}

		switch (c) {
			case 'l': {
				if (teamList.length) {
					showTeamList(fd, &teamList);
				}
				break;
			}
			case 'p': {
				showPlayerScreen(fd);
				break;
			}
			case 't': {
				TeamList tmp = {0};
				addToTeamList(fd, &tmp);
				showTeamList(fd, &tmp);
				break;
			}
			case 'w': {
				// TODO: add error checking around this
				addToTeamList(fd, &teamList);
				break;
			}
			default:
				break;
		}
	}
}
