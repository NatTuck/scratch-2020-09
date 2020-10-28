#include <stdio.h>
#include <stdlib.h>

const long NN = 500 * 1000 * 1000; // 500 million

int
main(int _ac, char* _av[])
{
    int* xs = malloc(NN * sizeof(int)); //   2 GB
    int* ys = malloc(NN * sizeof(int)); //   2 GB 
    int* zs = malloc(NN * sizeof(int)); // + 2 GB = 6 GB

    for (long ii = 0; ii < NN; ++ii) {
        xs[ii] = ii;
        ys[ii] = ii;
        zs[ii] = 0;
    }

    // Focusing on this FOR loop
    for (long ii = 0; ii < NN; ++ii) {
        // mov xs[ii], %rax
        // mov ys[ii], %rcx
        // add %rax, %rcx, zs[ii]
        zs[ii] = xs[ii] + ys[ii];
    }

    printf("%d\n", zs[1024]);
    printf("%d\n", zs[NN - 4]);

    free(zs);
    free(ys);
    free(xs);
    return 0;
}
