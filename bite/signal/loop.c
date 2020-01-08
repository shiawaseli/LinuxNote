#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    // int kill(pid_t pid, int signum);
    // kill(getpid(), SIGQUIT);
    // 
    // raise(SIGTERM);
    // 
    abort();
    //
    // alarm(3);

    while (1) {
        printf("hello\n");
        sleep(1);
    }
    return 0;
}
