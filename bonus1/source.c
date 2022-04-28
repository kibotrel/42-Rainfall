#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char buffer[40];
  int size = atoi(argv[1]);

  if (size < 10) {
    memcpy(buffer, argv[2], size * 4);
    
    if (size == 1464814662) {
      execl("/bin/sh", "sh", 0);
    }

    return 1;
  }

  return 0;
}