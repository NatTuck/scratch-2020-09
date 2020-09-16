#include <stdio.h>
#include <stdlib.h>

void
countdown(long xx)
{
    printf("%ld\n", xx);

    if (xx > 0) {
        countdown(xx - 1);
    }
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("bad usgae");
        return 1;
    }

    long xx = atol(argv[1]);
    countdown(xx);
    return 0;
}
