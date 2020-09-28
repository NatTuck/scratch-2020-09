#include <string.h>
#include <stdio.h>   // sprintf

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int _argc, char* _argv[])
{
    char intro[] = "lines in msg.txt:\n";
    write(1, intro, strlen(intro));

    int fd = open("msg.txt", 0);

    char rd_buf[192];
    long sz = read(fd, rd_buf, 192);

    long lines = 0;
    for (long ii = 0; ii < sz; ++ii) {
        if (rd_buf[ii] == '\n') {
            lines += 1;
        }
    }

    char wr_buf[64];
    long msg_sz = sprintf(wr_buf, "lines = %ld\n", lines);

    write(1, wr_buf, msg_sz);
    return 0;
}
