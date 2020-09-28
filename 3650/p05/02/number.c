#include <stdio.h>

int
bad_read_int()
{
    int x;
    scanf("%d", &x);
    return x + 4;
}

int
main(int _ac, char* _av)
{
    puts("Enter a number");
    printf("We got: %d\n", bad_read_int());
}


