#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    while (1) {
        printf("username@localhost>> ");
        fflush(stdout);
        char cmd_buf[1024] = { 0 };
        fgets(cmd_buf, 1023, stdin);
        cmd_buf[strlen(cmd_buf) - 1] = '\0';
        printf("cmd: [%s]\n", cmd_buf);
        
        int argc = 0, relocate_flag = 0;
        char *ptr = cmd_buf, *argv[32] = { 0 };
        char *filename_in = NULL, *filename_out = NULL;
        while (*ptr != '\0') {
            if (*ptr == '>') {
                relocate_flag = 1;
                ptr++;
                if (*ptr == '>') {
                    relocate_flag = 2;
                    ptr++;
                }
                while (isspace(*ptr) && *ptr != '\0') {
                    ptr++;
                }
                filename_out = ptr;
                while (!isspace(*ptr) && *ptr != '\0') {
                    ptr++;
                }
                *ptr = '\0';
                ptr++;
            } else if (*ptr == '<') {
                relocate_flag |= 4;
                ptr++;
                while (isspace(*ptr) && *ptr != '\0') {
                    ptr++;
                }
                filename_in = ptr;
                while (!isspace(*ptr) && *ptr != '\0') {
                    ptr++;
                }
                *ptr = '\0';
                ptr++;
            }
            if (!isspace(*ptr)) {
                argv[argc++] = ptr;
                while (!isspace(*ptr) && *ptr != '\0') {
                    ptr++;
                }
                *ptr = '\0';
            }
            ptr++;
        }
        argv[argc] = NULL;

        pid_t pid = fork();
        if (pid < 0) {
            continue;
        } else if (pid == 0) {
            printf("flag = %d, filename_in = %s, filename_out = %s\n", relocate_flag, filename_in, filename_out);
            umask(0);
            if (relocate_flag & 0x1) {
                 int fd = open(filename_out, O_WRONLY | O_CREAT | O_TRUNC, 0766);
                 if (fd < 0) {
                     perror("open file_out error");
                     exit(1);
                 }
                 dup2(fd, 1);
            } else if (relocate_flag & 0x2) {
                int fd = open(filename_out, O_WRONLY | O_CREAT | O_APPEND, 0766);
                if (fd < 0) {
                    perror("open file_out error");
                    exit(1);
                }
                dup2(fd, 1);
            }
            if (relocate_flag & 0x4) {
                int fd = open(filename_in, O_RDWR | O_CREAT, 0766);
                if (fd < 0) {
                    perror("open file_in error");
                    exit(1);
                }
                dup2(fd, 0);
            }
            execvp(argv[0], argv);
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}
