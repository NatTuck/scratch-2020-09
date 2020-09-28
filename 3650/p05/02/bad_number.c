#include <stdio.h>

int*
bad_read_int()
{
    int x;
    //scanf("%d", &x);
    x = good_read_int();
    return &x;
}

// Caller must free returned memory
int*
good_read_int()
{
    int* x = malloc(sizeof(int));
    scanf("%d", x);
    return x;
}


int
main(int _ac, char* _av)
{
    puts("Enter a number");
    printf("We got: %d\n", bad_read_int());
}


