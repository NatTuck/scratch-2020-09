:

# Challenging parts in the Challenge

## Dealing with multiple threads

 - Default: Allocator has global state, the free list
 - Running allocator from multiple threads concurrently => data race
 - Default solution: add a lock (mutex)
 - Problem: That serializes our allocator, which is a problem because
   many programs spend a *lot* of their time allocating and freeing

General idea to solve this: Have multiple data structures rather than
just one.

```
// An "arena" is a complete copy of the data structure
// needed for a simple single-threaded allocator.

struct allocated_memory_header {
    size_t size;
    long   arena;
};

// example: globally have *two* free lists
static free_list** lists[2]; // could also use a bucket allocator, buddy system, etc.
static pthread_mutex_t* locks[2];

static __thread int favorite_number = 5; // a global variable private to each thread

// how many?
//  - more arenas than threads (or processor cores)
//  - what about one arena per thread? can we get away with no locks?
//    - idea: use thread_local variables (see gcc "thread" keyword)

// randomly pick which one to use
void*
malloc(...)
{
    int arena = random(0..1); 

}

void
free(...)
{
    // Which free list do we free to?
    // Why does it matter? Coalescing
}
```

## Optimize for the test case

 - Beat the system allocator
 - The trick: Take advantage of the particular test programs
