#include <stdio.h>
#include <assert.h>

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int _ac, char* _av[])
{
    const long TOP = 1000000000;
    const long NPP = TOP / 10;

    printf("Summing numbers divisible by 101 from 0 to %ld\n", TOP - 1);

    long* sums = mmap(0, 10 * sizeof(long), PROT_READ|PROT_WRITE,
                     MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    pid_t kids[10];

    for (int pp = 0; pp < 10; ++pp) {
        if ((kids[pp] = fork())) {
            // parent does no work
        }
        else {
            // child, time to work
            long i0 = pp * NPP;
            long iN = i0 + NPP;

            long local_sum = 0;

            for (long ii = i0; ii < iN; ++ii) {
                if (ii % 101 == 0) {
                    local_sum += ii;
                }
            }

            sums[pp] = local_sum;

            munmap(sums, 10 * sizeof(long));
            exit(0);
        }
    }

    long global_sum = 0;

    for (int pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
        global_sum += sums[pp];
    }

    munmap(sums, 10 * sizeof(long));

    printf("Sum = %ld\n", global_sum);
    return 0;
}
