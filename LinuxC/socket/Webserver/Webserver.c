#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <wait.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 200
#define SERV_PORT 8000
#define WEB_PATH "/var/tmp"

int server(int connfd)
{
    int i, j, n, fd;
    char path[MAXLINE], http[MAXLINE], buf[MAXLINE], contentType[MAXLINE];

    printf("server starting\n");
    while (1) {
        n = read(connfd, buf, MAXLINE);
        if (n == 0) {
            printf("other side has been closed.\n");
            break;
        }
        if (n > 2 && buf[0] == 'G' && buf[1] == 'E' && buf[2] == 'T') {
            for (i = 3; i < n && buf[i] == ' '; )
                i++;
            for (j = 0; i < n && buf[i] != ' '; )
                buf[j++] = buf[i++];
            buf[j] = '\0';
            for (; i < n && buf[i] == ' '; )
                i++;
            for (j = 0; i < n && !isspace(buf[i]); )
                http[j++] = buf[i++];
            http[j] = '\0';
            if (strcmp(buf, "/") == 0)
                sprintf(path, "%s/index.html", WEB_PATH);
            else 
                sprintf(path, "%s%s", WEB_PATH, buf);
            if (strstr(path, "jpg") != NULL)
                sprintf(contentType, "image/jpg");
            else if (strstr(path, "png") != NULL)
                sprintf(contentType, "image/png");
            else 
                sprintf(contentType, "text/html");
            fd = open(path, O_RDONLY);
            if (fd > 0) {
                sprintf(buf, "%s 200 OK\r\nContent-Type: %s\r\n\r\n", http, contentType);
                write(connfd, buf, sizeof(buf));
                while ((n = read(fd, buf, MAXLINE)) > 0) {
                    write(connfd, buf, n);
                }
            } else {
                sprintf(buf, "%s 404 Not Found\r\nContent-Type: %s\r\n\r\n", http, contentType);
                write(connfd, buf, sizeof(buf));
                sprintf(buf, "<html><body>request file not found</body></html>\r\n");
                write(connfd, buf, sizeof(buf));
            }
            sprintf(buf, "FIN\n");
            write(connfd, buf, strlen(buf));
            close(fd);
        }
    }
    return 0;
}

int main(void)
{
    pid_t pid;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
   
    listen(listenfd, 20);
    while (1) {
        cliaddr_len = sizeof(cliaddr);
        connfd =  waitpid(-1, NULL, WNOHANG);
        if (connfd > 0)
        {
            close(connfd);
            printf("close connfd parent\n");
        } 
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
        pid = fork();
        if (pid < 0) {
            printf("fork error");
            exit(1);
        } else if (pid == 0) {
            close(listenfd);
            server(connfd);
            close(connfd);
            exit(0);
        }
    }
    return 0;
}
