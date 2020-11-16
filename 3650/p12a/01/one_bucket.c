#include <assert.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>

#include "xmalloc.h"

// What we have:
//  - An array of a bunch of long*'s.
//
// What we're allocating:
//  - Many objects of size 8.

// Structure: 
//  - Page-at-a-time bucket allocator
//  - Optimized (shared) size header

// Chunk layout:
// 16384 bytes (4 pages):
//  - size: 8 bytes
//  - next: 8 bytes (void* to page)
//  - used array : (bytes as boolean) 512 bytes
//  - the memory blocks: 3200 bytes (400 longs)

const size_t CHUNK_SIZE = 16384;

typedef struct apage {
    size_t size;
    struct apage* next;
    void* mmap_start;
    uint8_t used[1600];
    long blocks[1600];
} apage;

// Not a free list.
// List of all allocated chunks.
static apage* pages = 0;

apage*
alloc_page()
{
    intptr_t addr = (intptr_t) mmap(0, 2*CHUNK_SIZE, PROT_READ|PROT_WRITE, 
            MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    intptr_t ptr = addr;
    while (ptr % CHUNK_SIZE != 0) {
        // OK for 4 pages; want to be more clever for larger chunks
        ptr += 4096;
    }

    apage* pg = (apage*) ptr;
    pg->size = 8;
    pg->next = 0;
    pg->mmap_start = (void*) addr;
    memset(&(pg->used), 0, 1600);
    return pg;
}


void*
xmalloc(size_t bytes)
{
    assert(bytes == 8);
    if (pages == 0) {
        pages = alloc_page();
    }

try_again:
    for (long ii = 0; ii < 1600; ++ii) {
        if (pages->used[ii] == 0) {
            pages->used[ii] = 1;
            return &(pages->blocks[ii]);
        }
    }

    apage* pg = alloc_page();
    pg->next = pages;
    pages = pg;
    goto try_again;
}

void
xfree(void* ptr)
{
    // Find the beginning of the chunk.
    intptr_t addr = (intptr_t) ptr;
    apage* pg = (apage*) (addr - (addr % CHUNK_SIZE));

    // Find the index.
    intptr_t base = (intptr_t) &(pg->blocks[0]);
    long ii = (addr - base) / sizeof(long);

    // Mark that item free.
    pg->used[ii] = 0;

    // Figure out if that means the whole chunk is free.
    // If so, remove the chunk from the list of chunks, unmap the chunk.
    // Maybe we want a doubly linked list of chunks?
}

void*
xrealloc(void* prev, size_t bytes)
{
    assert(0);
}

