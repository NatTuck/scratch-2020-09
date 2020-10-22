#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

// Conditoins for a data race:
//  - Shared memory
//  - Multple / concurrent processes
//  - Write to the shared memory

long max(long aa, long bb) { return aa > bb ? aa : bb; }
long min(long aa, long bb) { return aa < bb ? aa : bb; }

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

sem_t* lock;
int    cs_fd   = 0;
long*  cs_data = 0;
long*  cs_size = 0;

void
init_counts(long size0)
{
    lock = mmap(0, size0*sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sem_init(lock, 1, 1);

    cs_fd = open("/tmp/shared1", O_CREAT|O_TRUNC|O_RDWR, 0644);
    assert(cs_fd != -1);
    ftruncate(cs_fd, size0*sizeof(long));

    cs_data = mmap(0, size0*sizeof(long), PROT_READ|PROT_WRITE, MAP_SHARED, cs_fd, 0);

    cs_size = mmap(0, sizeof(long), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *cs_size = size0;
}

void
grow_counts(long size1)
{
    long* old_data = cs_data;
    long  old_size = *cs_size;
    
    munmap(old_data, old_size*sizeof(long));
    
    ftruncate(cs_fd, size1*sizeof(long));
    cs_data = mmap(0, size1*sizeof(long), PROT_READ|PROT_WRITE, MAP_SHARED, cs_fd, 0);
    *cs_size = size1;
}

void
add_count(long xx)
{
    sem_wait(lock);
    if (xx >= *cs_size) {
        grow_counts(xx + 2);
    }
    sem_post(lock);

    cs_data[xx] += 1;
}

void
print_max_odd()
{
    long max_ii = 0;
    long max_cc = 0;
    
    printf("Size of vector: %ld\n", *cs_size);

    for (long ii = 0; ii < *cs_size; ++ii) {
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

    for (long pp = 0; pp < PP; ++pp) {
        if ((kids[pp] = fork())) {
            // parents don't do work
        }
        else {
            long i0 = max(2, NPP*pp);
            long iN = min(NPP*(pp+1), nn);

            for (long ii = i0; ii <= iN; ++ii) {
                test_collatz(ii);
            }

            exit(0);
        }
    }
    
    for (long pp = 0; pp < PP; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    print_max_odd();

    return 0;
}



