#pragma once

#include "player.h"


static inline void removeFromClubList(ClubList *clubList, const u8 index) {
	for (u8 i = index; i < clubList->length - 1; ++i) {
		clubList->clubs[i] = clubList->clubs[i + 1];
	}
	--clubList->length;
}

void addToTeamList(int fd, TeamList *teamList);
void addToClubList(int fd, ClubList *clubList, Club club);
PlayerList getPlayersFromTeamList(int fd, const TeamList *teamList);
