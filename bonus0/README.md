# Bonus0

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./bonus0
    -
  
    -
  
  $> ./bonus0
    - 
  teststring
    -
  salut
  teststring salut
```

> Seems like this program want us to input two string before printing them out.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). After a closer look, we can see that this program is using `strcat()` known for its overflow overruns.

For this exploit, we need:

- Tinkering a [Shellcode]() and get its address
- Find the offset of one buffer to inject it

`WIP`


```shell
  $> ./bonus0

  $ cat /home/user/bonus1/.pass
```

So next user credentials pair is `bonus1:`.

Check [here](./source.c) for reproduction source-code of this binary.