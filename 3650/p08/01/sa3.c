#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

void*
malloc_shared(size_t size)
{
    return mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
}

void
free_shared(void* ptr, size_t size)
{
    munmap(ptr, size);
}

int
main(int argc, char* argv[])
{
    long NN = 1010010010;
    long QQ = NN / 4;

    long* xs = malloc_shared(NN * sizeof(long));
    //long* sum = malloc_shared(sizeof(long));
    //*sum = 0;

    long PP = 4;
    pid_t kids[PP];

    for (long pp = 0; pp < PP; ++pp) {
        if ((kids[pp] = fork())) {
            // parent does nothing
        }
        else {
            long i0 = pp*QQ;
            long iN = (pp==3) ? NN : i0+QQ;

            long sum = 0;

            for (long ii = i0; ii < iN; ii += 1) {
                xs[ii] = (ii % 8);
            }

            for (long ii = i0; ii < iN; ii += 1) {
                xs[ii] += 1;
            }

            for (long ii = i0; ii < iN; ii += 1) {
                // Here's our problem.
                sum += xs[ii];
                //*sum += xs[ii]; // three operations: load, add, store
            }

            // Child is done
            /*
            free_shared(sum, NN*sizeof(long));
            free_shared(xs, sizeof(long));
            */

            printf("sum in %ld is %ld\n", pp, sum);
            exit(0);
        }
    }

    for (long pp = 0; pp < PP; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    //printf("sum = %ld\n", *sum);
            
    //free_shared(sum, NN*sizeof(long));
    //free_shared(xs, sizeof(long));

    return 0;
}
