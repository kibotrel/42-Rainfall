# Level7

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level7
  Segmentation fault (core dumped)
  $> ./level7 "teststring"
  Segmentation fault (core dumped)
  $> ./level7 "teststring" "teststring"
  ~~
```

> Seems like this program needs two arguments to work properly.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). Once again, we'll exploit `strcpy()` but in a more advanced way. We found out that the two given arguments are copied to two set addresses inside the code, then the password file of the next user is read and its content is stored into variable that is printedd in an unreachable function under normal circumstances.

Using a **buffer overflow** we could ask the program to write our second argument to wherever we want by shifting any address by the offset of the first `strcpy()` call.  We find a useless `puts()` that does nothing useful for the program's execution so like a previous level we can use a **GOT Overwrite** to redirect to the wanted function.

For this exploit, we need:

- Address of the `puts()` function (`0x08049928`)
- Offset of first `strcpy()` (**20** bytes)
- Address of the wanted function (`0x080484f4`)

Then all we have to do is shifting the address of `puts()` into the second `strcpy()` destination address and write the wanted function address into it.

```shell
  $> /level7 `python -c 'print "\x90"*20 + "\x08\x04\x99\x28"[::-1]'` `python -c 'print "\x08\x04\x84\xf4"[::-1]'`
  5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
  - 1649074015
```

So next user credentials pair is `level8:5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9`.

Check [here](./source.c) for reproduction source-code of this binary.