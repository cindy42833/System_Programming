#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

void sayHello(char *arg) {
    for(int i=0; i<1000; i++) {
        printf("Hello %s\n", arg);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t p1, p2;

    pthread_create(&p1, NULL, (void *)sayHello, "Child1");
    pthread_create(&p2, NULL, (void *)sayHello, "Child2");
    for(int i=0; i<10; i++) {
        printf("Hello parent\n");
    }
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}