#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
    fork();
    fork();
    getchar();
    return 0;
}
