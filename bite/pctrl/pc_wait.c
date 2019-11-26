#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid= fork();

    if (pid < 0) {
        perror("fork error");
    } else if (pid == 0) {
        printf("child %d\n", getpid());
        sleep(10);
        exit(2);
    }
    //WIFEXITED(status):查看进程是否正常退出
    //WEXITSTATUS(status):查看进程退出码
    //wait(NULL);
    int retval;
    int ret = waitpid(-1, &retval, 0);

    if (ret < 0) {
        perror("waitpid error");
    } else if (ret == 0) {
        printf("have no child exist\n");
    } else {
        printf("pid: %d child exit\n", ret);
        if ((retval & 0x7f) == 0) {
            printf("return val = %d\n", (retval >> 8) & 0xff);
        } else {
            printf("sig code : %d\n", retval & 0x7f);
        }   
    }
    while (1) {
        printf("打麻将~~\n");
        sleep(1);
    }
    return 0;
}
