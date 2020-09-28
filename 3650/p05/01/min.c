
#include <stdio.h>

int xs[] = {10, 100, 2, 90, 3, 180, 4, 70, 5};
int nn = 10;


// Return the smallest number in the array
// in index range i0 <= ii < i1.
int
min(int* xs, int i0, int i1)
{
    if (i1 - i0 == 1) {
        return xs[i0];
    }

    int mid = (i0 + i1) / 2; // truncate = round down
    int y0 = min(xs, i0, mid);
    int y1 = min(xs, mid, i1);
    return (y0 < y1) ? y0 : y1;
}

int
main(int _ac, char* _av[])
{
    int yy = min(xs, 0, nn);
    printf("yy = %d\n", yy);
    return 0;
}

