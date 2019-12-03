/* server.c */ 
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

// 使用select实现并发服务
int main(void)
{
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready, client[FD_SETSIZE];
    ssize_t n;
    fd_set rset, allset;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    socklen_t cliaddr_len;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    Listen(listenfd, 20);

    maxfd = listenfd; // initialize
    maxi =-1; // index into client[] array

    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1; // -1 indicates available entry
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (; ; ) {
        rset = allset; // structure assignment
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0) 
            perr_exit("select error");

        if (FD_ISSET(listenfd, &rset)) { // new client connection
            cliaddr_len = sizeof(cliaddr);
            connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
            printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
            for (i = 0; i < FD_SETSIZE; i++)
                if (client[i] < 0) {
                    client[i] = connfd; // save descriptor
                    break;
                }
            if (i == FD_SETSIZE) {
                fputs("too many clients\n", stderr);
                exit(1);
            }
            FD_SET(connfd, &allset); // add new descriptor to set 
            if (connfd > maxfd)
                maxfd = connfd; // for select 
            if (i > maxi)
                maxi = i; // max index in client[] array
            if (--nready == 0)
                continue; // no more readable descriptors
        }
        for (i = 0; i <= maxi; i++) { // check all clients for data
            if ((sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset)) {
                if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
                    Close(sockfd); // connection closed by client 
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else {
                    int j;
                    for (j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);
                    Write(sockfd, buf, n);
                }
                if (--nready == 0)
                    break; // no more readable descriptors
            }
        }
    }
    return 0;
}

// 使用fork实现并发服务
int main2(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    pid_t pid_book[20] = { 0 };
    int i, n;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    Listen(listenfd, 20);

    printf("Accepting connections ...\n");
    while (1) {
        cliaddr_len = sizeof(cliaddr);
        for (i = 0; i < 20; i++)
        {
            if (pid_book[i] != 0)
                waitpid(pid_book[i], NULL, WNOHANG);
        }
        connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
        pid_t pid = fork();
        if (pid == -1) {
            perror("call to fork");
            exit(1);
        } else if (pid == 0) {
            Close(listenfd);
            while (1) {
                n = Read(connfd, buf, MAXLINE);
                if (n == 0) {
                    printf("the other side(%s PORT %d) has been closed.\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
                    break;
                }
                printf("received form %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
                for (i = 0; i < n; i++)
                    buf[i] = toupper(buf[i]);
                Write(connfd, buf, n);
            }
            Close(connfd);
            exit(0);
        } else {
            Close(connfd);
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

// 简单处理每次客户端的请求
int main1(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    int i, n;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    Listen(listenfd, 20);
    printf("Accepting connections ...\n");
    while (1) {
        cliaddr_len = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
        n = Read(connfd, buf, MAXLINE);
        printf("received from %s at PORT %d\n",
                inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
        for (i = 0; i < n; i++) {
            buf[i] = toupper(buf[i]);
        }
        Write(connfd, buf, n);
        Close(connfd);
    }
    return 0;
}
