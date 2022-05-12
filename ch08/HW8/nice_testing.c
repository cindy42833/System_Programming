#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

long long int count = 0;

void alarmHandler() {
    printf("count: %lld\n", count);
    exit(0);
}

int main() {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    int ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);

    if(ret == -1) {
        perror("Error");
        exit(0);
    }
    else {
        int pid = fork();

        if(pid > 0) {
            nice(5);
        }

        signal(SIGALRM, alarmHandler);
        alarm(10);
        while (1) {
            count++;
        }
    }

    return 0;
}