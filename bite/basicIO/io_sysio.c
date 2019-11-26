#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    // umask 设置文件的创建权限掩码，决定了文件的默认权限
    // 给定权限 & ~掩码
    umask(0);
    // 有可能新建文件，一定要指定文件权限
    int fd = open("./test.txt", O_RDWR | O_CREAT, 0777);
    if (fd < 0) {
        perror("open error");
        return -1;
    }

    char *ptr = (char*)"天已经黑了！";
    int ret = write(fd, ptr, strlen(ptr));
    if (ret < 0) {
        perror("write error");
        return -1;
    }
    printf("write len: %d\n", ret);
   
    lseek(fd, 0, SEEK_SET);

    char buf[1024] = { 0 };
    ret = read(fd, buf, strlen(ptr));
    if (ret < 0) {
        perror("read error");
        return -1;
    } else if (ret == 0) {
        perror("at end of file");
        return -1;
    }
    printf("read buf : [%s]-[%d]\n", buf, ret);

    close(fd);
    return 0;
}

/*
 * open() 必选项:
 *
 * O_RDONLY 只读打开
 * O_WROMLY 只写打开
 * O_RDWR   可读可写打开
 *
 * open() 可选项:
 * 
 * O_CREAT  文件不存在则创建新文件，存在则打开
 * O_EXCL   跟O_CREAT同时使用，若文件不存在则创建，已存在则报错
 * O_TRUNC  打开文件同时截断文件
 * O_APPEND 写入数据时追加在文件末尾
 * 
 * fopen() 中：
 * w+: O_RDWR | O_CREAT | O_TRUNC
 * a+: O_RDWR | O_CREAT | O_APPEND
 *
 */ 

