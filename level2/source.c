#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void p(void) {
  uint8_t input[76];
  uint32_t memory_address;

  fflush(stdout);
  gets(input);

  if ((memory_address & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n", &memory_address);
    exit(1);
  }

  puts(input);
  strdup(input);
}

uint8_t main(void) {
  p();
}