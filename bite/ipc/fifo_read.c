#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main()
{
    umask(0);
    char *file = "./test.fifo";
    int ret = mkfifo(file, 0664);
    if (ret < 0 && errno != EEXIST) {
        perror("mkfifo error");
        return -1;
    }
    printf("create fifo success\n");
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        perror("open error");
        return -1;
    }
    printf("open fifo success\n");
    while (1) {
        char buf[1024] = { 0 };
        ret = read(fd, buf, 1023);
        if (ret < 0) {
            perror("read error");
            return -1;
        } else if (ret == 0) {
            printf("all write close\n");
            return -1;
        }
        printf("buf:[%s]\n", buf);
    }
    close(fd);
    return 0;
}
