
# Writing a Memory Allocator

A (normal, C-style) memory allocator allocates memory on the heap.

Two functions:

 - void* malloc(size_t size);
 - void free(void*)


A new process starts with no heap allocated.

To get heap space:

 - Traditionally, we used sbrk
 - On modern systems, we generally use mmap
   - The heap is a collection of regions, not just one.
   - To allocate private memory, that's MAP\_PRIVATE | MAP\_ANONYMOUS
   - The smallest region we can alloate with mmap is 4k
   - munmap takes (ptr, size)

To implement malloc, we have some goals:

 - We want it to be reasonably fast.
   - Syscalls are slow.
   - Especially for small allocations, we'd rather reuse memory
     over returning it to the os with munmap.
 - We don't want to waste too much memory.
   - We need to handle allocations under 1 page.
   - for (i = 1..100) { xs[i] = malloc(10); } 
 - Need to be able to match the standard interface.
   - free just takes a pointer, not a size
   - So that means our allocator needs to remember sizes somehow

The traditional / simple solution to this problem (and what you need for HW08)
is a "free list", which works as follows:

 - We're going to maintain a list of free blocks of memory.
 - When memory is requested with malloc, first we check the free list to see if
   the request can be satisfied with an already-allocated block.
 - If no block on the free list works, we request more memory from the OS with
   mmap, split off a chunk to satisfy the malloc, and put the rest of the chunk
   on the free list.
 - When memory is freed, we put the block on the free list.

Logically, our free list is a list of blocks with (for each block):

 - Location (memory address)
 - Size (in bytes)

## Problems

Where do we put the free list?

 - Simplest way to store a list is a linked list, but that needs a memory
   allocator.
 - Same problem for a VLA / vector.

Idea: A free list tracks *unused chunks of memory*. We can store data about
a free chunk of memory *in that chunk*.

Two things we needed to store were:

 - Location of the block (this is the pointer, which we have if we have the block)
 - Size of the block (we can store this in the block of memory)

This can be a linked list, where:

 - We have a single global pointer to the head of the free list
 - Each cell contains a struct { size, next }


Where do we store size for *allocated* blocks of memory?

 - We are the memory allocator. We can request extra bytes of memory to
   store stuff in.
 - If the user requests 100 bytes, we can allocate 100 + sizeof(size_t) = 108
   bytes.
 - Where do we put the size field? 

       +---------+
       |         |
       | data    |
ptr -> +---------+
       | size    |    size header comes *before* user allocated block
       +---------+



```
    aa = malloc(100)
    bb = malloc(100)
    cc = malloc(400)
    free(bb)
    dd = malloc(100)
    ee = malloc(4000)
    free(aa)
    free(dd)
    ff = malloc(200)
    free...
```

```
struct free_list_cell {
    size_t size;
    struct free_list_cell* next;
}
// sizeof(free_list_cell) = 16 B
// Minimum allocation size = 16 B, why?
```

```
          +-------------+
          | next = 0    |
          | size = 88   |
36776 ->  +-------------+
          | data for ee |
          | size = 4008 |
32768 ->  +-------------+


          +-------------+
          | next=36776  |
          | size = 3472 |
17000 ->  +-------------+
          | 400B for cc |
          | size = 408  |
16600 ->  +-------------+
          | next=17000  |
          | size = 216  |
16384 ->  +-------------+

free_list_head -> 36776

aa = 16392
bb = 16500 (invalid)
cc = 16608
dd = 16500
ee = 32776
ff = 16392
```

## Big Allocations

```
  zz = malloc(10G)
  free(zz) // better to just munmap so OS can reuse
```

```
void*
malloc(size_t bytes)
{
    if (bytes > BIG_MIN) {
        mmap
    }
    else {
        check free list 
    }

}
```


## Design Considerations

 - Singly or doubly linked list  (single is simpler)
 - List be ordered or unordered
   - Ordered by what?

Unordered list:

 - Insertion is O(1), just cons
 - Coalesing is at least O(n), maybe worse

Order by size:

 - Allocation is faster because we can stop searching early maybe.
 - Not an asymptotic improvement, both are O(N)

Order by memory address: <- best idea

 - Insertion is O(N)
 - Coalescing is free.

How big should the "big allocation" cutoff be?

 - Minimum is 4096 bytes
 - 64k? 1M? 100M?
 - Probalby smaller than 1GB

Should we ever return memory to the OS from the free list?

 - Simple answer: no. <- ok for HW08
 - Complex answer: maybe
   - Idea: If we have more than 10 full pages on the free list, free
           down to 10.
 
