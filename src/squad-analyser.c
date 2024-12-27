#include <stdio.h>

#include "squad-analyser.h"
#include "analyse.h"
#include "maths.h"
#include "memory.h"


void showPlayerScreen(const int fileDescriptorMemory, const long memoryLocationAttributes) {
	printPlayer(fileDescriptorMemory, memoryLocationAttributes);
	printf("\n");
}

void run(const int fileDescriptorMemory, const bool autoShow) {
	const long pointerAttributes = 0x15DCD9415;
	unsigned char bytes[4];
	readFromMemory(fileDescriptorMemory, pointerAttributes, 4, bytes);
	const long memoryLocationAttributes = hexBytesToInt(bytes, 4);

	if (autoShow) {
		showPlayerScreen(fileDescriptorMemory, memoryLocationAttributes);
	}

	char input = '\0';
	do {
		if (input == 'x') {
			break;
		}

		printf("\nMake a choice: ");

		if (input == 's') {
			showPlayerScreen(fileDescriptorMemory, memoryLocationAttributes);
		}
	} while (fgets(&input, 2, stdin));
}
