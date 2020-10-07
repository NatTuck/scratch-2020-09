
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
    //printf("Hi, I'm %d, child of %d\n", opid, opar);

    printf("Before fork\n");

    // To create a new process
    int cpid;
    if ((cpid = fork())) {
        if (cpid < 0) {
            abort();
        }

        puts("in parent, concurrent with child");

        // we're in the parent
        int st;
        wait(&st);

        puts("in parent, after child");
    }
    else {
        // we're in the child
        execlp("echo", "echo", "In", "subprocess", NULL);
        printf("after exec\n");
    }

    printf("All done.\n");

    // We call fork once.
    // It returns twice, in two separate processes.

    // Fork copies the current process. Now we have two processes:
    //   - The parent, which we had before.
    //   - The child, which is new.

    return 0;
}
