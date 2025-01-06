#pragma once

#include "player.h"


static inline void removeFromTeamList(TeamList *teamList, const u8 index) {
	for (u8 i = index; i < teamList->length - 1; ++i) {
		teamList->teams[i].address = teamList->teams[i + 1].address;
	}
	--teamList->length;
}

void addToTeamList(int fd, TeamList *teamList);
PlayerList getPlayersFromTeamList(int fd, const TeamList *teamList);
