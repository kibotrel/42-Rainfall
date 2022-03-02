#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#define _GNU_SOURCE

uint8_t main(uint32_t argc, uint8_t **argv) {
  if (atoi(argv[1]) == 423) {
    char *const args[] = { strdup("/bin/sh"), NULL };
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