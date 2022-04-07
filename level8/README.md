# Level8

> For introductory information on this operating system and binary securities, check [here](./Ressources/README.md).

Let's see what does the binary do.

```shell
  $> ./level8
  (nil), (nil)
  "teststring"
  (nil), (nil)
```

> Looks like two pointers are being shown to us and the program wants us to input something particular.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./Ressources/gdb.md)). After analysis, we understand that there are two global variables which are printed each time we input something.The first is called `auth` and the other one is `service`. On top of that, depending on our input, some logic is triggered if our input match a "command" name.

- `auth ` allocates **4** bytes for the `auth` variable then and copies the rest if the input within the variable if its length is less thant **32** bytes.
- `reset` will `free()` the `auth` variable.
- `service` will use `strdup()` on the rest of the input an stores it inside `service`.
- `login` will either prompt us a message or give us a shell depending on a simple condition: starting from the address of `auth` we need the following 32nd byte being set to something.

Now that we know how to get the next password (via a shell). We need to find a way to trigger it and this is where the printed pointers come handy. Since we know the address of `auth` and that `auth` and `service` are close in memory, all we have to do is to make sure that **32** bytes after `auth`, there is something meaning we are in the `service` memory space before typing `login`.

```shell
  $> ./level8
  (nil), (nil)
  auth
  0x804a008, (nil)
  service 0123456789abcdef
  0x804a008, 0x804a018
  login
  $ cat /home/user/level9/.pass
  c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a 
```

> Do not forget to input `auth` with a space at the end, otherwise it won't work. The `service` command also work with anything as the last character since the comparison only checks for the firsts **6** bytes.

So next user credentials pair is `level9:c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a`.

Check [here](./source.c) for reproduction source-code of this binary.