#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

int global=0;

void thread(int *cnt) {
	int i;
	for (i=0; i<1000000000; i++) {
		(*cnt)++;
	}
}

int main(void) {
	pthread_t id1, id2;
    int cnt1 = 0, cnt2 = 0;
	pthread_create(&id1,NULL,(void *) thread, &cnt1);
	pthread_create(&id2,NULL,(void *) thread, &cnt2);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	printf("1000000+1000000 = %d\n", cnt1+cnt2);
	return 0;
}
