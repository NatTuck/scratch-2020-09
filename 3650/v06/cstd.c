#include <stdio.h>

int
main(int _ac, char* _av[])
{
    FILE* thing1 = fopen("/tmp/thing1.txt", "w");
    fprintf(thing1, "Hello, thing1\n");
    fclose(thing1);

    char buf[80];
    FILE* input1 = fopen("/tmp/thing1.txt", "r");
    fgets(buf, 80, input1);
    fclose(input1);

    fprintf(stdout, "%s", buf);

    return 0;
}
