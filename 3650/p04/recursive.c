#include <stdio.h>

long xs[] = {1, 22, 2, 21, 3, 20, 4, 29, 5, 18, 6, 17};
long nn = 12;


// Find the maximum value in the array xs
// in array indexes i0 <= ii < i1
long
max(long* xs, long i0, long i1)
{
    if (i1 - i0 == 1) {
        return xs[i0];
    }
    
    long mid = (i0 + i1) / 2;
    long y0 = max(xs, i0, mid);
    long y1 = max(xs, mid, i1); 
    return (y0 > y1) ? y0 : y1;
}

int
main(int _ac, char* _av[])
{
    long yy = max(xs, 0, nn);
    printf("Max of array is: %ld\n", yy);
}


