#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 8000
#define MAXLINE 200

int main()
{
    int n, connfd;
    struct sockaddr_in servaddr;
    char buf[MAXLINE], input[MAXLINE];

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connfd < 0) {
        perror("socket error");
        exit(1);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);

    connect(connfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    while (fgets(input, MAXLINE, stdin) != NULL) {
        input[strlen(input) - 1] = '\0';
        if (input[0] != '/')
        {
            printf("please input /...\n");
            continue;
        }
        memset(buf, 0, MAXLINE);
        sprintf(buf, "GET %s HTTP/1.1\r\n\r\n", input);
        write(connfd, buf, strlen(buf));
        n = read(connfd, buf, MAXLINE);
        if (n == 0)
            printf("the other side has been closed.\n");
        else 
            printf("%s\n", buf);
    }
    printf("??????? %s ?????????\n", input);
    close(connfd);
    return 0;
}
