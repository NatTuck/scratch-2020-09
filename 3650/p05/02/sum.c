#include <stdio.h>

int DATA[] = {1,2,3,4,5,6};
int SIZE = 6;


int
sum_array(int* xs, int nn)
{
    if (nn == 0) {
        return 0;
    }

    if (nn == 1) {
        return xs[0];
    }

    int mid = nn / 2;
    int y0 = sum_array(xs, mid);
    int y1 = sum_array(xs + mid, nn - mid);
    return y0 + y1;
}

int
main(int _ac, char* _av[])
{
    int sum = sum_array(DATA, SIZE);
    printf("%d\n", sum);
    return 0;
}
