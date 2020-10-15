#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <semaphore.h>

int
main(int _ac, char* _av[])
{
    const long TOP = 1000000000;
    const long NPP = TOP / 10;

    printf("Summing numbers divisible by 101 from 0 to %ld\n", TOP - 1);

    sem_t* lock = mmap(0, sizeof(sem_t), PROT_READ|PROT_WRITE,
                       MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sem_init(lock, 1, 1);
    long* sum = mmap(0, sizeof(long), PROT_READ|PROT_WRITE,
                     MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    // Lock rules:
    //  - Each piece of shared memory is associted with a lock.
    //  - Whenever the shared memory is accessed during concurrent execution,
    //    the lock must be in the locked state.
    //  - The lock must then be unlocked by the locking process once whatever
    //    atomic operation we're trying to do is done.
    //  - This avoids data corruption due to data races.


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
                    sem_wait(lock); // lock
                    *sum += ii;
                    sem_post(lock); // unlock
                }
            }

            munmap(sum, sizeof(long));
            munmap(lock, sizeof(sem_t));
            exit(0);
        }
    }

    for (int pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    printf("Sum = %ld\n", *sum);

    munmap(sum, sizeof(long));
    munmap(lock, sizeof(sem_t));
    return 0;
}
