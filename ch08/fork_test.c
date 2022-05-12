#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
    int pid;

    // for(int i=0; i<10; i++) {
    //     pid = fork();
    //     if(pid == 0) {
    //         printf("group id= %d\n", getpgrp());
    //         exit(0);
    //     }
    //     else
    //         continue;
    // }
    // if(pid != 0) {
    //     printf("parent group id= %d\n", getpgrp());
    //     getchar();
    // }
    fork();
    fork();
    // fork();
    // fork();
    pause();
    return 0;
}