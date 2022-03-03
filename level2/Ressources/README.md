# Commands

## OS and File security

Let's run [`checksec`](https://www.systutorials.com/docs/linux/man/7-checksec/) on the binary we have.

```shell
  $> checksec --file level2
  RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
  No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level2
```

> Same security as `level1`.

## [GDB analysis](./gdb.md)

> Useful data on the binary itself.

## Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
  $> gcc -Wl,-z,norelro -fno-stack-protector -z execstack -o level2 source.c
```