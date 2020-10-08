
Different ways to copy strings:

```
char* strdup(char*);
```

Copy a string into newly allocated memory.

Logically, this funciton is just:

```
char*
strdup(char* xx)
{
    long nn = strlen(xx) + 1;
    char* yy = malloc(nn);
    strlcpy(yy, xx, nn);
    return yy;
}
```


```
void
strcpy(char* dest, const char* src)
{
    long ii = 0;
    for (; src[ii]; ++ii) {
        dest[ii] = src[ii];
    }
    dest[ii] = 0;
}
```

Loop through input, copy to output.

If source isn't a proper string - if it's not null terminated - then we copy
until a segfault happens.

If the allocated size for dest < strlen(src), we'll overflow the buffer.

strncpy exists to avoid copying too far, but it doesn't reliably null terminate
dest.

strlcpy is a corrected strncpy - it never overflows and always null terminates
the destination.

