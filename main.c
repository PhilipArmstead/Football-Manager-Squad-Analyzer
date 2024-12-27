#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./src/squad-analyser.h"
#include "./src/types.h"

int main(const int argc, const char *argv[]) {
	FILE *fp = popen("pidof 'Main Thread'", "r");
	char path[64];
	fgets(path, sizeof(path), fp);
	const long pid = strtol(path, NULL, 10);
	fclose(fp);

	char *pathToProcessMemory = malloc(32);
	sprintf(pathToProcessMemory, "/proc/%ld/mem", pid);

	const int fileDescriptorMemory = open(pathToProcessMemory, O_RDWR);
	if (fileDescriptorMemory == -1) {
		printf("Could not open %s\n", pathToProcessMemory);
		exit(1);
	}
	free(pathToProcessMemory);

	bool autoShow = 0;
	for (unsigned int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0) {
			autoShow = 1;
			break;
		}
	}

	run(fileDescriptorMemory, autoShow);
}
