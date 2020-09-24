
#include <stdio.h>
#include <stdlib.h>

void
hello()
{
    puts("hello");
}

int
main(int argc, char* argv[])
{
    long xx = atol(argv[1]);
    if (xx == 5) {
        hello();
    }
    return 0;
}
