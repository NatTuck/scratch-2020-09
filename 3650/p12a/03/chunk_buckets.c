
#include <sys/mman.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

// One Bucket: For 8B allocations
//
// Heap is implemented by allocating large
// chunks, with shared metadata.
//
// We'll use pointer arithmetic to find the
// start of a chunk to manage shared metadata.

const size_t CHUNK_SIZE = 16384; // 4 pages
#define BPC 1700   // blocks per chunk

typedef struct chunk {
    size_t size; // always 8
    struct chunk* next;
    void* base; // mmap return address
    uint8_t used[BPC];
    long blocks[BPC]; // this can't be this easy for variable sizes
} chunk;

static chunk* chunks = 0;

void*
xmalloc(size_t bytes)
{
    assert(bytes == 8);

    for (chunk* cc = chunks; cc; cc = cc->next) {
        for (long ii = 0; ii < BPC; ++ii) {
            if (cc->used[ii] == 0) {
                cc->used[ii] = 1;
                return &(cc->blocks[ii]);
            }
        }
    }

    // No chunk?
    intptr_t alloc_addr = (intptr_t) mmap(0, 2*CHUNK_SIZE, PROT_READ|PROT_WRITE, 
            MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    intptr_t chunk_addr = alloc_addr;
    while (chunk_addr % CHUNK_SIZE != 0) {
        chunk_addr += 4096;
    }

    chunk* cc = (chunk*) chunk_addr;
    cc->size = 8;
    cc->next = chunks;
    cc->base = (void*) alloc_addr;
    memset(&(cc->used[0]), 0, BPC);
    chunks = cc;

    return xmalloc(8);
}

void
xfree(void* ptr)
{
    // Find the chunk
    //  - ptr is an address of a block within the chunk
    //  - chunks are allocated at addresses which are multiples of 16384
    // 
    intptr_t ptr_addr = (intptr_t) ptr;
    intptr_t chunk_addr = ptr_addr - (ptr_addr % CHUNK_SIZE);
    chunk* cc = (chunk*) chunk_addr;

    // Figure out our index into the blocks array
    //  - Calculate difference between block array and blocks[0]
    //  - Divide by 8
    intptr_t block0_addr = (intptr_t) &(cc->blocks[0]);
    long ii = (ptr_addr - block0_addr) / sizeof(long);

    // Mark block unused
    cc->used[ii] = 0;

    // If entire chunk is now unused:
    //  - Remove from list of chunks.
    //  - Unmap it.
    //  - Idea: Maybe doubly linked list is better.
}

void*
xrealloc(void* prev, size_t bytes)
{
    assert(0);
}

