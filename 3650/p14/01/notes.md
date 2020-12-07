
# Computer Systems

 - Low level programming
 - What system? What platform?
 - One platform: Linux on AMD64
   - One assignment on xv6 on i386
 - Platform provides two APIs:
   - Syscalls (e.g. "open")
   - Machine instructions (e.g. "addl")
 - Best tool for developing on Linux is Linux
   - UNIX is an IDE for UNIX + C
   - Linux is ...
 - login server exists

## First major topic: Assembly

 - A program is a sequence of machine instructions
   - Assembly expresses these as text
   - Hardware wants machine code, which can be assembled from that text
 - Assembly is related to C in that they have the same concept of "functions"
 - HW02: Write assembly
 - HW03: Act as a compiler, translate quicksort

## Next major topic: System Calls 

 - The "syscall" instruciton allows user programs to request help from the OS
 - From C, you use wrappers: "write" calls the write syscall

## Interesting stuff to look at

 - Get an ARM machine.
   - Look at Pine64's dev machines
 - Try ARM assembly / the ARM64 platform

## C Programming: Data Structures

 - HW04: Built a Vector and a HashMap

## UNIX Shell

 - Tokenizer, string in C
 - Process-related system calls
   - Wait, what's a process?
   - A process is a running instance of a computer program.
   - Processes created by fork.
   - Programs are executed with exec.
 - File descriptors
   - Allowed shell operators

## Shared Memory, Concurrency, and Parallelism

 - Most significant syscall: mmap
 - mmap allows memory sharing between processes with MAP\_SHARED and fork()

Now we have shared memory between concurrently executing processes. That's a
problem. Why?

 - Data race!
 - What's a data race? 
   - Things happen concurrently.
   - That means we don't know what order the happen in.
   - The order potentially mattered.
   - That means we don't know what happened.
 - When two different processes read/write to the same memory and we don't know what
   order those events happened in.
 - Result: We can end up with memory in an unexepected state (i.e. it gets corrupted).

What is "concurrency"? Two or more processes running *logically* at the same
time. We can't assign a known order to what the processes do.

What's the most common solution to a data race (aside from simply eliminating
concurrency entirely)? Locks!

The plan for locks:

 - For every piece of shared data, it's protected by a lock.
 - Before accessing the shared data (read or write), the accessing
   process/thread must first hold the lock.
 - When the process is done with it's operation that wants to be atomic,
   it releases the lock.
 - If you do this, data races aren't a problem anymore.

But locks cause a problem themselves. What? Deadlock!

What's deadlock? When two locks are locked, both waiting on the other to
unlock. Or more generally, when some cycle of processes is circularly waiting
on each other.

How can we have locks but avoid deadlock?

 - Only lock in a specific order.
 - Simpler answer: Never lock more than one lock at a time.

We added threads - same stuff.

## Next topic: Memory Allocators

 - Simple allocator
 - Super optimized allocator for CH02

## Next topic: Implementing a syscall in xv6

 - You did this

## Last topic: Filesystems

 - FAT
 - ext => ext2 => ext3 => ext4 (journaling)
 - More modern filesystems CoW
 - CH03: Getting up to ext-level functionality

 - Neat project: Secure distributed filesystem







