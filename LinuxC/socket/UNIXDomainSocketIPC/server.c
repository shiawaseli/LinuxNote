#include "myIPC.h"
#include <ctype.h>
#include <wait.h>
#include <netinet/in.h>

#define MAXLINE 80

int main(int argc, char *argv[])
{
    int i, n, listenfd, connfd;
    pid_t pid, pid_book[20] = { 0 };
    uid_t uid = -1;
    char buf[MAXLINE];
    const char *name = "foo.socket";

    if (argc == 1)
        listenfd = serv_listen(name);
    else 
        listenfd = serv_listen(argv[1]);
    if (listenfd < 0) {
        perror("serv_listen error");
        exit(1);
    }
    while (1) {
        for (i = 0; i < 20; i++)
        {
            if (pid_book[i] != 0)
                waitpid(pid_book[i], NULL, WNOHANG);
        }
        connfd = serv_accept(listenfd, &uid);
        pid = fork();
        if (pid == 0) {
            close(listenfd);
            while (1) {
                n = read(connfd, buf, MAXLINE);
                if (n == 0) {
                    printf("the other side has been closed.\n");
                    break;
                }
                printf("received form %d\n", uid);
                for (i = 0; i < n; i++)
                    buf[i] = toupper(buf[i]);
                write(connfd, buf, n);
            }
            close(connfd);
            exit(0);
        } else if (pid < 0) {
            perror("fork error");
            exit(1);
        } else {
            close(connfd);
            for (i = 0; i < 20; i++)
            {
                if (pid_book[i] == 0)
                    break;    
            }
            pid_book[i] = pid;
        }
    }

    return 0;
}
