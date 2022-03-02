#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void run(void) {
  fwrite("Good... Wait what?\n", 1, 19, stdout);
  system("/bin/sh");
}

uint8_t main(void) {
  char buffer[64];

  gets(buffer);
  return 0;
}