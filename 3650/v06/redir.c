
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

int
main(int _ac, char* _av[])
{
    int cpid;
    if ((cpid = fork())) {
        assert(cpid != -1);
        // parent
        waitpid(cpid, 0, 0);
        printf("%d: child done\n", getpid());
    }
    else {
        // child
        int fd = open("/tmp/stdout.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
        assert(fd == 3);

        close(1);
        dup(fd);  // copy the stdout.txt fd into slot 1, making it stdout for
                  // this process
        close(fd);

        execlp("echo", "echo", "executed", "echo", NULL);

        // For redirect input:
        //  - open something for reading
        //  - close(0)
        //  - dup the thing
    }

    return 0;
}
