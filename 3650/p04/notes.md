

# Some Notes

 - Memory layout of a process
 

   64 bit address space

```
  16 EB ----------------------------
    
     // Stuff that isn't in the executable file
     // but is created when the process starts
     +---------------------
     |   stack
     |   (grows down)       0x7ffd 0cde4ee0
     ...
     
     
     ...
     |   (grows up)
     |   heap             0x5577 ae16a260
     +-----------------------
     
     // Stuff we load from the executable file
      +-------------
      |   .text           0x5577 ad94 1155
      +-------------
      |   .data           0x5577 ad94 4040
      +-------------
  0 GB ---------------------------
```


# Stack Allocations


```
   long xs[nn];
   vs.
   long* xs = alloca(nn*sizeof(long));
```



# Big Endian vs. Little Endian

```
short ys[] = {0, 1};
sizeof(short) = 2;

bytes: 0, {0, 1}, 0
```

In memory

```
[two bytes: 0] [two bytes: 1]
```

Option 1 - Big Endian:

```
short x = 1;
[one byte: 0] [one byte 1]
two digit number, each digit is 8 bits or a value between 0 and 255
```

Option 1 - Little Endian 

```
short x = 1;
[one byte: 1] [one byte: 0]
two digit number, each digit is 8 bits or a value between 0 and 255
```

address: 0x1000
 |
 v
[0, 1, 0, 0]
 ^
 |
address: 0x1000 



```
atol(argv[1])

int
main(int argc, char* argv[])

argv is an array of string

   argv[1] is a string
   argv[2][0] is a char





```






