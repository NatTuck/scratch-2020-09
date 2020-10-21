
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Conjecture: For every positve integer, if we repeat this
//    iterate step enough times, we'll get to 1.

long* counts = 0;
long  counts_size = 0;

void
init_counts(long nn)
{
    counts = calloc(nn, sizeof(long));
    counts_size = nn;
}

void
record(long xx)
{
    if (xx > counts_size) {
        long* olds = counts;
        long old_nn = counts_size;
        init_counts(xx + 1);
        for (long ii = 0; ii < old_nn; ++ii) {
            counts[ii] = olds[ii];
        } 
        free(olds);
    }

    counts[xx] += 1;
}

void
print_most_common()
{
    long max_vv = 0;
    long max_cc = 0;

    for (long ii = 0; ii < counts_size; ++ii) {
        if (counts[ii] > max_cc && ii % 2 == 1) {
            max_vv = ii;
            max_cc = counts[ii];
        }
    }

    printf("Max count %ld found at %ld\n", max_cc, max_vv);
}

long
iterate(long xx)
{
    if (xx % 2 == 0) {
        return xx / 2;
    }
    else {
        return 3 * xx + 1;
    }
}

int
main(int argc, char* argv[])
{
    assert(argc == 2);
    long nn = atol(argv[1]);

    init_counts(nn + 1);

    for (long ii = 1; ii < nn; ++ii) {
        long xx = ii;
        //printf("next value = %ld\n", xx);
        do {
            record(xx);
            //printf("%ld\n", xx);
            xx = iterate(xx);
        } while (xx != 1);
    }

    print_most_common();

    return 0;
}
