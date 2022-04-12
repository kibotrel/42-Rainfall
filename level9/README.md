# Level9

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level9
  $> ./level9 "teststring"
```

> Nothing is prompted to us in a normal usage.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). This time we're facing a C++ program with some class method using `memcpy()` which is known to be exploitable since no overlaping checks are made.

After a closer look, we can see that this program calls a loaded address in memory **after** the class method call. Using `memcpy` we could overwrite this address to get the program to call `system()` to spawn a shell.

For this exploit, we need:

- Address of the `system()` function (`0xb7d86060`)
- Offset of the `memcpy()` function (**108** bytes)
- Address of `eax` register on method return (`0x0804a00c`)

The main point of this exploit is to replace the address pointed by `eax` to a `system()` call. For this we need to write `system()` address then put **104** junk bytes to overflow and then put the address of `eax` which is where we want to overwrite. Everything after will be parameter to the `system()` call, so let's add `/bin/sh` string to get a shell and the next password!


```shell
  $> ./level9 $(python -c 'print "\xb7\xd8\x60\x60"[::-1] + "\x90" * 104 + "\x08\x04\xa0\x0c"[::-1] + ";/bin/sh"')

  $ cat /home/user/bonus0/.pass
  f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```

So next user credentials pair is `bonus0:f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728`.

Check [here](./source.c) for reproduction source-code of this binary.