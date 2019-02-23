#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;
pthread_mutex_t m;

void* t1f(void *args) {
    int i = *((int*)args);
    while(i--) {
        pthread_mutex_lock(&m);
        ++counter;
    }
    pthread_mutex_unlock(&m);
    return NULL;
}

int main() {
    pthread_t t1;
    printf("App start work with counter = %d\n", counter);
    int t1arg = 100;

    pthread_create(&t1, NULL, t1f, &t1arg);
    
    pthread_join(t1, NULL);
    printf("App finish work with counter = %d\n", counter);
    return 0;
}
