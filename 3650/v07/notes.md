
A data race is likely if your program:

 - Multiple concurrent processes.
 - Shared memory is accessed concurrently by multiple processes.
 - At least one process writes to that shared memory.

We can avoid data races with locks.

 - Each piece of shared memory is protected by a lock.
 - We always lock the lock before accessing that shared memory.

But locks can lead to deadlock.

 - Deadlocks are caused by "circular wait".

Avoiding deadlocks:

 - Plan A: Never hold more than one lock.

Advanced plan for avoiding deadlock: Lock ordering

 - Assign a global order among all locks in the program
 - Rule: Never attempt to lock a lock if you're already holding a lock
   that is ordered after it (always lock locks in order)
 - This is hard for larger programs.
