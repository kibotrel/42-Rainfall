#include <stdio.h>

void run(void) {
  fwrite("Good... Wait what?\n", 1, 19, stdout);
  system("/bin/sh");
}

int main(int argc, char **argv) {
  char buffer[64];

  gets(buffer);
  return 0;
}