#pragma once

#define ROLE_COUNT 12

typedef struct {
	char name[16];
	unsigned char positionIndex;
	unsigned char *weights[54];
} Role;
