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
  int *buffer1 = malloc(8);
  int *junk = malloc(8);
  int *buffer2 = malloc(8);

  *buffer1 = 1;
  buffer1[1] = (int*)junk;
  *buffer2 = 2;
  buffer2[1] = (int*)junk;
  strcpy((char*)buffer1[1], argv[1]);
  strcpy((char*)buffer2[1], argv[2]);

  FILE *file = fopen("/home/user/level8/.pass", "r");

  fgets(c, 68, file);
  puts("~~");
  return 0;
}