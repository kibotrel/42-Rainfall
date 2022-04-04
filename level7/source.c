#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char c[80];

void m(void *address) {
  time_t timestamp;

  timestamp = time(0);
  printf("%s - %d\n", c, timestamp);
}

int main(int argc, char** argv) {
  int *buffer1;
  int *buffer2;

  buffer1 = malloc(8);
  buffer1[0] = 1;
  buffer1[1] = malloc(8);

  buffer2 = malloc(8);
  buffer2[0] = 2;
  buffer2[1] = malloc(8);

  strcpy((char*)buffer1[1], argv[1]);
  strcpy((char*)buffer2[1], argv[2]);

  FILE *file = fopen("/home/user/level7/.pass", "r");

  fgets(c, 68, file);
  puts("~~");
  return 0;
}