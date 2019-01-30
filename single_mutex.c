#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;
pthread_mutex_t m;

void* t1f(void *args) {
    int i;
    for (i=0; i<1000000; i++) 
    {
        pthread_mutex_lock(&m);
        ++counter;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    pthread_t t1;
    printf("App start work with counter = %d\n", counter);

    pthread_create(&t1, NULL, t1f, NULL);
    
    pthread_join(t1, NULL);
    printf("App finish work with counter = %d\n", counter);
    return 0;
}
