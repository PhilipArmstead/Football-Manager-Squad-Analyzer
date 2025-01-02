#pragma once

#include "types.h"


void printPlayer(const Player *player, const u8 attributes[56], const u8 personality[8], const u8 positions[15]);
float calculateRoleScores(const u8 attributes[54], const u8 weights[54]);
void showTeamList(int fd, const TeamList *teamList);
void showPlayerScreen(int fd);
