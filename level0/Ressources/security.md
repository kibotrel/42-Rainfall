# OS and File security

Once logged on the we are prompted the following message:

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
- `RUNPATH` is almost the same as `RPATH`. The difference lies in the order they are searched in. `RPATH` is searched in before [`LD_LIBRARY_PATH`]() while `RUNPATH` is searched in after. The meaning of this is that `RPATH` cannot be changed dynamically with environment variables while `RUNPATH` can.