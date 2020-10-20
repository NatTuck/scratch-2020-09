#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[])
{
    long NN = 1010010010;
    long* xs = calloc(NN, sizeof(long));

    for (long ii = 0; ii < NN; ++ii) {
        xs[ii] = (ii % 8);
    }

    for (long ii = 0; ii < NN; ++ii) {
        xs[ii] += 1;
    }
    
    long sum = 0;
    for (long ii = 0; ii < NN; ++ii) {
        sum += xs[ii];
    }
 
    free(xs);

    printf("sum = %ld\n", sum);

    return 0;
}
