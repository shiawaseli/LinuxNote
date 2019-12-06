#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int pipefd[2] = { 0 };
    int ret = pipe(pipefd);
    if (ret < 0) {
        perror("pipe error");
        return -1;
    }
    int pid = fork();
    if (pid < 0) {
        perror("fork error");
        return -1;   
    } else if (pid == 0) {
        close(pipefd[0]);
        pause();
        char buf[1024] = { 0 };
        int ret = read(pipefd[0], buf, 1023);
        printf("buf[%s]-[%d]\n", buf, ret);
    } else {
        close(pipefd[0]);
        char *ptr = "今天天气好晴朗~";
        int total = 0;
        int ret = write(pipefd[1], ptr, strlen(ptr));
        total += ret;
        printf("total: %d\n", total);
    }
    /*
    while (1) {
        printf("--------%d\n", getpid());
        sleep(1);
    }
    */
    return 0;
}
