#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main()
{
    while (1) {
        printf("username@PC>> ");
        char inbuf[1024];
        fgets(inbuf, 1023, stdin);
        inbuf[strlen(inbuf) - 1] = '\0';
        printf("input = [%s]\n", inbuf);
        
        int argc = 0;
        char *pstr = inbuf, *argv[32] = { 0 };
        while (*pstr != '\0') {
            if (!isspace(*pstr)) {
                argv[argc++] = pstr;
                while (*pstr != '\0' && !isspace(*pstr)) {
                    pstr++;
                }
                *pstr = '\0';
            }
            pstr++;
        }
        argv[argc] = NULL;

        pid_t pid = fork();
        if (pid < 0) {
            continue;
        } else if (pid == 0) {
            execvp(argv[0], argv);
            exit(1);
        }
        wait(NULL);
    }
    return 0;
}
