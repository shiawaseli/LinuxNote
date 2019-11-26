#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    } 
    char *env[3];
    env[0] = "MYVAL=2019";
    env[1] = NULL;
    //execl("/bin/ls", "ls", "-l", NULL);
    //execlp("ls", "-l", NULL);
    //execle("/bin/ls", "ls", "-l", NULL, env);
    
    char *arg[3];
    arg[0] = "ls";
    arg[1] = "-l";
    arg[2] = NULL;
    //execv("/bin/ls", arg);
    //execvp("ls", arg);
    //execvpe("ls", arg, env);
    
    execve("/bin/ls", arg, env);
    printf("hello !!\n");
    
    return 0;
}
