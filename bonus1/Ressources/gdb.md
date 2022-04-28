# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./bonus1
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x08048424 <+0>:     push   %ebp
    0x08048425 <+1>:     mov    %esp,%ebp
    0x08048427 <+3>:     and    $0xfffffff0,%esp
    0x0804842a <+6>:     sub    $0x40,%esp
    0x0804842d <+9>:     mov    0xc(%ebp),%eax
    0x08048430 <+12>:    add    $0x4,%eax
    0x08048433 <+15>:    mov    (%eax),%eax
    0x08048435 <+17>:    mov    %eax,(%esp)
    0x08048438 <+20>:    call   0x8048360 <atoi@plt>
    0x0804843d <+25>:    mov    %eax,0x3c(%esp)
    0x08048441 <+29>:    cmpl   $0x9,0x3c(%esp)
    0x08048446 <+34>:    jle    0x804844f <main+43>
    0x08048448 <+36>:    mov    $0x1,%eax
    0x0804844d <+41>:    jmp    0x80484a3 <main+127>
    0x0804844f <+43>:    mov    0x3c(%esp),%eax
    0x08048453 <+47>:    lea    0x0(,%eax,4),%ecx
    0x0804845a <+54>:    mov    0xc(%ebp),%eax
    0x0804845d <+57>:    add    $0x8,%eax
    0x08048460 <+60>:    mov    (%eax),%eax
    0x08048462 <+62>:    mov    %eax,%edx
    0x08048464 <+64>:    lea    0x14(%esp),%eax
    0x08048468 <+68>:    mov    %ecx,0x8(%esp)
    0x0804846c <+72>:    mov    %edx,0x4(%esp)
    0x08048470 <+76>:    mov    %eax,(%esp)
    0x08048473 <+79>:    call   0x8048320 <memcpy@plt>
    0x08048478 <+84>:    cmpl   $0x574f4c46,0x3c(%esp)
    0x08048480 <+92>:    jne    0x804849e <main+122>
    0x08048482 <+94>:    movl   $0x0,0x8(%esp)
    0x0804848a <+102>:   movl   $0x8048580,0x4(%esp)
    0x08048492 <+110>:   movl   $0x8048583,(%esp)
    0x08048499 <+117>:   call   0x8048350 <execl@plt>
    0x0804849e <+122>:   mov    $0x0,%eax
    0x080484a3 <+127>:   leave  
    0x080484a4 <+128>:   ret 
  End of assembler dump.
```

> It uses [`atoi()`](https://man7.org/linux/man-pages/man3/atoi.3.html), [`memcpy()`](https://man7.org/linux/man-pages/man3/memcpy.3.html) and [`execl()`](https://linux.die.net/man/3/execl).

Looks like starting from address `0x08048482`, the instruction list is meant to spawn a shell.

# Data

## Strings

```gdb
  0x0804848a <+102>:   movl   $0x8048580,0x4(%esp)

  (gdb) x/s 0x8048580
  0x8048580: "sh"
```

The string `sh` is located at address `0x08048580`.

```gdb
  0x08048492 <+110>:   movl   $0x8048583,(%esp)

  (gdb) x/s 0x8048583
  0x8048583: "/bin/sh"
```

The string `/bin/sh` is located at address `0x08048583`.

## Buffer offset

Since we need to exploit memcpy through `atoi()` underflow, let's compute the offset of its buffer.
For this test, any large enough `atoi()` input should work. In our case **-1073741792** gives a copy of **192** bytes.

```gdb
  $> gdb ./bonus1

  (gdb) run -1073741792 $(echo -e "import string\nprint ''.join([char * 4 for char in string.ascii_letters])" | python)
  Starting program: /home/user/bonus1/bonus1 -1073741792 $(echo -e "import string\nprint ''.join([char * 4 for char in string.ascii_letters])" | python)

  Program received signal SIGSEGV, Segmentation fault.
  0x6f6f6f6f in ?? ()
```

> `0x6f6f6f6f` represent `oooo`. It means that buffer ends on `nnnn` which is 14th letter in our sequence, so the offset must be **14 * 4** = **56** bytes.
