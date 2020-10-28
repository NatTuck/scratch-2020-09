#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

// .data
int stack[5];
int stptr = 0;  // the next empty slot

// (4096 - sizeof(int)) / 4 = 1023

void
stack_push(int xx)
{
    stack[stptr++] = xx;
}

int
stack_pop()
{
    return stack[--stptr];
}

int
main(int _ac, char* _av[])
{
    const int NN = 1008;

    for (int ii = 0; ii < NN; ++ii) {
        stack_push(ii);
    }

    for (int ii = 0; ii < NN; ++ii) {
        int yy = stack_pop();
        printf("%d\n", yy);
    }

    return 0;
}
