#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigcb(int signum)
{
    pid_t pid;
    // 若没有子进程退出，则waitpid返回0
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        printf("delete %d\n", pid);
}

int main()
{
    signal(SIGCHLD, sigcb);
    pid_t pid = fork();
    if (pid == 0) {
        printf("I am child%d\n", getpid());
        sleep(5);
        exit(0);
    }
    
    if (fork() == 0) {
        int cnt = 0;
        while (cnt++ < 10) {
            printf("I am child%d\n", getpid());
            sleep(1);
        }
        exit(0);
    }

    while (1) {
        printf("打一桌麻将\n");
        sleep(1);
    }

    return 0;
}
