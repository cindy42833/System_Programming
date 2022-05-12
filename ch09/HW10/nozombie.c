#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void ZombieGen(int factor) {
    int cpid = fork();
    if(cpid == 0) {
        sleep(factor);
        exit(0);
    }
}

int main() {
    for(int i=1; i<=100; i++) {
        int pid = fork();
        if(pid == 0) {
            printf("%d: child\n", i);          
            sleep(i);
            exit(0);
        }
        else if(pid > 0) {
            int child_status;
            printf("%d: wait\n", i);          
            wait(&child_status);  
            printf("%d: end wait\n", i);  
        }
    }
    return 0;
}