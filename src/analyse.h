#pragma once

#include "types.h"


void printPlayer(
	const u8 ability[3],
	const u8 attributes[56],
	const u8 personality[8],
	const u8 positions[15],
	const u8 forename[32],
	const u8 surname[32]
);
float calculateRoleScores(const u8 attributes[54], const u8 weights[54]);
