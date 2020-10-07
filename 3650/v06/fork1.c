
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(int _ac, char* _av)
{
    int opid = getpid();
    int opar = getppid();
    printf("Hi, I'm %d, child of %d\n", opid, opar);

    // To create a new process
    int cpid;
    if ((cpid = fork())) {
        if (cpid < 0) {
            abort();
        }

        // we're in the parent
        int st;
        //wait(&st);
        waitpid(cpid, &st, 0);

        int pid1 = getpid();
        int par1 = getppid();
        printf("[parent] Hi, I'm %d, child of %d\n", pid1, par1);

    }
    else {
        // we're in the child
        int pid2 = getpid();
        int par2 = getppid();
        printf("[child] Hi, I'm %d, child of %d\n", pid2, par2);
    }

    printf("All done.\n");

    // We call fork once.
    // It returns twice, in two separate processes.

    // Fork copies the current process. Now we have two processes:
    //   - The parent, which we had before.
    //   - The child, which is new.

    return 0;
}
