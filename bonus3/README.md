# Bonus3

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./bonus3
  $> ./bonus3 "teststring"

```

> Looks like this program takes an argument.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). This time the trick is pretty simple... Our input needs to match some pointer value that is being altered by our input fed through `atoi()`. It is ruled by `pointer[atoi(argv[1])] = 0`. So if we send an empty string to parse, it will be `pointer[0] = 0` and since `argv[1]` equals `NULL`, the condition `pointer == argv[1]` is satisfied.

```shell
  $> ./bonus3 ""
  $ cat /home/user/end/.pass
  3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```

So next and last user credentials pair is `end:3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c`.

Check [here](./source.c) for reproduction source-code of this binary.