#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "maths.h"
#include "memory.h"


Player getPlayer(int fd, unsigned long peronAddress, unsigned long playerAddress, Date date);
bool isPlayerValid(int fd, unsigned long peronAddress, unsigned long playerAddress);
void healPlayer(int fd, unsigned long playerAddress);
void showPlayerList(int fd, PlayerList playerList);

static inline void makeWonderkid(const int fd, const unsigned long personAddress, const unsigned long playerAddress) {
	writeToMemory(fd, personAddress + OFFSET_PERSONALITY, 8, (u8[8]){20, 20, 20, 20, 20, 20, 20, 1});
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_HIDDEN_ATTRIBUTES, 5, (u8[5]){100, 1, 100, 100, 100});
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_BRAVERY, 1, (u8[1]){100});
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_CONSISTENCY, 1, (u8[1]){100});
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_DIRTINESS, 1, (u8[1]){50});

	const u8 potentialAbility = readByte(fd, playerAddress + PLAYER_OFFSET_POTENTIAL_ABILITY);
	if (potentialAbility < 160) {
		const u8 newAbility = 160 + (rand() % 41);
		writeToMemory(fd, playerAddress + PLAYER_OFFSET_POTENTIAL_ABILITY, 1, (u8[1]){newAbility});
	}
}

static inline void destroyPlayer(const int fd, const unsigned long personAddress, const unsigned long playerAddress) {
	writeToMemory(fd, personAddress + OFFSET_PERSONALITY, 8, (u8[8]){1, 1, 1, 1, 1, 1, 1, 20});
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_HIDDEN_ATTRIBUTES, 5, (u8[5]){1, 100, 1, 1, 1});
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_BRAVERY, 1, (u8[1]){1});
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_CONSISTENCY, 1, (u8[1]){1});

	const u8 currentAbility = readByte(fd, playerAddress + PLAYER_OFFSET_ABILITY);
	writeToMemory(fd, playerAddress + PLAYER_OFFSET_POTENTIAL_ABILITY, 1, (u8[1]){currentAbility});
}

static inline void printPlayerPositions(const Player *p) {
	bool canPlaySomewhereElse = false;
	if (p->positions[0] > 9) {
		printf("GK");
		canPlaySomewhereElse = true;
	}
	if (p->positions[1] > 9) {
		if (canPlaySomewhereElse) {
			printf(", ");
		}
		printf("SW");
		canPlaySomewhereElse = true;
	}
	bool canPlayOnThisRow = false;
	if (p->positions[2] > 9) {
		if (canPlaySomewhereElse) {
			printf(", ");
		}
		printf("DL");
		canPlaySomewhereElse = true;
		canPlayOnThisRow = true;
	}
	if (p->positions[3] > 9) {
		if (canPlayOnThisRow) {
			printf("/C");
		} else {
			if (canPlaySomewhereElse) {
				printf(", ");
			}
			printf("DC");
		}
		canPlaySomewhereElse = true;
		canPlayOnThisRow = true;
	}
	if (p->positions[4] > 9) {
		if (canPlayOnThisRow) {
			printf("/R");
		} else {
			if (canPlaySomewhereElse) {
				printf(", ");
			}
			printf("DR");
		}
		canPlaySomewhereElse = true;
	}
	canPlayOnThisRow = false;
	if (p->positions[13] > 9) {
		if (canPlaySomewhereElse) {
			printf(", ");
		}
		printf("WBL");
		canPlaySomewhereElse = true;
		canPlayOnThisRow = true;
	}
	if (p->positions[14] > 9) {
		if (canPlayOnThisRow) {
			printf("/R");
		} else {
			if (canPlaySomewhereElse) {
				printf(", ");
			}
			printf("WBR");
		}
		canPlaySomewhereElse = true;
	}
	if (p->positions[5] > 9) {
		if (canPlaySomewhereElse) {
			printf(", ");
		}
		printf("DM");
		canPlaySomewhereElse = true;
	}
	canPlayOnThisRow = false;
	if (p->positions[6] > 9) {
		if (canPlaySomewhereElse) {
			printf(", ");
		}
		printf("ML");
		canPlaySomewhereElse = true;
		canPlayOnThisRow = true;
	}
	if (p->positions[7] > 9) {
		if (canPlayOnThisRow) {
			printf("/C");
		} else {
			if (canPlaySomewhereElse) {
				printf(", ");
			}
			printf("MC");
		}
		canPlaySomewhereElse = true;
		canPlayOnThisRow = true;
	}
	if (p->positions[8] > 9) {
		if (canPlayOnThisRow) {
			printf("/R");
		} else {
			if (canPlaySomewhereElse) {
				printf(", ");
			}
			printf("MR");
		}
		canPlaySomewhereElse = true;
	}
	canPlayOnThisRow = false;
	if (p->positions[9] > 9) {
		if (canPlaySomewhereElse) {
			printf(", ");
		}
		printf("AML");
		canPlaySomewhereElse = true;
		canPlayOnThisRow = true;
	}
	if (p->positions[10] > 9) {
		if (canPlayOnThisRow) {
			printf("/C");
		} else {
			if (canPlaySomewhereElse) {
				printf(", ");
			}
			printf("AMC");
		}
		canPlaySomewhereElse = true;
		canPlayOnThisRow = true;
	}
	if (p->positions[11] > 9) {
		if (canPlayOnThisRow) {
			printf("/R");
		} else {
			if (canPlaySomewhereElse) {
				printf(", ");
			}
			printf("AMR");
		}
		canPlaySomewhereElse = true;
	}
	if (p->positions[12] > 9) {
		if (canPlaySomewhereElse) {
			printf(", ");
		}
		printf("ST");
	}
}

static inline u8 getAge(const int fd, const unsigned long address, const Date date) {
	u8 bytes[4];
	readFromMemory(fd, address + OFFSET_DOB, 4, bytes);
	const u8 yearBytes[2] = {bytes[2], bytes[3]};
	const u16 yearOfBirth = hexBytesToInt(yearBytes, 2);
	const u16 dayOfBirth = hexBytesToInt(bytes, 2);

	u8 age = date.year - yearOfBirth;
	if (date.days < dayOfBirth) {
		--age;
	}

	return age;
}
