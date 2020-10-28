

# Data Races

Conditions for a data race:

 - Concurrent execution of two processes / threads.
 - Shared data that both processes access (read or write).
 - At least one process writes.

Solving data races with locks:

 - Each piece of shared data should be protected by a lock.
 - Any process must lock the lock before accessing that shared data.
 - Make sure to unlock when done.

Locks work by preventing concurrency.


# Deadlock

If we have multiple locks, we risk deadlock.

 - Condition is: Circular wait.

Possible solution: Lock ordering


# Semaphores

A semaphore is a non-negative integer with two associated operations.

 - sem-wait: Attempt to decrement the value. If this would bring the value below zero,
   block the process/thread instead.
 - sem-post: Increment the value. If any process is blocked attempting to decrement, give it another try.

This allows sem-wait to restrict access to a resource to some fixed number of processes (the initial value of the semaphore). For the value 1, we have a lock.

If we start with a value of zero, processes can call sem-wait and immediately
block until sem-post is later called.

# A barrier

A barrier is an object that syncronizes the execution of a group of
processes of a fixed size.

```
    // 1: code
    barrier_wait();
    // 2: more code
```

The processes:

 - Run code before the barrier.
 - Hit the barrier and block until all processes have hit the barrier.
 - Once all processes have hit the barrier, they all run code after the barrier.
 
This is useful because we can break up data races.

Example:

 - We have four processes (numbered 0..3) filling in an array of size four.
 - Each process writes to data[pp].
 - Barrier between write and read phase eliminates race.
 - Each process read from the whole array.


