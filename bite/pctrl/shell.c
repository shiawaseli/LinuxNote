#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

int main()
{
    while (1) {
        printf("user@shell>> ");
        fflush(stdout);
        char inbuf[1024] = { 0 };
        fgets(inbuf, 1023, stdin);
        inbuf[strlen(inbuf) - 1] = '\0';
        printf("command: [%s]\n", inbuf);

        int i = 0, argc = 0;
        char *argv[32] = { 0 };
        while (inbuf[i]) {
            if (!isspace(inbuf[i])) {
                argv[argc++] = &inbuf[i];
                while (inbuf[i] && !isspace(inbuf[i])) {
                    i++;
                }
                inbuf[i] = '\0';
            }
            i++;
        }
        argv[argc] = NULL;
        for (i = 0; i < argc; ++i) {
            printf("argv[%d] = [%s]\n", i, argv[i]);
        }

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
