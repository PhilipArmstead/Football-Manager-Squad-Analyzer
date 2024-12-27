#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static inline long hexBytesToInt(const unsigned char *bytes,
                                 const char length) {
  long value = 0;
  for (short i = 0; i < length; ++i) {
    value += (long)(bytes[i] * pow(256, i));
  }
  return value;
}

int main() {
  /**
  For scanning
          For each line in /proc/id/maps...
          e.g.
          00010000-00012000 r--s 00000000 00:29 824407
          build array of start/end addresses (10000, 12000)
  */

  char path[64];

  FILE *fp = popen("pidof 'Main Thread'", "r");
  if (fp == NULL) {
    printf("Failed to run command\n");
    exit(1);
  }

  fgets(path, sizeof(path), fp);
  const long pid = strtol(path, NULL, 10);
  fclose(fp);

  char *proc_mem = malloc(32);
  sprintf(proc_mem, "/proc/%ld/mem", pid);

  const int fileDescriptorMemory = open(proc_mem, O_RDWR);
  if (fileDescriptorMemory == -1) {
    printf("Could not open %s\n", proc_mem);
    exit(1);
  }

  unsigned char bytes[4];
  const long pointerAttributes = 0x15DCD9415;
  lseek(fileDescriptorMemory, pointerAttributes, SEEK_SET);
  read(fileDescriptorMemory, &bytes, 4);
  const long memoryLocationAttributes = hexBytesToInt(bytes, 4);
  lseek(fileDescriptorMemory, memoryLocationAttributes - 0x76, SEEK_SET);
  read(fileDescriptorMemory, &bytes, 1);

  printf("  %d\n", bytes[0]);

  // byte = 200;
  // lseek(fileDescriptorMemory, addr, SEEK_SET);
  // write (fileDescriptorMemory, &byte, len     );
  // if (write (fileDescriptorMemory, byte , len     ) == -1) {
  //    printf("Error while writing\n");
  //    exit(1);
  // }

  free(proc_mem);
}
