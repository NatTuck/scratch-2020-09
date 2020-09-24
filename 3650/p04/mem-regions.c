
#include <stdio.h>
#include <stdlib.h>

long global_int = 7;

int
main(int argc, char* argv[])
{
    long local_int = 14;

    long* heap_int = malloc(sizeof(long));
    *heap_int = 29;

    printf("main is\t%p\n", main);
    printf("&global_int is\t%p\n", &global_int);
    printf("&local_int is\t%p\n", &local_int);
    printf("heap_int is\t%p\n", heap_int);

    free(heap_int);
    return 0;
}
