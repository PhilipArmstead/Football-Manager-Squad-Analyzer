#pragma once

#include "types.h"


void printPlayer(const Player *p);
float calculateRoleScores(const u8 attributes[54], const u8 weights[54]);
void showTeamList(int fd, const TeamList *teamList, const u8 indexList[5]);
void showPlayerScreen(int fd, Club *watchedClub);
