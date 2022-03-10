#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t m;

void p(char *string) {
  printf(string);
}

void n(void) {
  char input[520];

  fgets(input, 512, stdin);
  p(input);

  if (m == 16930116) {
    system("/bin/cat /home/user/level5/.pass");
  }
}

uint8_t main(void) {
  n();
}