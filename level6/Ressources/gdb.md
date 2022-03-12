# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level6
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x0804847c <+0>:     push   %ebp
    0x0804847d <+1>:     mov    %esp,%ebp
    0x0804847f <+3>:     and    $0xfffffff0,%esp       
    0x08048482 <+6>:     sub    $0x20,%esp
    0x08048485 <+9>:     movl   $0x40,(%esp)
    0x0804848c <+16>:    call   0x8048350 <malloc@plt> 
    0x08048491 <+21>:    mov    %eax,0x1c(%esp)        
    0x08048495 <+25>:    movl   $0x4,(%esp)
    0x0804849c <+32>:    call   0x8048350 <malloc@plt> 
    0x080484a1 <+37>:    mov    %eax,0x18(%esp)        
    0x080484a5 <+41>:    mov    $0x8048468,%edx        
    0x080484aa <+46>:    mov    0x18(%esp),%eax     
    0x080484ae <+50>:    mov    %edx,(%eax)
    0x080484b0 <+52>:    mov    0xc(%ebp),%eax
    0x080484b3 <+55>:    add    $0x4,%eax
    0x080484b6 <+58>:    mov    (%eax),%eax
    0x080484b8 <+60>:    mov    %eax,%edx
    0x080484ba <+62>:    mov    0x1c(%esp),%eax        
    0x080484be <+66>:    mov    %edx,0x4(%esp)
    0x080484c2 <+70>:    mov    %eax,(%esp)
    0x080484c5 <+73>:    call   0x8048340 <strcpy@plt> 
    0x080484ca <+78>:    mov    0x18(%esp),%eax        
    0x080484ce <+82>:    mov    (%eax),%eax
    0x080484d0 <+84>:    call   *%eax
    0x080484d2 <+86>:    leave
    0x080484d3 <+87>:    ret
  End of assembler dump.
```

> This `main()` calls [`malloc()`](https://man7.org/linux/man-pages/man3/malloc.3.html) twice, [`strcpy()`](https://man7.org/linux/man-pages/man3/strcpy.3.html) and a loaded address in **EAX** register.

## Additional functions

Since variable in `main()` holds a callable address, it might be a function pointer so, let's check for available functions in this program.

```gdb
  $> gdb ./level6
  (gdb) info functions

  All defined functions:

  Non-debugging symbols:
  0x080482f4  _init
  0x08048340  strcpy
  0x08048340  strcpy@plt
  0x08048350  malloc
  0x08048350  malloc@plt
  0x08048360  puts
  0x08048360  puts@plt
  0x08048370  system
  0x08048370  system@plt
  0x08048380  __gmon_start__
  0x08048380  __gmon_start__@plt
  0x08048390  __libc_start_main
  0x08048390  __libc_start_main@plt
  0x080483a0  _start
  0x080483d0  __do_global_dtors_aux
  0x08048430  frame_dummy
  0x08048454  n
  0x08048468  m
  0x0804847c  main
  0x080484e0  __libc_csu_init
  0x08048550  __libc_csu_fini
  0x08048552  __i686.get_pc_thunk.bx
  0x08048560  __do_global_ctors_aux
  0x0804858c  _fini
```

> We can see that some `m()`and `n()` function are available.

Disassembling `m()` gives us the following:

```gdb
  $> gdb ./level6
  (gdb) disassemble m
  Dump of assembler code for function m:
    0x08048468 <+0>:     push   %ebp
    0x08048469 <+1>:     mov    %esp,%ebp
    0x0804846b <+3>:     sub    $0x18,%esp
    0x0804846e <+6>:     movl   $0x80485d1,(%esp)
    0x08048475 <+13>:    call   0x8048360 <puts@plt>
    0x0804847a <+18>:    leave
    0x0804847b <+19>:    ret
  End of assembler dump.
```

> Only calls [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html) so, nothing really interesting here.

Disassembling `n()` gives us the following:

```gdb
  $> gdb ./level6
  (gdb) disassemble n
  Dump of assembler code for function n:
    0x08048454 <+0>:     push   %ebp
    0x08048455 <+1>:     mov    %esp,%ebp
    0x08048457 <+3>:     sub    $0x18,%esp
    0x0804845a <+6>:     movl   $0x80485b0,(%esp)
    0x08048461 <+13>:    call   0x8048370 <system@plt>
    0x08048466 <+18>:    leave
    0x08048467 <+19>:    ret
  End of assembler dump.
```

> Only calls [`system()`](https://man7.org/linux/man-pages/man3/system.3.html), probably a way to get the next password.

# Data

## Strings

```gdb
  0x0804845a <+6>:     movl   $0x80485b0,(%esp)
  
  (gdb) x/s 0x80485b0
  0x80485b0:       "/bin/cat /home/user/level7/.pass"
```

The string `/bin/cat /home/user/level7/.pass` is stored at address `0x80485b0` and it is used in function `n()` inside a `system()` call, it must be the way to get the next password.

```gdb
  0x0804846e <+6>:     movl   $0x80485d1,(%esp)
  
  (gdb) x/s 0x80485d1
  0x80485d1:       "Nope"
```

The string `Nope` is stored at address `0x80485d1` and it is used in function `m()`.

## Buffers size

```gdb
  0x08048485 <+9>:     movl   $0x40,(%esp)
  0x0804848c <+16>:    call   0x8048350 <malloc@plt> 
  ...
  0x08048495 <+25>:    movl   $0x4,(%esp)
  0x0804849c <+32>:    call   0x8048350 <malloc@plt>

  (gdb) print 0x40
  $1 = 64
```

There are two allocated buffers set in `main()` respectively **64** and **4** bytes long.

## Buffers offset

Since we know that programs uses `strcpy()` at some point, it is vulnerable to **buffer overflow**.

```gdb
  $> gdb ./level6
  (gdb) run `echo -e "import string\nprint ''.join([char * 4 for char in string.ascii_letters])" | python`
  Starting program: /home/user/level6/level6 `echo -e "import string\nprint ''.join([char * 4 for char in string.ascii_letters])" | python`

  Program received signal SIGSEGV, Segmentation fault.
  0x73737373 in ?? ()
```

> This little python script creates a string that look likes `aaaabbbbcccc....`. Since the program crashed on address `0x73737373` which is `ssss` the offset is equal to `4 * (Index of letter - 1)`. So this buffer offset is **72**.