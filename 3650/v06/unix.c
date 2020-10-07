#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int _ac, char* _av[])
{
    int thing2 = open("/tmp/thing2.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    char* msg = "Hello, Thing2\n";
    write(thing2, msg, strlen(msg));
    close(thing2);

    char buf[80];
    int input2 = open("/tmp/thing2.txt", O_RDONLY /* don't care about third arg*/);
    int len = read(input2, buf, 80);
    close(input2);
    buf[len] = 0;

    write(1, buf, strlen(buf));

    return 0;
}
