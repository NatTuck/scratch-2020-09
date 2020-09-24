
#include <stdio.h>

typedef int (*main_type)(int, char**);

long xs[] = {1, 2, 3, 4, 5, 6};
short ys[] = {0, 1};

int
main(int argc, char* argv[])
{
    main_type mp = main;

    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("sizeof(short) = %ld\n", sizeof(short));
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(long) = %ld\n", sizeof(long));
    printf("sizeof(long long) = %ld\n", sizeof(long long));
    printf("\n");
    printf("sizeof(char*) = %ld\n", sizeof(char*));
    printf("sizeof(long*) = %ld\n", sizeof(long*));
    printf("sizeof(void*) = %ld\n", sizeof(void*));
    printf("\n");
    printf("sizeof(main) = %ld\n", sizeof(main));
    printf("sizeof(mp) = %ld\n", sizeof(mp));
    printf("sizeof(void) = %ld\n", sizeof(void));

    printf("\n");
    long* xsp = xs;
    printf("xsp = %p\n", xsp);
    printf("*xsp = %ld\n", *xsp);
    printf("xsp + 3 = %p\n", xsp + 3);
    printf("*(xsp + 3) = %ld\n", *(xsp + 3));

    void* vp = xs;
    printf("vp = %p\n", xsp);
    printf("*((long*)vp) = %ld\n", *((long*)vp));
    printf("vp + 8 = %p\n", vp + 8);
    printf("*((long*)(vp + 8)) = %ld\n", *((long*)(vp+8)));
    printf("*((long*)(vp + 12)) = %ld\n", *((long*)(vp+12)));

    printf("\n");
    void* svp = ys;
    printf("*((short*)(svp + 1)) = %ld\n", *((short*)(svp+1)));
    return 0;
}

//short ys[] = {0, 1};
//sizeof(short) = 2
//4 bytes
//[2 bytes: 0] [2 bytes: 1]
//     [ what?s here ]
//
//[ 0 ] [ 0 ] [ 1 ] [ 0 ]
//
//[least sig] [most sig]
//
// Intel-type processors store bytes in "Little-Endian"
// Storing bytes in the other order is "Big-Endian"
//
//
// Benefit to little-endian
//
// [ 7 ] [ 0 ] [ 0 ] [ 0 ]  = (int)(7)
//   ^
// cast to (short*)
// [ 7 ] [ 0 ]
//   ^
