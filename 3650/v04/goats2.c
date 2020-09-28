
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct goat {
   char* name;
   float mass;  // kilos
} goat;

goat
make_goat(const char* name, float mass)
{
    goat gg;
    gg.name = strdup(name);
    gg.mass = mass;
    return gg;
}

goat
copy_goat(goat gg0)
{
    goat gg1 = gg0;
    gg1.name = strdup(gg0.name);
    return gg1;
}

void
cleanup_goat(goat* gg)
{
    free(gg->name);
}

goat
fattest_goat(goat* xs, long nn)
{
    assert(nn != 0);
    goat fattest = xs[0];
    for (long ii = 1; ii < nn; ++ii) {
        if (fattest.mass < xs[ii].mass) {
            fattest = xs[ii];
        }
    }
    return copy_goat(fattest);
}

int
main(int _ac, char* _av[])
{
    goat herd[4];
    herd[0] = make_goat("Alice", 50);
    herd[1] = make_goat("Bob", 75);
    herd[2] = make_goat("Carol", 60);
    herd[3] = make_goat("Dave", 55);

    goat gg = fattest_goat(herd, 4);

    printf("The fattest goat is %s\n", gg.name);
    herd[1].name[0] = 'R';
    printf("The fattest goat is %s\n", gg.name);


    for (long ii = 0; ii < 4; ++ii) {
        cleanup_goat(&(herd[ii]));
    }

    cleanup_goat(&gg);
    return 0;
}
