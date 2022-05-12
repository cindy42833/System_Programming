#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void zombie(int num) {
    int pid;
    for(int i=0; i<num; i++) {
        pid = vfork();
        if(pid != 0) 
            // exit(0);
        // else
            continue;
    }
}

int main(int argc, char **argv) {
    int pid, num;
    num = atoi(argv[1]);
    pid = fork();
    if(pid == 0) {
        zombie(num);
        // exit(0);
    }
    else
        printf("child: %d\n", pid);
    getchar();
    return 0;
}