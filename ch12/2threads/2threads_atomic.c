#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

atomic_int global=0;

void thread(void) {
	int i;
	for (i=0; i<1000000; i++)
		atomic_fetch_add_explicit(&global, 1, memory_order_relaxed);
		// atomic_fetch_add(&global, 1);
}

int main(void) {
	pthread_t id1, id2;
	pthread_create(&id1,NULL,(void *) thread,NULL);
	pthread_create(&id2,NULL,(void *) thread,NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	printf("1000000+1000000 = %d\n", global);
	return 0;
}
