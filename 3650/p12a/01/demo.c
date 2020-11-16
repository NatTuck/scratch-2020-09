
#include <stdio.h>
#include <stdlib.h>

#include "xmalloc.h"


int
main(int _ac, char* _av[])
{
    long NN = 20 * 1000;
    //long NN = 100;
    long** xs = malloc(2*NN*sizeof(long*));

    for (long ii = 0; ii < 2*NN; ++ii) {
        xs[ii] = xmalloc(sizeof(long));
        xs[ii][0] = ii;
    }
   
    long sum = 0;

    for (long ii = 0; ii < NN; ++ii) {
        sum += xs[2*ii+1][0];
        xfree(xs[2*ii]);
    }
    
    for (long ii = 0; ii < NN; ++ii) {
        sum += xs[2*ii][0];
        xfree(xs[2*ii] + 1);
    }

    printf("sum = %ld\n", sum);

    return 0;
}
