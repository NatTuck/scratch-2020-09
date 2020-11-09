
#include "xmalloc.h"

// TODO: This file should be replaced by another allocator implementation.
//
// If you have a working allocator from the previous HW, use that.
//
// If your previous homework doesn't work, you can use the provided allocator
// taken from the xv6 operating system. It's in xv6_malloc.c
//
// Either way:
//  - Replace xmalloc and xfree below with the working allocator you selected.
//  - Modify the allocator as nessiary to make it thread safe by adding exactly
//    one mutex to protect the free list. This has already been done for the
//    provided xv6 allocator.
//  - Implement the "realloc" function for this allocator.

void*
xmalloc(size_t bytes)
{
    // TODO: replace this with malloc
    return 0;
}

void
xfree(void* ptr)
{
    // TODO: replace this with free
}

void*
xrealloc(void* prev, size_t bytes)
{
    // TODO: write realloc
    return 0;
}
