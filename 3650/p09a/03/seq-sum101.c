#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

// Number of threads
const int NN = 10;

// A billion
const long TOP = 1000000000;

long sum;

int
main(int _ac, char* _av[])
{
    sum = 0;

    for (long ii = 0; ii < TOP; ++ii) {
        if (ii % 101 == 0) {
            sum += ii;
        }
    }

    printf("sum = %ld\n", sum);

    return 0;
}

