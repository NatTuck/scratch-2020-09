#include <stdio.h>
#include <stdlib.h>

long
len(char* text)
{
    long ii = 0;
    for (; text[ii]; ++ii) {
        // do nothing
    }
    return ii;
}

int
main(int argc, char** argv)
{
    printf(
        "len(%s) = %ld\n", 
        argv[1], 
        len(argv[1])
    );
    return 0;
}
