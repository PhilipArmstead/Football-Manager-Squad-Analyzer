#pragma once

#include <analyse.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "types.h"


Club getClubFromPerson(int fd, unsigned long personAddress);

static inline void showClubPrompt(const int fd, const ClubList *clubList) {
	printf("Select up to five squads to print (press enter after each choice):\n");

	u8 teamCount = 0;
	const Team *cachedTeams[80];
	TeamList selectedTeams = {0};

	while (true) {
		u8 index = 1;
		for (u8 i = 0; i < clubList->length; ++i) {
			const Club c = clubList->clubs[i];
			for (u8 j = 0; j < c.teamList.length; ++j) {
				printf("%d) %s", index, c.name);

				const Team t = c.teamList.teams[j];
				switch (t.teamType) {
					case 1:
						printf(" reserves");
						break;
					case 12:
						printf(" U18s");
						break;
					case 22:
						printf(" Youth Candidates");
						break;
					default:
						break;
				}

				for (u8 k = 0; k < selectedTeams.length; ++k) {
					if (selectedTeams.teams[k].address == t.address) {
						printf(" (selected)");
					}
				}

				printf("\n");
				cachedTeams[teamCount++] = &c.teamList.teams[j];
				++index;
			}
		}

		printf("Press enter when you're finished adding.\n");

		char buffer[10];
		u8 i = 0;
		while (i < 10 && read(STDIN_FILENO, &buffer[i], 1) > 0) {
			if (buffer[i] == '\n') {
				break;
			}
			++i;
		}

		if (!i) {
			break;
		}

		const u8 v = strtol(buffer, NULL, 10) - 1;
		if (v > teamCount) {
			break;
		}

		bool existed = false;
		for (u8 j = 0; j < selectedTeams.length; ++j) {
			if (selectedTeams.teams[j].address == cachedTeams[v]->address) {
				for (u8 k = j; k < selectedTeams.length - 1; ++k) {
					selectedTeams.teams[k] = selectedTeams.teams[k + 1];
				}
				--selectedTeams.length;
				existed = true;
				break;
			}
		}

		if (!existed && selectedTeams.length < 5) {
			selectedTeams.teams[selectedTeams.length++] = *cachedTeams[v];
		}
	}

	showTeamList(fd, &selectedTeams);
}
