#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>    
#include <sys/wait.h>
int main() {
        int wstatus;
        char *const lsargv[] = { "ls", "-R", "/", NULL };
        pid_t pid;
        pid = fork();
        if (pid == 0) {  // child
                printf("child(%d): pgid=%d, parent=%d\n",getpid(), getpgrp(), getppid());
                getchar();
                execvp(lsargv[0], lsargv);
        } else {
                wait(&wstatus);
        }
        return 0;
}