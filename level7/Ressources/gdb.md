# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level7
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x08048521 <+0>:     push   %ebp
    0x08048522 <+1>:     mov    %esp,%ebp
    0x08048524 <+3>:     and    $0xfffffff0,%esp
    0x08048527 <+6>:     sub    $0x20,%esp
    0x0804852a <+9>:     movl   $0x8,(%esp)
    0x08048531 <+16>:    call   0x80483f0 <malloc@plt>
    0x08048536 <+21>:    mov    %eax,0x1c(%esp)
    0x0804853a <+25>:    mov    0x1c(%esp),%eax       
    0x0804853e <+29>:    movl   $0x1,(%eax)
    0x08048544 <+35>:    movl   $0x8,(%esp)
    0x0804854b <+42>:    call   0x80483f0 <malloc@plt>
    0x08048550 <+47>:    mov    %eax,%edx
    0x08048552 <+49>:    mov    0x1c(%esp),%eax
    0x08048556 <+53>:    mov    %edx,0x4(%eax)
    0x08048559 <+56>:    movl   $0x8,(%esp)
    0x08048560 <+63>:    call   0x80483f0 <malloc@plt>
    0x08048565 <+68>:    mov    %eax,0x18(%esp)
    0x08048569 <+72>:    mov    0x18(%esp),%eax
    0x0804856d <+76>:    movl   $0x2,(%eax)
    0x08048573 <+82>:    movl   $0x8,(%esp)
    0x0804857a <+89>:    call   0x80483f0 <malloc@plt>
    0x0804857f <+94>:    mov    %eax,%edx
    0x08048581 <+96>:    mov    0x18(%esp),%eax
    0x08048585 <+100>:   mov    %edx,0x4(%eax)
    0x08048588 <+103>:   mov    0xc(%ebp),%eax
    0x0804858b <+106>:   add    $0x4,%eax
    0x0804858e <+109>:   mov    (%eax),%eax
    0x08048590 <+111>:   mov    %eax,%edx
    0x08048592 <+113>:   mov    0x1c(%esp),%eax
    0x08048596 <+117>:   mov    0x4(%eax),%eax
    0x08048599 <+120>:   mov    %edx,0x4(%esp)
    0x0804859d <+124>:   mov    %eax,(%esp)
    0x080485a0 <+127>:   call   0x80483e0 <strcpy@plt>
    0x080485a5 <+132>:   mov    0xc(%ebp),%eax
    0x080485a8 <+135>:   add    $0x8,%eax
    0x080485ab <+138>:   mov    (%eax),%eax
    0x080485ad <+140>:   mov    %eax,%edx
    0x080485af <+142>:   mov    0x18(%esp),%eax
    0x080485b3 <+146>:   mov    0x4(%eax),%eax
    0x080485b6 <+149>:   mov    %edx,0x4(%esp)
    0x080485ba <+153>:   mov    %eax,(%esp)
    0x080485bd <+156>:   call   0x80483e0 <strcpy@plt>
    0x080485c2 <+161>:   mov    $0x80486e9,%edx
    0x080485c7 <+166>:   mov    $0x80486eb,%eax
    0x080485cc <+171>:   mov    %edx,0x4(%esp)
    0x080485d0 <+175>:   mov    %eax,(%esp)
    0x080485d3 <+178>:   call   0x8048430 <fopen@plt>
    0x080485d8 <+183>:   mov    %eax,0x8(%esp)
    0x080485dc <+187>:   movl   $0x44,0x4(%esp)
    0x080485e4 <+195>:   movl   $0x8049960,(%esp)
    0x080485eb <+202>:   call   0x80483c0 <fgets@plt>
    0x080485f0 <+207>:   movl   $0x8048703,(%esp)
    0x080485f7 <+214>:   call   0x8048400 <puts@plt>
    0x080485fc <+219>:   mov    $0x0,%eax
    0x08048601 <+224>:   leave
    0x08048602 <+225>:   ret
  End of assembler dump.
