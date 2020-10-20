#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>

int
main(int argc, char* argv[])
{
    const long NN = 1000;
    const long PP = 1;

    uint8_t* nums = mmap(0, NN*NN, PROT_READ|PROT_WRITE, 
            MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    pid_t kids[PP];

    for (long pp = 0; pp < PP; ++pp) {
        if ((kids[pp] = fork())) {
            // parent does nothing
        }
        else {
            // fixme
            for (long ii = 2 + pp; ii < NN; ii += PP) {
                for (long jj = 2; jj < (NN * NN); ++jj) {
                    if (jj != ii && jj % ii == 0) {
                        //printf("%ld is not prime, because %ld\n", jj, ii);
                        if (nums[jj] < 100) {
                            nums[jj] += 1;
                        }
                    }
                }
            }
    
            munmap(nums, NN*NN);
            exit(0);
        }
    }


    for (long pp = 0; pp < PP; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    long count = 0;
    long csum = 0;
    for (long ii = 2; ii < (NN * NN); ++ii) {
        csum = (csum + nums[ii]) % 1024;
        if (nums[ii] == 0) {
            count += 1;
        }
    }

    printf("There are %ld primes < %ld.\n", count, NN * NN);
    printf("Checksum = %ld.\n", csum);

    munmap(nums, NN*NN);
    return 0;
}

