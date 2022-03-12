#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef void(*function_pointer)(void);

void n(void) {
	system("/bin/cat /home/user/level7/.pass");
}

void m(void) {
	puts("Nope");
}

uint8_t main(int argc, char **argv) {
  uint8_t *input = (uint8_t*)malloc(64);
  function_pointer *f = (function_pointer*)malloc(4);
  *f = m;

  strcpy(input, argv[1]);
  (*f)();
}