

# HW08 - Memory Allocator

 - You'll get to write a memory allocator!
 - Actually 2: CH02 is another one.

# Page Tables

 - Every process gets its own virtual address space.
 - Virtual memory is managed in pages.
   - Usually 4k.
   - Sometimes bigger.
 - This means that every running process needs a lookup table
   which maps virtual pages to physical pages.

## 32 bit page tables

 - How many potential 4k pages fit in a 32-bit address space?
   - 32 bit address space = 2^32 = 4 GB
   - 4k page = 2^12
   - That's 2^20 = 1M pages
   - Need to map 1M virtual page #'s to up to 1M physical page #'s.
 - How big is a page table entry?
   - Index into table (map key) is a virtual page #, so 20 bits. (no space taken)
   - Physical page #: 20 bits
   - Permissions and other flags ?
   - = Total is something like 64 bits = 8 bytes
 - If the table is an array that's
   - 1M entries
   - 8 bytes per entry
   - = 8 MBs for a table

Problem: The origional i386 shipped with like 2MB of RAM.

64 bits is even worse:

 - How many potential 4k pages fit in a 64-bit address space?
 - 2^64 / 2^12 = 2^52

How to solve?

Hash tables? Resizing takes O(n), and that's not good enough.

Binary Search Tree? O(log n) seems slow here.

## Solution: Multi-level page tables

32-bit:

 - Split up the table into two levels
   - Root table (first 10 bits of physical address -> second table)
   - Leaf table (second 10 bits of physical address -> page table row)

Virtual Address:

  0000000001 0000000010 000000000011

32 bits breaks up as first-level 10, second level 10, offset 12

A table with a 10-bit index has 2^10 = 1024 entries

 - First level table just needs to store address of next table.
 - Second level table contains PTE
 
Two levels of page tables lets us not allocate unused second-level tables.

Minimum size for a process:

 - 1 page for stack
   - gets its own second-level table
 - 1 page for heap
   - gets its own second-level table
 - 1 page for data
 - 1 page for text
   - share a second-level table
 - = 4 pages

Total memory used for 2-level table:

 - top level table is 1024 * 8 = 8 kB
 - 3 second-level tables = 8 * 3 = 24 kB
 - minimum size = 32k for page tables per process

64-bit page table:

 - First plan: We don't need 64-bits; 48 is plenty
 - offset is still 12, leaving 36 bits for indexes
 - AMD64 does 4-level page tables: 9, 9, 9, 9, offset 12 = 48
 - Next expansion is 5-level tables: 5 * 9 + 12 = 57
 - 2^48 = 256 TB

Problem: Programs use virtual addresses

 - An instruction (e.g. mov (%rsp), %rax) uses virtual addresses.
 - This needs to be translated to a physical address.
 - Hardware (MMU) can handle the lookup, but it still takes an extra
   2 memory accesses on 32-bit
 - This would mean that every memory access actaully takes 3 memory accesses.
 - This is way too expensive.
 - Solution: A cache, called the TLB or Translation Lookaside Buffer
   - Stores the last 1536 virtual -> physical translations

Consider the following code:

```
int* xs = // two pages of data;
int sum = 0;
for (int ii = 0; ii < 2048; ++ii) {
   sum += xs[ii];
}
```

Without TLB, with four-level table:

 2048 * 1 + 2048 * 4 = 10k memory accesses

With TLB, with four-level table:

 2048 * 1 + 2 * 4 = 2k memory accesses


# Context Switches

Consider:

 - One core processor
 - Two processes
 - Both have computation to do
 - OS makes them take turns (pre-emptive scheduling)
 - After a fixed amount of time, a hardware interrupt occurs (a timer)
   and runs the scheduler code in the kernel.

To switch processes:

 - Hardware interrupt occurs, jumping us to kernel interrupt handler code.
 - Handler saves off current value for all registers to the current process
   stack.
 - Kernel picks a new process to run.
 - Kernel tells the processor to use the page table for the new process.
 - The saved registers are restored from the stack... but it's the new stack
   now, so we're restoring the state of that process.
 - We return from the interrupt handler into the new process.

One thing slows this down:

 - All the TLB entries are no longer valid.
 - So until the TLB is loaded up again, lots of memory accesses take
   5 memory accesses for a while.

This is better for threads: just need to switch stack pointer, don't lose the
TLB because the page table is the same.

More reasons to context switch:

 - Blocking
   - I/O
   - IPC (e.g. locks, semaphores)
