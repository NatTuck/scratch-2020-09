#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <sys/wait.h>

void
assert_ok(long rv, char* call)
{
    if (rv == -1) {
        fprintf(stderr, "Failed call: %s\n", call);
        perror("Error:");
        exit(1);
    }
}

int
main(int _ac, char* _av[])
{
    //int* shared = mmap(0, 4096, PROT_READ|PROT_WRITE,
    //                   MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    int* shared = mmap(0, 4096, PROT_READ|PROT_WRITE,
                       MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    assert_ok((long)shared, "mmap");

    for (int ii = 0; ii < 10; ++ii) {
        shared[ii] = ii;
    }

    int cpid;
    if ((cpid = fork())) {
        printf("parent: sleep 1\n");
        sleep(1);

        printf("mutating array\n");
        for (int ii = 0; ii < 10; ++ii) {
            shared[ii] = ii * 100;
        }

        waitpid(cpid, 0, 0);
    }
    else {
        printf("child: array contents\n");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d ", shared[ii]);
        }
        printf("\n");

        sleep(2);

        printf("child: array contents\n");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d ", shared[ii]);
        }
        printf("\n");
    }

    munmap(shared, 4096);
    return 0;
}
