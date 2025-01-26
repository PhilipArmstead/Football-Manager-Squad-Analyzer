#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "player.h"
#include "types.h"
#include "watch-list.h"


Club getClubFromPerson(int fd, unsigned long personAddress);

static inline void showClubPrompt(const int fd, const Club *watchedClub) {
	printf("Select up to five squads to print (press enter after each choice):\n");

	u8 index = 1;
	for (u8 j = 0; j < watchedClub->teamList.length; ++j) {
		printf("%d) %s", index, watchedClub->name);

		const Team t = watchedClub->teamList.teams[j];
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

		printf("\n");

		++index;
	}

	printf("Press enter when you're finished adding.\n");

	u8 buffer[6];
	u8 i = 0;
	while (i < 6 && read(STDIN_FILENO, &buffer[i], 1) > 0) {
		if (buffer[i] == '\n') {
			break;
		}
		++i;
	}

	if (!i) {
		return;
	}

	for (u8 j = 0; j < i; ++j) {
		buffer[j] -= 49;
	}
	const PlayerList playerList = getPlayersFromTeamList(fd, &watchedClub->teamList, buffer);
	showPlayerList(fd, playerList);

	// Prompt user again to export list of heal the team
	u8 c = '\n';
	printf("\nFully (h)eal team\n");
	printf("Press anything else to return\n");
	c = getchar();

	const u8 a = c;

	// swallow newline
	while (c != '\n') {
		c = getchar();
	}

	if (a == 'h') {
		for (u8 j = 0; j < playerList.playerCount; ++j) {
			healPlayer(fd, playerList.player[j].playerAddress);
		}
	}

	free(playerList.player);
}
