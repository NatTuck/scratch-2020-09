#include <stdio.h>
#include <stdlib.h>

long
len(char* text)
{
    if (!*text) {
        return 0;
    }

    return 1 + len(text+1);
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
