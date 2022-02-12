# Level0

Once logged as level0 we are prompted the following message:

```
GCC stack protector support:            Enabled
Strict user copy checks:                Disabled
Restrict /dev/mem access:               Enabled
Restrict /dev/kmem access:              Enabled
grsecurity / PaX:                       No GRKERNSEC
```

It gives us some information about how binaries are compiled and what we could or couldn't use as leads to exploit these binaries.

- [GCC Stack protector](https://mudongliang.github.io/2016/05/24/stack-protector.html) is a compiler option that checks for potential [buffer overflows](https://en.wikipedia.org/wiki/Buffer_overflow). It adds a guard variable to functions with vulnerable objects according to the documentation.
- [Strict user copy checks](https://blog.siphos.be/2011/07/checksec-kernel-security/) is a kernel option that enables the compiler to detect function calls with variable length arguments so that it can predict the length of the argument. This further prevent buffer overflows.
- Restricting [`/dev/mem`](https://blog.siphos.be/2011/07/checksec-kernel-security/) and [`/dev/kmem` access](https://blog.siphos.be/2011/07/checksec-kernel-security/) tells to the kernel to not allow applications to access all of memory, only device-mapped memory and their own process for everything including the kernel memory if access to `/dev/kmem` is restricted as well.
- [grsecurity / PAX](https://wiki.debian.org/grsecurity) is a set of patches for the kernel with an emphasis on enhancing security.

Using [`checksec`](https://www.systutorials.com/docs/linux/man/7-checksec/) we can have more details on the binary protections themselves.

```shell
  $> checksec --file level0
  RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
  No RELRO        No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   level0
```

Once again a lot of information here:

- [RELRO](https://www.redhat.com/en/blog/hardening-elf-binaries-using-relocation-read-only-relro) means **Rel**ocation **R**ead-**O**nly. It is a compiler option that force the linker to resolve all dynamically linked functions at the beginning of the execution and then makes the [Global offset table](https://en.wikipedia.org/wiki/Global_Offset_Table) (GOT) read-only. It is meant to prevent some security weakness induced by the GOT itself.
- [Stack canary](https://www.sans.org/blog/stack-canaries-gingerly-sidestepping-the-cage/) is a way to prevent buffer overflows to be exploitable by putting some value after the buffer itself on the stack and check if it was overriden on function return.
- [NX](https://access.redhat.com/solutions/2936741) is an hardware technology use in processors to prevent execuion of certain types of code.
- [PIE](https://en.wikipedia.org/wiki/Position-independent_code) is a process that will randomize code position in memory at run-time, making exploit harder to perform.
- [`RPATH`](https://en.wikipedia.org/wiki/Rpath#:~:text=In%20computing%2C%20rpath%20designates%20the,(or%20another%20shared%20library).) is a variable used at run-time. It contains a list of hard-coded paths in which the binary could search.
- `RUNPATH` is almost the same as `RPATH`. The difference lies in the order they are searched in. `RPATH` is searched in before [`LD_LIBRARY_PATH`]() while `RUNPATH` is searched in after. The meaning of this is that `RPATH`cannot be changed dynamically with environment variables while `RUNPATH` can.

Now let's see what does the binary do.

```shell
  $> ./level0
  Segmentation fault (core dumped)
  $> ./level0 "test"
  No !
```

> Seems like this program want us to input an argument.

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on.

```gdb
  $> gdb ./level0
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x08048ec0 <+0>:     push   %ebp
    0x08048ec1 <+1>:     mov    %esp,%ebp
    0x08048ec3 <+3>:     and    $0xfffffff0,%esp
    0x08048ec6 <+6>:     sub    $0x20,%esp
    0x08048ec9 <+9>:     mov    0xc(%ebp),%eax
    0x08048ecc <+12>:    add    $0x4,%eax
    0x08048ecf <+15>:    mov    (%eax),%eax
    0x08048ed1 <+17>:    mov    %eax,(%esp)
    0x08048ed4 <+20>:    call   0x8049710 <atoi>
    0x08048ed9 <+25>:    cmp    $0x1a7,%eax
    0x08048ede <+30>:    jne    0x8048f58 <main+152>
    0x08048ee0 <+32>:    movl   $0x80c5348,(%esp)
    0x08048ee7 <+39>:    call   0x8050bf0 <strdup>
    0x08048eec <+44>:    mov    %eax,0x10(%esp)
    0x08048ef0 <+48>:    movl   $0x0,0x14(%esp)
    0x08048ef8 <+56>:    call   0x8054680 <getegid>
    0x08048efd <+61>:    mov    %eax,0x1c(%esp)
    0x08048f01 <+65>:    call   0x8054670 <geteuid>
    0x08048f06 <+70>:    mov    %eax,0x18(%esp)
    0x08048f0a <+74>:    mov    0x1c(%esp),%eax
    0x08048f0e <+78>:    mov    %eax,0x8(%esp)
    0x08048f12 <+82>:    mov    0x1c(%esp),%eax
    0x08048f16 <+86>:    mov    %eax,0x4(%esp)
    0x08048f1a <+90>:    mov    0x1c(%esp),%eax
    0x08048f1e <+94>:    mov    %eax,(%esp)
    0x08048f21 <+97>:    call   0x8054700 <setresgid>
    0x08048f26 <+102>:   mov    0x18(%esp),%eax
    0x08048f2a <+106>:   mov    %eax,0x8(%esp)
    0x08048f2e <+110>:   mov    0x18(%esp),%eax
    0x08048f32 <+114>:   mov    %eax,0x4(%esp)
    0x08048f36 <+118>:   mov    0x18(%esp),%eax
    0x08048f3a <+122>:   mov    %eax,(%esp)
    0x08048f3d <+125>:   call   0x8054690 <setresuid>
    0x08048f42 <+130>:   lea    0x10(%esp),%eax
    0x08048f46 <+134>:   mov    %eax,0x4(%esp)
    0x08048f4a <+138>:   movl   $0x80c5348,(%esp)
    0x08048f51 <+145>:   call   0x8054640 <execv>
    0x08048f56 <+150>:   jmp    0x8048f80 <main+192>
    0x08048f58 <+152>:   mov    0x80ee170,%eax
    0x08048f5d <+157>:   mov    %eax,%edx
    0x08048f5f <+159>:   mov    $0x80c5350,%eax
    0x08048f64 <+164>:   mov    %edx,0xc(%esp)
    0x08048f68 <+168>:   movl   $0x5,0x8(%esp)
    0x08048f70 <+176>:   movl   $0x1,0x4(%esp)
    0x08048f78 <+184>:   mov    %eax,(%esp)
    0x08048f7b <+187>:   call   0x804a230 <fwrite>
    0x08048f80 <+192>:   mov    $0x0,%eax
    0x08048f85 <+197>:   leave  
    0x08048f86 <+198>:   ret
  End of assembler dump.
```

> We can see [`atoi()`](https://linux.die.net/man/3/atoi), [`strdup()`](https://linux.die.net/man/3/strdup), [`getegid()`](https://linux.die.net/man/2/getegid), [`geteuid()`](https://linux.die.net/man/3/geteuid), [`setresgid()`](https://linux.die.net/man/2/setresgid), [`setresuid()`](https://man7.org/linux/man-pages/man2/setresuid.2.html), [`execv()`](https://man7.org/linux/man-pages/man2/execve.2.html) and [`fwrite()`](https://linux.die.net/man/3/fwrite) calls.

There is one interesting instruction here which is this line:

```gdb
  0x08048ed9 <+25>:    cmp    $0x1a7,%eax
```

> This is a comparison between two values one being `0x1a7` and the other being what's currently stored in [EAX Register](https://www.tutorialspoint.com/assembly_programming/assembly_registers.htm).

Let's convert this hexadecimal value using [`bc`](https://www.tutorialspoint.com/assembly_programming/assembly_registers.htm)

```shell
  $> echo 'ibase=16; 1A7' | bc 
  423
```