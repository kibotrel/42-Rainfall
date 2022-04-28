# 42-Rainfall

Information security project. This is a collection of ELF Binary exploits to better understand how memory works.

## Breakdown

| Level | Ressources | Exploit |
| :-: | :-: | :-: |
| [0](./level0/README.md) | [EAX register](https://www.tutorialspoint.com/assembly_programming/assembly_registers.htm) | Simple reverse engineering |
| [1](./level1/README.md) | [EIP register](https://security.stackexchange.com/questions/129499/what-does-eip-stand-for) \| [Byte order](https://en.wikipedia.org/wiki/Endianness) \| [`cat`](https://man7.org/linux/man-pages/man1/cat.1.html) | [Buffer overflow attack](https://en.wikipedia.org/wiki/Buffer_overflow) |
| [2](./level2/README.md) | | [ret2libc attack](https://shellblade.net/files/docs/ret2libc.pdf) |
| [3](./level3/README.md) | [`printf()`](https://linux.die.net/man/3/printf) | [format string attack](https://infosecwriteups.com/exploiting-format-string-vulnerability-97e3d588da1b) |
| [4](./level4/README.md) | |  [format string attack](https://infosecwriteups.com/exploiting-format-string-vulnerability-97e3d588da1b) |
| [5](./level5/README.md) | |  [format string attack](https://infosecwriteups.com/exploiting-format-string-vulnerability-97e3d588da1b) \| [GOT overwrite](https://infosecwriteups.com/got-overwrite-bb9ff5414628) |
| [6](./level6/README.md) | [`strcpy()`](https://linux.die.net/man/3/fgets) | [Buffer overflow attack](https://en.wikipedia.org/wiki/Buffer_overflow) |
| [7](./level7/README.md) | | [Buffer overflow attack](https://en.wikipedia.org/wiki/Buffer_overflow) \| [GOT overwrite](https://infosecwriteups.com/got-overwrite-bb9ff5414628) |
| [8](./level8/README.md) | | Simple reverse engineering |
| [9](./level9/README.md) | | [Buffer overflow attack](https://en.wikipedia.org/wiki/Buffer_overflow) |
| [bonus0](./bonus0/README.md) | [shell-storm](http://shell-storm.org/shellcode/) \| [exploit-db](https://www.exploit-db.com/) | [Shellcode injection](https://en.wikipedia.org/wiki/Shellcode) |
| [bonus1](./bonus1/README.md) | | [Integer underflow](https://en.wikipedia.org/wiki/Integer_overflow) \| [Buffer overflow attack](https://en.wikipedia.org/wiki/Buffer_overflow) |
| [bonus2](./bonus2/README.md) | | [Shellcode injection](https://en.wikipedia.org/wiki/Shellcode) |
| [bonus3](./bonus3/README.md) | | Simple reverse engineering |