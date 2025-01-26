#pragma once

#include "types.h"


typedef struct {
	char name[16];
	u8 nameLength;
	u8 positionIndex;
	u8 *weights;
} Role;
