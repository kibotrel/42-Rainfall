#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void o(void) {
  system("/bin/sh");
  _exit(1);
}

void n(void) {
  char input[520];
  
  fgets(input, 512, stdin);
  printf(input);
  exit(1);
}

uint8_t main(void) {
  n();
}