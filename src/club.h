#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "player.h"
#include "sort.h"
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

	bool isRunning = true;
	while (isRunning) {
		showPlayerList(fd, playerList);

		// Prompt user again to export list of heal the team
		u8 c = '\n';
		printf("\nFully (h)eal team\n");
		printf("(s)ort players\n");
		printf("Press anything else to return\n");
		c = getchar();

		const u8 a = c;

		// swallow newline
		while (c != '\n') {
			c = getchar();
		}

		switch (a) {
			case 'h': {
				for (u8 j = 0; j < playerList.playerCount; ++j) {
					healPlayer(fd, playerList.player[j].playerAddress);
				}
				isRunning = false;
				break;
			}
			case 's': {
				printf("\nSelect sort criteria:\n");
				printf("1: age\n");
				printf("2: current ability\n");
				printf("3: potential ability\n");
				printf("4-15: roles\n");

				u8 buf[3];
				u8 j = 0;
				while (j < 3 && read(STDIN_FILENO, &buf[j], 1) > 0) {
					if (buf[j] == '\n') {
						break;
					}
					++j;
				}

				if (!j) {
					return;
				}

				bool (*compare)(Player, Player);
				switch (strtol(buf, NULL, 10)) {
					case 1:
						compare = sortByAge;
						break;
					case 2:
						compare = sortByCurrentAbility;
						break;
					case 3:
						compare = sortByPotentialAbility;
						break;
					case 4:
						compare = sortByRoleGoalkeeper;
						break;
					case 5:
						compare = sortByRoleDefenderLeft;
						break;
					case 6:
						compare = sortByRoleDefenderCentre;
						break;
					case 7:
						compare = sortByRoleDefenderRight;
						break;
					case 8:
						compare = sortByRoleDefensiveMidfielder;
						break;
					case 9:
						compare = sortByRoleAttackingMidfielderLeftAttack;
						break;
					case 10:
						compare = sortByRoleAttackingMidfielderLeftSupport;
						break;
					case 11:
						compare = sortByRoleAttackingMidfielderCentre;
						break;
					case 12:
						compare = sortByRoleAttackingMidfielderRightAttack;
						break;
					case 13:
						compare = sortByRoleAttackingMidfielderRightSupport;
						break;
					case 14:
						compare = sortByRoleStrikerAttackingForward;
						break;
					case 15:
						compare = sortByRoleStrikerPressingForward;
						break;
					default:
						compare = sortByAge;
				}
				quickSort(playerList.player, 0, playerList.playerCount - 1, compare);
				break;
			}
			default: {
				isRunning = false;
			}
		}
	}

	free(playerList.player);
}
