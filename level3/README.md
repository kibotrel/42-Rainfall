# Level3

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level3
```

> It looks like the programs only prints what you write on standard input.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)).

So next user credentials pair is `level3:`.

Check [here](./source.c) for reproduction source-code of this binary.