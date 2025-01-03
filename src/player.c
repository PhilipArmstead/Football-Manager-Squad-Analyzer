#include "player.h"

#include "constants.h"
#include "maths.h"
#include "memory.h"


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

// FIXME: this fails to work when the player is also staff
Player getPlayer(const int fd, const unsigned long address, const Date date) {
	u8 ability[3];
	readFromMemory(fd, address + OFFSET_ABILITY, 3, ability);

	Player player = {
		address,
		getAge(fd, address, date),
		ability[ABILITY_CA],
		ability[ABILITY_PA],
		0
	};
	getPlayerForename(fd, address, player.forename);
	getPlayerSurname(fd, address, player.surname);
	readFromMemory(fd, address + OFFSET_PERSONALITY, 8, player.personality);
	readFromMemory(fd, address + OFFSET_ATTRIBUTES, 54, player.attributes);
	readFromMemory(fd, address + OFFSET_POSITIONS, 15, player.positions);

	player.canDevelopQuickly = player.age <= 23 &&
		player.attributes[ATTRIBUTES_INJURY_PRONENESS] < 70 &&
		player.personality[PERSONALITY_AMBITION] > 10 &&
		player.personality[PERSONALITY_PROFESSIONALISM] > 10 &&
		player.attributes[ATTRIBUTES_DETERMINATION] > 50;

	if (player.age <= 19) {
		player.isHotProspect = player.ca >= 80 + 5 * (player.age - 15);
	} else if (player.age <= 23) {
		player.isHotProspect = player.ca >= 140;
	} else {
		player.isHotProspect = false;
	}

	return player;
}

bool isPlayerValid(const int fd, const unsigned long address) {
	for (u8 i = 0; i < 5; ++i) {
		const u8 attribute = readByte(fd, address + OFFSET_HIDDEN_ATTRIBUTES + i);
		if (!attribute || attribute > 100) {
			return false;
		}
	}
	for (u8 i = 0; i < 8; ++i) {
		const u8 attribute = readByte(fd, address + OFFSET_PERSONALITY + i);
		if (!attribute || attribute > 20) {
			return false;
		}
	}

	return true;
}
