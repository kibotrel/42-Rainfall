#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int language;

int greetuser(char *s) {
  char buffer[88];

  if (language == 1) {
    strcpy(buffer, "Hyvää päivää ");
  } else if (language == 2) {
    strcpy(buffer, "Goedemiddag! ");
  } else {
    strcpy(buffer, "Hello ");
  }

  strcat(buffer, s);
  puts(buffer);
}

int main(int argc, char **argv) {
  char *lang;
  char buffer[80];
  char *result;

  if (argc == 3) {
    bzero(buffer, 19);
    strncpy(buffer, argv[1], 40);
    strncpy(buffer + 40, argv[2], 32);

    lang = getenv("LANG");

    if (lang) {
      if(!memcmp(lang, "fi", 2)) {
        language = 1;
      } else if (!memcmp(lang, "nl", 2)) {
        language = 2;
      }
    }

    strncpy(result, buffer, 19);
    greetuser(result);

    return 0;
  } else {
    return 1
  }
}