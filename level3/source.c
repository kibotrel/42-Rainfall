#include <stdio.h>
#include <stdlib.h>

int m;

void v(void) {
  char input[520];

  fgets(input, 512, stdin);
  printf(input);

  if (m == 64) {
    fwrite("Wait what?!\n", 1, 12, stdout);
    system("/bin/sh");
  }
}

int main(void) {
  v();

  return 0;
}