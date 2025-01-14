#pragma once

#include "player.h"


void addToTeamList(int fd, TeamList *teamList);
void addToClubList(int fd, Club *watchedClub, const Club *club);
PlayerList getPlayersFromTeamList(int fd, const TeamList *teamList, const u8 indexList[5]);
