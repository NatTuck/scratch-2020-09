
#include <stdio.h>

int
main(int _argc, char* _argv[])
{
    long xs[] = {1, 2, 3, 4};
    long nn = 4;

    long sum = 0;
    for (long ii = 0; ii < nn; ++ii) {
        //sum += xs[ii];
        //sum += *(xs + ii);   // memory address xs + sizeof(xs[0])*ii
        //sum += *(ii + xs);
        sum += ii[xs];
    }

    printf("%ld\n", sum);

    return 0;
}