```

> This `main()` calls [`malloc()`](https://man7.org/linux/man-pages/man3/malloc.3.html) multiple times, [`strcpy()`](https://man7.org/linux/man-pages/man3/strcpy.3.html), [`fopen()`](https://man7.org/linux/man-pages/man3/fopen.3.html), [`fgets()`](https://linux.die.net/man/3/fgets) and  [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html).

## Additional functions

Checking the list of available functions within the program gives us...
```gdb
  $> gdb ./level7
  (gdb) info functions
  All defined functions:

  Non-debugging symbols:
    0x0804836c  _init
    0x080483b0  printf
    0x080483b0  printf@plt
    0x080483c0  fgets
    0x080483c0  fgets@plt
    0x080483d0  time
    0x080483d0  time@plt
    0x080483e0  strcpy
    0x080483e0  strcpy@plt
    0x080483f0  malloc
    0x080483f0  malloc@plt
    0x08048400  puts
    0x08048400  puts@plt
    0x08048410  __gmon_start__
    0x08048410  __gmon_start__@plt
    0x08048420  __libc_start_main
    0x08048420  __libc_start_main@plt
    0x08048430  fopen
    0x08048430  fopen@plt
    0x08048440  _start
    0x08048470  __do_global_dtors_aux
    0x080484d0  frame_dummy
    0x080484f4  m
    0x08048521  main
    0x08048610  __libc_csu_init
    0x08048680  __libc_csu_fini
    0x08048682  __i686.get_pc_thunk.bx
    0x08048690  __do_global_ctors_aux
    0x080486bc  _fini
  End of assembler dump.
```

Looks like, `m()` is never called inside the `main()` function. Let's check what it does as well.

```gdb
  $> gdb ./level7
  (gdb) disassemble m
  Dump of assembler code for function m:
    0x080484f4 <+0>:     push   %ebp
    0x080484f5 <+1>:     mov    %esp,%ebp
    0x080484f7 <+3>:     sub    $0x18,%esp
    0x080484fa <+6>:     movl   $0x0,(%esp)
    0x08048501 <+13>:    call   0x80483d0 <time@plt>
    0x08048506 <+18>:    mov    $0x80486e0,%edx
    0x0804850b <+23>:    mov    %eax,0x8(%esp)
    0x0804850f <+27>:    movl   $0x8049960,0x4(%esp)
    0x08048517 <+35>:    mov    %edx,(%esp)
    0x0804851a <+38>:    call   0x80483b0 <printf@plt>
    0x0804851f <+43>:    leave
    0x08048520 <+44>:    ret
  End of assembler dump.
```

> This function loads a global variable located at `0x8049960` called `c` to print its value previously set in `main()` with `fgets()`.

# Data

## Strings

```gdb
  0x080485c7 <+166>:   mov    $0x80486eb,%eax
  
  (gdb) x/s 0x80486eb
  0x80486eb: "/home/user/level8/.pass"
```

The string `/home/user/level8/.pass` is stored at address `0x80486eb` and it is used as input to `fopen()`. It must be the way to get the next password.

## Buffers offset

In this program we can identify two `strcpy()` calls.

```gdb
  ...
  0x080485a0 <+127>:   call   0x80483e0 <strcpy@plt>
  ...
  0x080485bd <+156>:   call   0x80483e0 <strcpy@plt>
  ...
```

Since we know that programs uses `strcpy()` at some point, it is vulnerable to **buffer overflow**.

```shell
  $> ltrace ./level7  `echo -e "import string\nprint ''.join([char * 4 for char in string.ascii_letters])" | python` "teststring"
__libc_start_main(0x8048521, 3, 0xbffff704, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                                                          = 0x0804a008
malloc(8)                                                                                          = 0x0804a018
malloc(8)                                                                                          = 0x0804a028
malloc(8)                                                                                          = 0x0804a038
strcpy(0x0804a018, "aaaabbbbccccddddeeeeffffgggghhhh"...)                                          = 0x0804a018
strcpy(0x66666666, "teststring" <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

> Using a buffer overflow we can overide the destination address of the second call. which is `ffff`, using the same method as previous level, this buffer offset is indeed **20**.