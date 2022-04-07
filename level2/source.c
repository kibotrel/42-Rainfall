#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void p(void) {
  char input[76];
  int memory_address;

  fflush(stdout);
  gets(input);

  if ((memory_address & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n", &memory_address);
    exit(1);
  }

  puts(input);
  strdup(input);
}

int main(void) {
  p();

  return 0;
}