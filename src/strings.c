#include "strings.h"


u8 getNameLength(const u8 *name1, const u8 *name2) {
	u8 length = 0;
	u8 diacriticCount = 0;
	bool name1Terminated = false;
	bool name2Terminated = false;
	u8 i = 0;

	while (!name1Terminated || !name2Terminated) {
		if (name1[i]) {
			if (!name1Terminated) {
				++length;
				if (name1[i] > 127) {
					++diacriticCount;
				}
			}
		} else {
			name1Terminated = true;
		}

		if (name2[i]) {
			if (!name2Terminated) {
				++length;
				if (name2[i] > 127) {
					++diacriticCount;
				}
			}
		} else {
			name2Terminated = true;
		}

		++i;
	}

	return length - diacriticCount / 2;
}
