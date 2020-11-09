
# Challenges in the Challenge Assignment

 - Multi-threaded
   - Problem: Allocator has shared global state (e.g. the free list)
   - Two threads allocating at the same time is a data race
   - Solution: Add a lock (mutex) to protect that shared data
   - Problem 2: Allocatoin is pretty common in many programs,
     so a lock on the allocator may sequentialize the program
     overall and eliminate parallel speedup.
 - Want to beat the system allocator
   - This is possible because we're looking at two concrete test cases.
   - So you'll need to figure out what those test cases do and optimize
     for that.

## Speeding up compared to a single lock

General strategy: Have more than one "arena"

By "arena", I mean the data structures associated with an allocator. So for a
free-list allocator, an arena is a free list.

```
// Thread-local arenas
static __thread list_cell* free_list;
// Really nice: no mutex
static list_cell* remote_frees[2];
static pthread_mutex_t locks[2];

// Multiple shared arenas
static list_cell* free_lists[2];
static pthread_mutex_t locks[2];

struct allocated_header {
    size_t size;
    long   arena_id;
};

void*
malloc(...)
{
    int arena_id = random(0..1);
    pthread_mutex_lock(&(locks[arena-id]));
    list_cell* free_list = free_lists[arena_id];
    ...
}

void
free(void* ptr)
{
    // which free list do we use?
    // why not just pick a random one again?

    // Could end up with unbalanced usage
    // which would waste memory.

    // Problem: Can't coalesce!


}
```





