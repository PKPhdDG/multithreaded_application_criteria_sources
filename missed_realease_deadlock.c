#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;
pthread_mutex_t m;

void* t1f(void *args) {
    pthread_mutex_lock(&m);
    ++counter;
    pthread_mutex_unlock(&m);
    return NULL;
}

void* t2f(void *args) {
    pthread_mutex_lock(&m);
    int i = *((int*)args);

    if (i) {
        ++counter;
        pthread_mutex_unlock(&m);
    }
    else {
        counter += 2;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    printf("App start work with counter = %d\n", counter);
    int t2arg = 0;

    pthread_create(&t1, NULL, t1f, NULL);
    pthread_create(&t2, NULL, t2f, &t2arg);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("App finish work with counter = %d\n", counter);
    return 0;
}
