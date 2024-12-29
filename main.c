#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./src/squad-analyser.h"
#include "./src/types.h"

int main(const int argc, const char *argv[]) {
	// Get process ID for game
	FILE *fp = popen("pidof 'Main Thread'", "r");
	char path[64];
	fgets(path, sizeof(path), fp);
	const long pid = strtol(path, NULL, 10);
	fclose(fp);

	// Get file descriptor for process's memory
	char memoryPath[32];
	sprintf(memoryPath, "/proc/%ld/mem", pid);
	Context ctx = {open(memoryPath, O_RDWR), 0};
	if (ctx.fd == -1) {
		printf("Could not open %s\n", memoryPath);
		exit(1);
	}

	// Parse command line args
	bool autoShow = 0;
	for (unsigned int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0) {
			autoShow = 1;
			break;
		}
	}

	run(&ctx, autoShow);
}
