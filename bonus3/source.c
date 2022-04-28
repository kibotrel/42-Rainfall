#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  FILE *stream;
  char buffer1[24];
  char buffer2[66];
  int input;

  stream = fopen("/home/user/end/.pass","r");
  bzero(buffer1, 33);

  if (argc == 2 && stream) {
    fread(buffer1, 1, 66, stream);
    input = atoi(argv[1]);
    buffer1[input] = 0;
    fread(buffer2, 1, 65, stream);
    fclose(stream);
    
    if (!strcmp(buffer2, argv[1])) {
      execl("/bin/sh", "sh", 0);
    } else {
      puts(buffer2);
    }

    return 0;
  }

  return 0xffffffff;
}