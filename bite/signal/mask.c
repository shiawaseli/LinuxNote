#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigcb(int signum)
{
    printf("recv signum:%d\n", signum);
}

int main()
{
    signal(2, sigcb);
    signal(40, sigcb);

    // 阻塞所有信号
    sigset_t set, old;
    sigemptyset(&set); // 清空信号集合
    sigemptyset(&old);

    // 将所有的信号都添加到set集合中
    sigfillset(&set);
    //sigaddset(int signum, sigset_t *set); 将指定信号添加到set集合中
    sigprocmask(SIG_BLOCK, &set, &old); // 阻塞所有信号

    printf("press enter to continue\n");
    getchar();

    sigprocmask(SIG_UNBLOCK, &set, NULL); // 解除阻塞
    
    return 0;
}
