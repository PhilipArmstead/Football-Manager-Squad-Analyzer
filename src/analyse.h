#pragma once

#include "types.h"


void printPlayer(
	unsigned long id,
	const u8 ability[3],
	const u8 attributes[56],
	const u8 personality[8],
	const u8 positions[15]
);
float calculateRoleScores(const u8 attributes[54], const u8 weights[54]);
