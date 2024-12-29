#pragma once

#include "types.h"


void printPlayer(const Context *ctx, unsigned long attributeBase);
float calculateRoleScores(const u8 attributes[54], const u8 weights[54]);
