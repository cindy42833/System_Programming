#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void ZombieGen() {
    for(int i=0; i<10; i++) {
        int cpid = fork();
        if(cpid == 0) {
            char *agv[] = {"ls", "-alh", "/", NULL};
            execvp("ls", agv);
            exit(0);
        }
        else
            continue; 
    }
}

int main() {
    
    int pid = fork();

    if(pid == 0) {
        ZombieGen();
    }
    getchar();

    return 0;
}