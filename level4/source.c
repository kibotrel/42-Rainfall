#include <stdio.h>
#include <stdlib.h>

int m;

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

int main(void) {
  n();

  return 0;
}