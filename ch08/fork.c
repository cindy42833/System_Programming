#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int pid, var = 0;

    printf("%d", var);
    pid = fork();
    if(pid == 0)
        var = 1;
    else
        var = 2;
    printf("%d\n", var);
    return 0;
}