
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>

// Conjecture: For every positve integer, if we repeat this
//    iterate step enough times, we'll get to 1.

long
max(long aa, long bb)
{
    return aa > bb ? aa : bb;
}

long
min(long aa, long bb)
{
    return aa < bb ? aa : bb;
}

sem_t lock;
long  fd = 0;
long* counts = 0;
long* counts_size = 0;

void*
calloc_shared_grow(size_t count, size_t nn)
{
    if (counts_size) {
        int mypid = getpid();
        printf("growing shared mem: %ld => %ld (%d)\n", *counts_size, count*nn, mypid);
    }

    void* ys = mmap(0, nn * count, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    memset(ys, 0, nn * count);
    return ys;
}

void*
calloc_shared(size_t count, size_t nn)
{
    void* ys = mmap(0, nn * count, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    memset(ys, 0, nn * count);
    return ys;
}


void
free_shared(void* ptr, size_t count, size_t nn)
{
    munmap(ptr, nn*count);
}

void
init_counts(long nn)
{
    fd = open("/tmp/shared_mem", O_RDWR|O_CREAT|O_TRUNC, 0644);
    assert(fd != -1);
    ftruncate(fd, nn * sizeof(long));
    counts = calloc_shared_grow(nn, sizeof(long));
    counts_size = calloc_shared(1, sizeof(long));
    *counts_size = nn;
}

void
grow_counts(long nn)
{
    ftruncate(fd, nn * sizeof(long));
    counts = calloc_shared_grow(nn, sizeof(long));
    *counts_size = nn;
}

void
record(long xx)
{
    sem_wait(&lock);
    if (xx > *counts_size) {
        long* olds = counts;
        long old_nn = *counts_size;
        grow_counts(xx + 1);
        for (long ii = 0; ii < old_nn; ++ii) {
            counts[ii] = olds[ii];
        } 
        free_shared(olds, old_nn, sizeof(long));
    }
    sem_post(&lock);

    counts[xx] += 1;
}

void
print_most_common()
{
    long max_vv = 0;
    long max_cc = 0;

    for (long ii = 3; ii < *counts_size; ++ii) {
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

void
child_labor(long i0, long i1)
{
    for (long ii = i0; ii < i1; ++ii) {
        long xx = ii;
        //printf("next value = %ld\n", xx);
        do {
            record(xx);
            //printf("%ld\n", xx);
            xx = iterate(xx);
        } while (xx != 1);
    }
}

int
main(int argc, char* argv[])
{
    sem_init(&lock, 1, 1);

    assert(argc == 2);
    long nn = atol(argv[1]);

    const long PP = 4;
    pid_t kids[PP];

    long WPP = nn / PP;

    init_counts(nn + 1);

    for (long pp = 0; pp < PP; ++pp) {
        if ((kids[pp] = fork())) {
            // parents don't do work
        }
        else {
            long i0 = max(1, WPP*pp);
            long i1 = min(i0 + WPP, nn);

            child_labor(1, nn);
            exit(0);
        }
    }
    
    for (long pp = 0; pp < PP; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    print_most_common();

    return 0;
}
