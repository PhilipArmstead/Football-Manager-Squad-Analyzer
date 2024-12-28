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

	Context ctx = {.fd = 0};
	sprintf(ctx.memoryPath, "/proc/%ld/mem", pid);

	bool autoShow = 0;
	for (unsigned int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0) {
			autoShow = 1;
			break;
		}
	}

	run(&ctx, autoShow);
}
