#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

volatile int r1 = 0;
pthread_mutex_t m;

void* deposit(void *args) {

    for (int i=0; i<10; i++)
    {
        pthread_mutex_lock(&m);
        ++r1;
        pthread_mutex_unlock(&m);
        usleep(100);
        pthread_mutex_lock(&m);
        printf("%d\n", r1);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    printf("App start work with r1 = %d\n", r1);

    pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, deposit, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("App finish work with r1 = %d\n", r1);
    return 0;
}
