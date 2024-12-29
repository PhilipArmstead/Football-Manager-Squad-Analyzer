#pragma once

#include "types.h"


#define ROLE_COUNT 12

typedef struct {
	char name[16];
	u8 nameLength;
	u8 positionIndex;
	u8 *weights;
} Role;
