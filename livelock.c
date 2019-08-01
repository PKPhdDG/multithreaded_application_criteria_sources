#include <stdbool.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m, n;

volatile int i = 0;
const size_t sleep_time_s = 1;

void* t1f(void *args) {
	int r = 0;
	bool job_is_done = false;
	while(!job_is_done) {
		pthread_mutex_lock(&m);
		r=pthread_mutex_trylock(&n);
		if (r == EBUSY) {
			printf("Cannot lock mutex n in thread t1.\n");
			pthread_mutex_unlock(&m);
			sleep(sleep_time_s);
			continue;
		}
		else {
			printf("Mutex n in thread t1 is locked.\n");
			printf("Thread t1 made its jobs.\n");
			i += 1;
			job_is_done = true;
			pthread_mutex_unlock(&n);
			pthread_mutex_unlock(&m);
		}

	}
	printf("Finished job in t1 thread.\n");
	return NULL;
}

void* t2f(void *args) {
	pthread_mutex_lock(&n);
	if (i > 0) {
		printf("Thread t2 made its jobs.\n");
		pthread_mutex_unlock(&n);
	}
	else {
		printf("Thread t2 does not has a job.\n");
	}
	return NULL;
}


int main() {
    pthread_t t1, t2;
    printf("App start work with counter = %d\n", i);

    pthread_create(&t1, NULL, t1f, NULL);
    pthread_create(&t2, NULL, t2f, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("App finish work with counter = %d\n", i);
    return 0;
}


