#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

int num_thread;
long total_loopcount;
double global_hit=0.0;
pthread_mutex_t mutex;
long volatile hit[16], loopcount[16];
int idx = 0, first_ctrl = 0;
struct timeval record;

void sighandler(int signum){
    long cur_hit = 0, cur_loopcount = 0;
    struct timeval cur;
    gettimeofday(&cur, NULL);

	for (int i=0; i<num_thread; i++) {
        cur_hit += hit[i];
        cur_loopcount += loopcount[i];
    }
	printf("%ld\n", sizeof(long volatile));
    double pi = (double)4*((double)cur_hit/cur_loopcount);
	printf("hit: %ld, loop: %ld, pi = %.8lf\n", cur_hit, cur_loopcount,pi);

    if(first_ctrl == 0) {
        record = cur;
        first_ctrl = 1;
    }
    else {
        struct timeval diff;
        timersub(&cur, &record, &diff);
        double time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
		printf("time used: %lf\n", time_used);
        if(time_used < 0.5) 
            _exit(0);
        else
            record = cur;
    }
}

void thread(void* rand_buffer) {
	double point_x,point_y;
	long local_loopcount = total_loopcount/num_thread;
	double rand_d;

	pthread_mutex_lock(&mutex);
	volatile long* local_hit = &hit[idx];
    volatile long* cur_loopcount = &loopcount[idx++];
	pthread_mutex_unlock(&mutex);

	for(long i=0;i<local_loopcount;i++) {	
		drand48_r(rand_buffer, &rand_d);
		point_x = rand_d;
		drand48_r(rand_buffer, &rand_d);
		point_y = rand_d;
		if( (point_x*point_x + point_y*point_y) < 1.0)
			*local_hit += 1;
        *cur_loopcount += 1;
	}
	printf("hit = %ld\n", *local_hit);
	pthread_mutex_lock(&mutex);
	global_hit += *local_hit;
	pthread_mutex_unlock(&mutex);
}


void main(int argc,char*argv[]) {
	pthread_t id[16];
	struct drand48_data* rand_buffer[16];
	double rand_d;

	total_loopcount=atol(argv[1]);
	num_thread=atoi(argv[2]);
	assert(num_thread <= 16);

	signal(SIGINT, sighandler);

	pthread_mutex_init(&mutex,NULL);	
	for(int i=0;i<num_thread;i++) {
		/*使用aligned_alloc分配記憶體，避免false sharing*/
		/*在這個例子中，「剛好」用malloc也會得到相同效果*/
		rand_buffer[i] = aligned_alloc(64, sizeof(struct drand48_data));
		srand48_r(rand(), rand_buffer[i]);
		drand48_r(rand_buffer[i], &rand_d);
		printf("@buffer = %p\n", rand_buffer[i]);
		printf("thread%d's seed = %f\n", i, rand_d);
		pthread_create(&id[i],NULL,(void *)thread,rand_buffer[i]);
	}

	for(int i=0;i<num_thread;i++)
		pthread_join(id[i],NULL);

	double pi = (double)4*(global_hit/total_loopcount);
	printf("pi = %.8lf\n",pi);
}