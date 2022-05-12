#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
    int pid;

    pid = vfork();
    
    for(int i=0; i<10000; i++) {
        if(pid == 0)
            printf("1");
        else
            printf("2");

        if(i == 9999 && pid == 0)
            exit(0);
    }
    return 0;
}