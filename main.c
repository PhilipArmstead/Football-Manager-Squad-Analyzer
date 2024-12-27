#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printPlayer(const int fd, const long address);

static inline long hexBytesToInt(const unsigned char *bytes, const char length) {
  long value = 0;
  for (short i = 0; i < length; ++i) {
    value += (long)(bytes[i] * pow(256, i));
  }
  return value;
}

static inline void resetAttributes(const int fd, const long address) {
  const char max = 100;
  const char min = 1;

  lseek(fd, address - 0x61, SEEK_SET);
  for (short i = 0; i < 41; ++i) {
    write (fd, &max, 1);
  }

  write (fd, &min, 1);
  for (short i = 0; i < 6; ++i) {
    write (fd, &max, 1);
  }
  write (fd, &min, 1);
  for (short i = 0; i < 4; ++i) {
    write (fd, &max, 1);
  }

  lseek(fd, address + 0x78, SEEK_SET);
  const char twenty = 20;
  for (short i = 0; i < 8; ++i) {
    write (fd, &twenty, 1);
  }
}

static inline void readFromMemory(const int fd, const long address, const int length, unsigned char *bytes) {
  lseek(fd, address, SEEK_SET);
  read(fd, bytes, length);
}

static inline void writeToMemory(const int fd, const long address, const int length, unsigned char *bytes) {
  lseek(fd, address, SEEK_SET);
  write(fd, bytes, length);
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
  readFromMemory(fileDescriptorMemory, pointerAttributes, 4, bytes);
  const long memoryLocationAttributes = hexBytesToInt(bytes, 4);

  // resetAttributes(fileDescriptorMemory, memoryLocationAttributes);

  // while (1) {
    // printf("\n");
    // signed short input;

    // printf("Offset from attribute base: ");
    // scanf("%d", &input);
    // signed short offset = input;
    // printf("New value (0-255): ");
    // scanf("%d", &input);
    // unsigned char value = input;

    // writeToMemory(fileDescriptorMemory, memoryLocationAttributes + offset, 1, &value);
  // }

  printPlayer(fileDescriptorMemory, memoryLocationAttributes);

  free(proc_mem);
}

static inline void padLeft(const unsigned char byte) {if (byte < 10) {
  printf(" ");
}
  printf("%d", byte);
}

void printPlayer(const int fd, const long address) {
  unsigned char bytes[8];
  readFromMemory(fd, address + 0x0C, 4, bytes);

  printf(".------------------------------------------.");
  printf("\n| %ld (Gk, DL/R, ST)\n", hexBytesToInt(bytes, 4));

  readFromMemory(fd, address - 0x78, 4, bytes);
  printf("| Ability: %d/%d\n", bytes[0], bytes[2]);
  printf(".------------------------------------------.");
  printf("------------------------------------------.\n");

  readFromMemory(fd, address + 0x78, 8, bytes);
  unsigned char hidden[9];
  readFromMemory(fd, address - 0x38, 9, hidden);
  unsigned char byte;
  readFromMemory(fd, address - 0x2E, 1, &byte);

  printf("| Adaptability:  ");
  padLeft(bytes[0]);
  printf("  Professionalism:  ");
  padLeft(bytes[4]);
  printf("  | Consistency:    ");
  padLeft(hidden[3]);
  printf("  Injury proneness:  ");
  padLeft(hidden[7]);
  printf("\n| Ambition:      ");
  padLeft(bytes[1]);
  printf("  Sportsmanship:    ");
  padLeft(bytes[5]);
  printf("  | Determination:  ");
  padLeft(byte);
  printf("  Versatility:       ");
  padLeft(hidden[8]);
  printf("\n| Loyalty:       ");
  padLeft(bytes[2]);
  printf("  Temperament:      ");
  padLeft(bytes[6]);
  printf("  | Dirtiness:      ");
  padLeft(hidden[0]);
  printf("\n| Pressure:      ");
  padLeft(bytes[3]);
  printf("  Controversy:      ");
  padLeft(bytes[7]);
  printf("  | Imp. Matches:   ");
  padLeft(hidden[6]);
  // Age
  // Positions

  printf("\n");
}
