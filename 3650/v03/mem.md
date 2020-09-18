

## Places to put stuff

 - Stack
 - Heap - Dynamicly allocated memory
   Good place to put stuff when we don't know how big it is.

```
  void *malloc(size_t size);
  void free(void *ptr);
```

 - To get heap memory: malloc
 - When we're done with it: free
 - Every pointer we get from malloc needs to get passed to free exactly once.

## Forcing stack alignment

```
    mov $15, %rcx
    not %rcx
    and %rcx, %rsp
```

15 in decimal is ....001111 in binary

not 15 is ....11110000 in binary

AND forces the last 4 bits to zero

 - if %rsp is divisible by 16, this does nothing
 - if it's not, then it's rounded down to the next lowest multiple of 16
