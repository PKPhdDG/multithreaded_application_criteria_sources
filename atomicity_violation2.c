#include <stdio.h>
#include <pthread.h>

static volatile size_t thread_num;

struct thread_args{ size_t num_of_thread; };

void *t1f(void *args)
{
    thread_num++;
    struct thread_args *ta=(struct thread_args*)(args);
    printf("Thread number: %ld\n", ta->num_of_thread);
    printf("Is run as: %ld\n", thread_num);
    printf("=============================================\n");
}

int main()
{
    const size_t NUM_OF_THREADS=5;
    struct thread_args threads_args[NUM_OF_THREADS];
    pthread_t threads[NUM_OF_THREADS];
    size_t sum;

    for(size_t i=0; i<NUM_OF_THREADS; ++i)
    {
        threads_args[i].num_of_thread=i;
        pthread_create(&threads[i], NULL, t1f, (void*)(threads_args+i));
    }
    for(size_t i=0; i<NUM_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
