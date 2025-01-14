#pragma once

#include "types.h"


static inline int power(const int base, int exp) {
	int result = 1;
	while (exp--) result *= base;
	return result;
}

static inline long hexBytesToInt(const u8 *bytes, const char length) {
	long value = 0;
	for (short i = 0; i < length; ++i) {
		value += (long)(bytes[i] * power(256, i));
	}
	return value;
}
