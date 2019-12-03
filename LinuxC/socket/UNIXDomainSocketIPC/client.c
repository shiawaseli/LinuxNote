#include "myIPC.h"
#include <netinet/in.h>

#define MAXLINE 80

int main(int argc, char *argv[])
{
    int connfd, n;
    char buf[MAXLINE];
    const char *name = "foo.socket";

    if (argc == 1)
        connfd = cli_conn(name);
    else 
        connfd = cli_conn(argv[1]);
    if (connfd < 0) {
        perror("cli_conn error");
        exit(1);
    }
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        write(connfd, buf, strlen(buf));
        n = read(connfd, buf, MAXLINE);
        if (n == 0)
        {
            printf("the server has been closed.\n");
            break;
        }
        printf("received: %s", buf);
    }

    return 0;
}
