#include <stdio.h>
#include <pthread.h>

static volatile int counter_for_t1f = 0;
static volatile int counter_for_t2f = 0;
pthread_mutex_t m;

void* t1f(void *args) {
    int i;
    for (i=0; i<1000000; i++) 
    {
        pthread_mutex_lock(&m);
        ++counter_for_t1f;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void* t2f(void *args) {
    int i;
    for (i=0; i<1000000; i++) 
    {
        pthread_mutex_lock(&m);
        ++counter_for_t2f;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    printf("App start work with counter = %d in thread t1\n", counter_for_t1f);
    printf("App start work with counter = %d in thread t2\n", counter_for_t2f);

    pthread_create(&t1, NULL, t1f, NULL);
    pthread_create(&t2, NULL, t2f, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("App finish work with counter = %d in thread t1\n", counter_for_t1f);
    printf("App finish work with counter = %d in thread t2\n", counter_for_t2f);
    return 0;
}
