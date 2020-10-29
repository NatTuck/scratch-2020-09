#include <stdio.h>
#include <stdlib.h>

const long NN = 500 * 1000 * 1000; // 500 million

int
main(int _ac, char* _av[])
{
    // malloc can be estimated at O(1)
    int* xs = malloc(NN * sizeof(int)); //  2 GB
    int* ys = malloc(NN * sizeof(int)); // +2 GB 
    int* zs = malloc(NN * sizeof(int)); // +2 GB = 6 GB

    // this loop is basically free too
    for (long ii = 0; ii < NN; ++ii) {
        xs[ii] = ii;
        ys[ii] = ii;
        zs[ii] = 0;
    }
   
    // This loop is where we focus 
    for (long ii = 0; ii < NN; ++ii) {
        zs[ii] = xs[ii] + ys[ii];
        // mov xs[ii], %r9
        // mov ys[ii], %r10
        // add %r9, %r10, zs[ii]
    }

    // Time estimate 1: 
    //  - 500M adds, at 1 add/clock, is 500M clock
    //  - so 500M * 0.25 ns = 0.125 or 1/8th of a second

    // Time estimate 2:
    //  - There are actually 3 ops per iteration.
    //  - But we can do them in parallel.

    // Time estimate 3:
    //  - How long do the two loads and a store take?
    //  - We're loading 4GB, RAM throughput is 20 GB/sec
    //  - That means we'll take at least 1/5th of a second.

    // Time estimate 4:
    //  - 1 billion loads
    //  - Nothing in cache
    //  - RAM latency is 60 ns
    //  - What's 60 ns * 1 billion? = 60 s

    // Time estimate 5:
    //  - The caches operate in cache lines, or 64 B chunks of data
    //  - 64 / sizeof(int) ints per cache line = 16
    //  - 60s / 16 = 4s

    // printf is O(1)
    printf("%d\n", zs[1024]);
    printf("%d\n", zs[NN-2]);

    // free can be estimated at O(1)
    free(xs);
    free(ys);
    free(zs);
    return 0;
}
