#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
  if (atoi(argv[1]) == 423) {
    char *args[2] = { strdup("/bin/sh"), 0 };
    gid_t gid = getegid();
    uid_t uid = geteuid();

    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);
    execv("/bin/sh", args);

  } else {
    fwrite("No !\n", 1, 5, stderr);
  }

  return 0;
}