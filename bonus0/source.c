void p(char *buffer1, char *buffer2) {
  char buffer3[4104];

  puts(buffer2);
  read(0, buffer3, 4096);
  *strchr(buffer3, '\n') = 0;
  strncpy(buffer1, buffer3, 20);
}

void pp(char *buffer) {
  char buffer1[20];
  char buffer2[20];

  p(buffer1, " - ");
  p(buffer2, " - ");
  strcpy(buffer, buffer1);
  buffer[strlen(buffer)] = ' ';
  strcat(buffer, buffer2);
}

int main(void) {
  char buffer[54];

  pp(buffer);
  puts(buffer);

  return 0;
}