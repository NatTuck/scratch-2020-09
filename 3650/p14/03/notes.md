

# Part 1: Challenge 3 Questions?



# Part 2: Topics This Semester


## A: "Computer Systems"

 - A computer platform / system consists of:
   - Operating System: Linux
   - Instruction Set Archetecture (type of CPU): AMD64
 - Also saw: xv6 on i386
 - A system provides two "APIs":
   - Operating system provides syscalls
   - CPU provides machine instructions

## B: First HW topic: Assembly Language

 - HW02: Write assembly programs
 - HW03: Act as a compiler to compile Quicksort
 - System calls can be made from assembly, with the "syscall" instruction.

## C: C Programming

 - Implemented Vector and HashMap
 - Shell Tokenizer

## D: UNIX Shell

 - Syscalls for process management
   - fork creates proccesses
   - exec runs programs
 - Syscalls for file I/O
   - dup

What is a process?

 - A process is an instance of a running program

## E: Concurrency and Parallelism

 - Introduced mmap (our favorite syscall), with MAP\_SHARED
 - We now have concurrently executing processes with shared memory. That's a
   problem. Why?
   - Problem is data races
   - What is a data race? Multiple processes try to read/write memory in the
     same place at the same time.
   - We're going to get unexpected results.
     - Multiple instructions aren't executed atomicly.
     - Behavior is different from expected sequential execution.
     - Processes don't expect competition.
   - "Concurrency" means things happen "at the same time", which is another way
     to say that we can't assign an order in which they happen.
     - If the order matters - produces different results - then we don't know
       what our program does.
   - We could try to solve this by:
     - Not having concurrency.
     - Proving that we really don't care about execution order.

How do we normally solve this without entirely avoiding concurrency?

 - Plan A: Locks

The procedure for locks:

 - Every piece of shared data is protected by a lock.
 - Any process (or thread) that accesses (read or write) the shared data must
   hold the lock.
 - Once the atomic operation is done, the lock is unlocked.

Unfortunately, locks cause problems too:

 - New problem: Deadlock
 - Deadlock is a thing that happens when one process is wating for a lock held
   by another, and the second process is waiting for a lock held by the first.
 - Or, more generally, when we have waiting in a cycle.

Deadlock can be solved:

 - By never locking more than one lock at a time.
 - By mandating a fixed global order that locks are locked in.

## F: Memory Allocators

 - HW: Simple allocator
 - CH02: Optimized, thread-safe allocator

## G: xv6

 - You implemented a syscall

## H: File Systems

 - FAT
 - ext => ext2 => ext3 => ext4 (journaling)
 - CoW filesystems
   - Apple devices, Windows Servers, Many Linux systems (btrfs / ZFS), BSD (ZFS)
   - ext4 / NTFS (another journaling FS) are being phased out

### COW Filesystems

 - On write, copy and modify the copy (of a block0 rather than overwriting the
   old version
 - This gives us free snapshots
 - Crashes can't lose data, since we don't overwrite the old version until later
 - Keep all old versions forever - or until the garbage collector gets them.

### Journaling Filesystems

 - We write everything twice.
 - First, we write a log saying what we plan to do.
 - Then we mutate the data in the FS data structure as planned.
 - If we crash after log, we can replay log.


# Questions on the semester?

 - How does ISA effect higher level software.
   - Hopefully not much.
   - I recommend getting an ARM machine and trying ARM assembly.
     - e.g Raspberry Pi, Pine64 Pinephone/Pinebook
 - Recommended systems courses:
   - Systems and Networks / Networks and Distributed Systems
   - Compilers

# Questions on CH03?

 - Large reads / writes?
   - One userspace write can produce several nufs\_write callbacks.
   - You should be able to handle any valid call.
     - offset = 1000, size = 8000
     - offset = 77, size = 44
     - offset = k*4096, size = 4096 is pretty likely
     - Not safe to assume that offset is always a multiple of 4096
     - offset = 4000, size = 200 is page 0 and page 1
 - Timestamps
   - You should remember the two timestamps provided in the FUSE
     callback and correctly report them on stat calls.
 - ioctl?
   - If it doesn't get called, you don't need it.
 - symlinks (aka shortcuts)
   - You get a "symlink" call which gives you a path and a string.
   - You remember the string (e.g. store it in the data block)
   - You get a "readlink" call to the same path, you give back the
     string you got.
 - Permissions should only matter for stat (e.g. what you see from ls -l)
 - Fun filesystem project for winter break
   - An encrypted distributed file system
   - Email me if you want more info

## Last Lecture of the semester

 - Good luck with CH03.
 - Have an excellent winter break! 




