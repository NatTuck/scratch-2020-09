#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

// Collatz Conjecture
//
// Start with positive integer and repeat this operation:

long
iterate(long xx)
{
    if (xx % 2 == 0) {
        return xx / 2;
    }
    else {
        return xx * 3 + 1;
    }
}

// Are there any integers (> 0) we can start from, where repeated application
// of this step won't eventually reach one?
// 
// Collatz said: No

// Our question: testing all numbers 2..n, what's the odd integer
// that's visited most frequently?

long* cs_data = 0;
long cs_size = 0;

void
init_counts(long size0)
{
    cs_data = calloc(size0, sizeof(long));
    cs_size = size0;
}

void
add_count(long xx)
{
    if (xx >= cs_size) {
        // grow
        long* old_data = cs_data;
        long  old_size = cs_size;

        init_counts(xx + 2);
        for (long ii = 0; ii < old_size; ++ii) {
            cs_data[ii] = old_data[ii];
        }
        free(old_data);
    }

    cs_data[xx] += 1;
}

void
print_max_odd()
{
    long max_ii = 0;
    long max_cc = 0;
    
    printf("Size of vector: %ld\n", cs_size);

    for (long ii = 0; ii < cs_size; ++ii) {
        if (ii % 2 == 1 && cs_data[ii] > max_cc) {
            max_ii = ii;
            max_cc = cs_data[ii];
        }
    }

    printf("Max odd count at %ld: %ld\n", max_ii, max_cc);
}

void
test_collatz(long xx)
{
    //printf("Test start at %ld\n", xx);
    while (xx > 1) {
        add_count(xx);
        xx = iterate(xx);
        //printf("%d\n", xx);
    }
}

int
main(int argc, char* argv[])
{
    const long PP = 4;
    pid_t kids[PP];
    
    assert(argc == 2);
    long nn = atol(argv[1]);

    long NPP = nn / PP;

    init_counts(nn + 1);

    long i0 = 2;
    long iN = nn;

    for (long ii = i0; ii <= iN; ++ii) {
        test_collatz(ii);
    }


    print_max_odd();

    return 0;
}



