# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level1
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x08048480 <+0>:     push   %ebp
    0x08048481 <+1>:     mov    %esp,%ebp
    0x08048483 <+3>:     and    $0xfffffff0,%esp
    0x08048486 <+6>:     sub    $0x50,%esp
    0x08048489 <+9>:     lea    0x10(%esp),%eax
    0x0804848d <+13>:    mov    %eax,(%esp)
    0x08048490 <+16>:    call   0x8048340 <gets@plt>
    0x08048495 <+21>:    leave  
    0x08048496 <+22>:    ret    
  End of assembler dump.
```

> Small program this time, all we can see is [`gets()`](https://linux.die.net/man/3/gets) being call.

## Additional functions

We can get more details on this program by listing all functions it uses.

```gdb
  (gdb) info functions
  All defined functions:

  Non-debugging symbols:
  0x080482f8  _init
  0x08048340  gets
  0x08048340  gets@plt
  0x08048350  fwrite
  0x08048350  fwrite@plt
  0x08048360  system
  0x08048360  system@plt
  0x08048370  __gmon_start__
  0x08048370  __gmon_start__@plt
  0x08048380  __libc_start_main
  0x08048380  __libc_start_main@plt
  0x08048390  _start
  0x080483c0  __do_global_dtors_aux
  0x08048420  frame_dummy
  0x08048444  run
  0x08048480  main
  0x080484a0  __libc_csu_init
  0x08048510  __libc_csu_fini
  0x08048512  __i686.get_pc_thunk.bx
  0x08048520  __do_global_ctors_aux
  0x0804854c  _fini
```

We can see `run` which is never called in the main. Let's check what it's supposed to do.

```gdb
  (gdb) disassemble run
  Dump of assembler code for function run:
    0x08048444 <+0>:     push   %ebp
    0x08048445 <+1>:     mov    %esp,%ebp
    0x08048447 <+3>:     sub    $0x18,%esp
    0x0804844a <+6>:     mov    0x80497c0,%eax
    0x0804844f <+11>:    mov    %eax,%edx
    0x08048451 <+13>:    mov    $0x8048570,%eax
    0x08048456 <+18>:    mov    %edx,0xc(%esp)
    0x0804845a <+22>:    movl   $0x13,0x8(%esp)
    0x08048462 <+30>:    movl   $0x1,0x4(%esp)
    0x0804846a <+38>:    mov    %eax,(%esp)
    0x0804846d <+41>:    call   0x8048350 <fwrite@plt>
    0x08048472 <+46>:    movl   $0x8048584,(%esp)
    0x08048479 <+53>:    call   0x8048360 <system@plt>
    0x0804847e <+58>:    leave  
    0x0804847f <+59>:    ret    
  End of assembler dump.
```

> We can see calls to [`fwrite()`](https://linux.die.net/man/3/fwrite) and [`system()`](https://man7.org/linux/man-pages/man3/system.3.html) there.

If we get a closer look into this function we can see this:

```gdb
  0x08048472 <+46>:    movl   $0x8048584,(%esp)
  0x08048479 <+53>:    call   0x8048360 <system@plt>

  x/s 0x8048584
  0x8048584: "/bin/sh"
```

> This should be the way to get a shell via this binary.

## Data

### Additional function address

```gdb
  info address run
  Symbol "run" is at 0x8048444 in a file compiled without debugging.
```

The `run()` function is located at address `0x8048444`.

### Buffer offset

```gdb
  (gdb) b *0x08048490
  Breakpoint 1 at 0x8048490
  (gdb) run 
  Starting program: /home/user/level1/level1 

  Breakpoint 1, 0x08048490 in main ()
  (gdb) i f
  Stack level 0, frame at 0xbffff730:
  eip = 0x8048490 in main; saved eip 0xb7e454d3
  Arglist at 0xbffff728, args: 
  Locals at 0xbffff728, Previous frame's sp is 0xbffff730
  Saved registers:
    ebp at 0xbffff728, eip at 0xbffff72c
  (gdb) x $esp
  0xbffff6d0: 0xbffff6e0
```

> We put a breakpoint before the `gets()` call to retrieve some useful addresses: [EIP register](https://security.stackexchange.com/questions/129499/what-does-eip-stand-for) and the one where the buffer starts.

We get the following adresses:

- EIP register: `0xbffff72c`
- Buffer beginning: `0xbffff6e0`

Now, to compute the offset we simply need to substract the buffer address from EIP's one.

```shell
  $> echo 'ibase=16; BFFFF72C - BFFFF6E0' | bc
  76
```

The buffer offset is `76`.