# OS and File security

Let's run [`checksec`](https://www.systutorials.com/docs/linux/man/7-checksec/) on the binary we have.

```shell
  $> checksec --file level1 
  RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
  No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level1
```

> Same security as `level0` except `NX` which is now **disabled**.