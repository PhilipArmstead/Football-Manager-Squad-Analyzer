#pragma once

#include "constants.h"
#include "maths.h"
#include "memory.h"


u8 getAge(int fd, unsigned long address, Date date);


static inline void getPlayerName(const int fd, u8 pointer[4], u8 str[32]) {
	unsigned long a = hexBytesToInt(pointer, 4);
	readFromMemory(fd, a, 4, pointer);
	a = hexBytesToInt(pointer, 4);
	readFromMemory(fd, a + 4, 32, str);
}

static inline void getPlayerForename(const int fd, const unsigned long attributeBase, u8 str[32]) {
	u8 pointer[4];
	readFromMemory(fd, attributeBase + OFFSET_FORENAME, 4, pointer);
	getPlayerName(fd, pointer, str);
}

static inline void getPlayerSurname(const int fd, const unsigned long attributeBase, u8 str[32]) {
	u8 pointer[4];
	readFromMemory(fd, attributeBase + OFFSET_SURNAME, 4, pointer);
	getPlayerName(fd, pointer, str);
}


static inline bool getIsHotProspect(const u8 age, const u8 currentAbility) {
	if (age <= 19) {
		return currentAbility >= 80 + 5 * (age - 15);
	}
	if (age <= 23) {
		return currentAbility >= 140;
	}
	return false;
}

static inline bool getCanDevelopQuickly(
	const u8 age,
	const u8 injuryProneness,
	const u8 ambition,
	const u8 professionalism,
	const u8 determination
) {
	return age <= 23 &&
		injuryProneness < 70 &&
		ambition > 10 &&
		professionalism > 10 &&
		determination > 50;
}
