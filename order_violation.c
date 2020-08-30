#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m;
volatile int i = 1;

// Thread 1
void* t1f(void *args)
{

    for (int j = 0; j < 3; ++j)
    {
        pthread_mutex_lock(&m);
        switch(i) {
            case 1:
                printf("%d\n", i++);
                break;
            case 2:
                printf("%d\n", i++);
                break;
            default:
                printf("%d\n", i);
                i = 0;
        }
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

// Thread 2
void* t2f(void *args)
{
    pthread_mutex_lock(&m);
    i = 1;
    pthread_mutex_unlock(&m);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, t1f, NULL);
    pthread_create(&t2, NULL, t2f, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
