#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t m;

void v(void) {
  char input[520];

  fgets(input, 512, stdin);
  printf(input);

  if (m == 64) {
    fwrite("Wait what?!\n", 1, 12, stdout);
    system("/bin/sh");
  }
}

uint8_t main(void) {
  v();
}