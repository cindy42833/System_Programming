#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

// __thread int tls = 0;
// volatile int global=0;
atomic_int global = 0;


void thread() {
	for (int i=0; i<1000000000; i++) {
		global++;
	}
    // global += tls;
}

int main(void) {
	pthread_t id1, id2;
	pthread_create(&id1,NULL,(void *) thread, NULL);
	pthread_create(&id2,NULL,(void *) thread, NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	printf("1000000+1000000 = %d\n", global);
	return 0;
}
