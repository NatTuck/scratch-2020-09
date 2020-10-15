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

    long* sum = mmap(0, sizeof(long), PROT_READ|PROT_WRITE,
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

            for (long ii = i0; ii < iN; ++ii) {
                if (ii % 101 == 0) {
                                //   sum = 100
                                //   proc 1 (ii = 5)          proc 2 (ii = 15)
                    *sum += ii; // mov (sum), %tmp (100)
                                //                            mov (sum), %tmp (100)
                                // add %ii, %tmp (105)
                                //                            mov %ii, %tmp (115)
                                // mov %tmp, (sum) (105)
                                //                            mov %tmp, (sum) (115)
                                //  result: 100 + 5 + 15 = 115
                }
            }

            munmap(sum, sizeof(long));
            exit(0);
        }
    }

    for (int pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    printf("Sum = %ld\n", *sum);

    munmap(sum, sizeof(long));
    return 0;
}
