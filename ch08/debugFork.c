#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int pid, waiting = 1;

    pid = fork();

    if(pid == 0) {
        while (waiting)
            ;
        printf("child");
    }
    else {
        printf("child's pid = %d\n", pid);
        printf("parent");
    }
    return 0;
}