# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level2
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x0804853f <+0>:     push   %ebp
    0x08048540 <+1>:     mov    %esp,%ebp
    0x08048542 <+3>:     and    $0xfffffff0,%esp
    0x08048545 <+6>:     call   0x80484d4 <p>
    0x0804854a <+11>:    leave
    0x0804854b <+12>:    ret
  End of assembler dump.
```

> This `main()` does nothing but calling another function `p()`

## Additional functions

As shown in the `main()` function another one is called, let's disasssemble it as well.

```gdb
  (gdb) disassemble p
  Dump of assembler code for function p:
    0x080484d4 <+0>:     push   %ebp
    0x080484d5 <+1>:     mov    %esp,%ebp
    0x080484d7 <+3>:     sub    $0x68,%esp
    0x080484da <+6>:     mov    0x8049860,%eax
    0x080484df <+11>:    mov    %eax,(%esp)
    0x080484e2 <+14>:    call   0x80483b0 <fflush@plt>
    0x080484e7 <+19>:    lea    -0x4c(%ebp),%eax
    0x080484ea <+22>:    mov    %eax,(%esp)
    0x080484ed <+25>:    call   0x80483c0 <gets@plt>
    0x080484f2 <+30>:    mov    0x4(%ebp),%eax
    0x080484f5 <+33>:    mov    %eax,-0xc(%ebp)
    0x080484f8 <+36>:    mov    -0xc(%ebp),%eax
    0x080484fb <+39>:    and    $0xb0000000,%eax
    0x08048500 <+44>:    cmp    $0xb0000000,%eax
    0x08048505 <+49>:    jne    0x8048527 <p+83>
    0x08048507 <+51>:    mov    $0x8048620,%eax
    0x0804850c <+56>:    mov    -0xc(%ebp),%edx
    0x0804850f <+59>:    mov    %edx,0x4(%esp)
    0x08048513 <+63>:    mov    %eax,(%esp)
    0x08048516 <+66>:    call   0x80483a0 <printf@plt>
    0x0804851b <+71>:    movl   $0x1,(%esp)
    0x08048522 <+78>:    call   0x80483d0 <_exit@plt>
    0x08048527 <+83>:    lea    -0x4c(%ebp),%eax
    0x0804852a <+86>:    mov    %eax,(%esp)
    0x0804852d <+89>:    call   0x80483f0 <puts@plt>
    0x08048532 <+94>:    lea    -0x4c(%ebp),%eax
    0x08048535 <+97>:    mov    %eax,(%esp)
    0x08048538 <+100>:   call   0x80483e0 <strdup@plt>
    0x0804853d <+105>:   leave
    0x0804853e <+106>:   ret
  End of assembler dump.
```

> This time we get more information. It uses [`fflush()`](https://man7.org/linux/man-pages/man3/fflush.3.html), [`gets()`](https://linux.die.net/man/3/gets), [`printf()`](https://man7.org/linux/man-pages/man3/printf.3.html), [`exit()`](https://man7.org/linux/man-pages/man3/exit.3.html), [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html) and [`strdup()`](https://man7.org/linux/man-pages/man3/strdup.3.html).

# Data

## Strings

```gdb
  0x08048507 <+51>:    mov    $0x8048620,%eax
  
  (gdb) x/s 0x8048620
  0x8048620: "(%p)\n"
```

The string `(%p)\n` is stored at address `0x8048620`.

```gdb
  (gdb) break main
  Breakpoint 1 at 0x8048542
  
  (gdb) run
  Starting program: /home/user/level2/level2
  
  Breakpoint 1, 0x08048542 in main ()

  (gdb) find &system, +999999999, "/bin/sh"
  0xb7f8cc58
```

> The `find` command allow us to look for specific strings between two addresses.

The string `/bin/sh` is stored at address `0xb7f8cc58`.

## Buffer size

```gdb
  0x080484e7 <+19>:    lea    -0x4c(%ebp),%eax
  
  (gdb) print 0x4c
  $1 = 76
```

 There is a buffer of **76** bytes in `p()`.

## Buffer offset

```gdb
  (gdb) break *0x080484f2
  Breakpoint 1 at 0x80484f2

  (gdb) run
  Starting program: /home/user/level2/level2 
  randomstring

  Breakpoint 1, 0x080484f2 in p ()

  (gdb) x $eax
  0xbffff5dc: 0xb7ec0061

  (gdb) info frame
  Stack level 0, frame at 0xbffff630:
    eip = 0x80484f2 in p; saved eip 0x804854a
    called by frame at 0xbffff640
    Arglist at 0xbffff628, args:
    Locals at 0xbffff628, Previous frame's sp is 0xbffff630
    Saved registers:
      ebp at 0xbffff628, eip at 0xbffff62c

  (gdb) print 0xbffff62c - 0xbffff5dc
  $1 = 80
```

We get the following adresses:

- EIP register: `0xbffff62c`
- Buffer beginning: `0xbffff5dc`

By substraction, we find that the buffer offset is **80**.

## Additional function addresses

```gdb
  (gdb) print &system
  $1 = (<text variable, no debug info> *) 0xb7e6b060 <system>
```

Function `system()` is located at address `0xb7e6b060`.

```gdb
  (gdb) print &exit
  $1 = (<text variable, no debug info> *) 0xb7e5ebe0 <exit>
```

Function `exit()` is located at address `0xb7e5ebe0`.