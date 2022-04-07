#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class N {
  public:

  char buffer[104];
  int value;

  N(int value) {
    this->value = value;
  }

  int operator+(N number) {
    return this->value + number.value;
  }

  int operator-(N number) {
    return this->value - number.value;
  }

  void setAnnotation(char *str) {
    memcpy(this->buffer, str, strlen(str));
  }
};

int main(int argc, char **argv) {
  if (argc < 2) {
    exit(1);
  }

  N first = N(5);
  N second = N(6);
  
  first.setAnnotation(argv[1]);
  return first + second;
}
