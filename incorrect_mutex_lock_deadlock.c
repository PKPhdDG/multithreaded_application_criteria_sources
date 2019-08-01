#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;
pthread_mutex_t m, n;

void* t1f(void *args) {
    pthread_mutex_lock(&m);
    pthread_mutex_lock(&n);
    ++counter;
    pthread_mutex_unlock(&n);
    pthread_mutex_unlock(&m);
    return NULL;
}

void* t2f(void *args) {
    pthread_mutex_lock(&n);
    pthread_mutex_lock(&m);
    ++counter;
    pthread_mutex_unlock(&m);
    pthread_mutex_unlock(&n);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    printf("App start work with counter = %d\n", counter);

    pthread_create(&t1, NULL, t1f, NULL);
    pthread_create(&t2, NULL, t2f, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("App finish work with counter = %d\n", counter);
    return 0;
}
