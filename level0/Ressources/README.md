# [OS and File security](./security.md)

> Some infos that could help us exploit this level's binary.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -Wl,-z,norelro -o level0 source.c
```