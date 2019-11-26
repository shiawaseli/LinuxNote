#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main()
{
    while (1) {
        printf("username@localhost>> ");
        fflush(stdout);
        char cmd_buf[1024] = { 0 };
        fgets(cmd_buf, 1023, stdin);
        cmd_buf[strlen(cmd_buf) - 1] = '\0';
        printf("cmd: [%s]\n", cmd_buf);
        
        int argc = 0;
        char *ptr = cmd_buf, *argv[32] = { 0 };
        while (*ptr != '\0') {
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
            execvp(argv[0], argv);
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}
