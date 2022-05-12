#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int n_fork=0;
    int pid;

    pid=vfork();
    if (pid==0) {
        execlp("ls", "ls", "-R", "/", NULL);
    }
    else {
        int status;
        while(1) {
            printf("parent\n");
        }
        wait(&status);
    }
        
    return 0;
}