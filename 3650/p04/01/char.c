#include <stdio.h>
#include <string.h>


int
main(int argc, char* argv[])
{
    for (int ii = 0; ii < strlen(argv[1]); ++ii) {
        printf("The ascii value of char #%d (%c) is %d\n", ii, argv[1][ii], argv[1][ii]);
    }
    return 0;
}
