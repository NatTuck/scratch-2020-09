#include <stdio.h>
#include <stdlib.h>

/*
 *     5 => 16 => 8 => 4 => 2 => 1
 *     7 => 22 => 11 => 34 => 17 => 52 => 26 => 13 => 40 => 20 => 10 => 5 ^
 *
 *     Three possibilities for the input:
 *       - Cycles at 1    <= conjecture is that all positve integers do this
 *       - Cycles at some values above 1
 *       - Grows forever
 */

long
iterate(long xx)
{
    if (xx % 2 == 0) {
        return xx/2;
    }
    else {
        return xx*3 + 1;
    }
}

int
main(int argc, char* argv[])
{
    long xx = atol(argv[1]);
    long ii = 0;

    while (xx > 1) {
        printf("%ld\n", xx);
        xx = iterate(xx);
        ii++;
    }

    printf("ii = %ld\n", ii);
    return 0;
}
