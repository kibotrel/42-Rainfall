# Level0

> For introductory information on this operating system and binary securities, check [here](./Ressources/security.md).

Let's see what does the binary do.

```shell
  $> ./level0
  Segmentation fault (core dumped)
  $> ./level0 "test"
  No !
```

> Seems like this program want us to input an argument.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). Thanks to it we find that **423** should be given to the program to get a running shell as `level1`. All we have to do then is to navigate through the filesystem to get the `level1` user password.

```shell
  $> ./level0 423
  $ cat /home/user/level1/.pass
  1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```

> We can see that our prompt changed to `$` meaning a new shell spawned.

So next user credentials pair is `level1:1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a`.

Check [here](./source.c) for reproduction source-code of this binary.