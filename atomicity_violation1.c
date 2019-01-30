#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

const size_t num=24;
const size_t NUM_OF_THREADS=5;
static volatile size_t divided_by=4;
pthread_mutex_t m;

struct thread_args{ size_t num_of_thread; int *res; size_t divided_by; bool has_result; };

void *t1f(void *args)
{
    struct thread_args *ta=(struct thread_args*)(args);
    int res;

    if(divided_by)
    {
        pthread_mutex_lock(&m);
        printf("Thread number: %ld\n", ta->num_of_thread);
        res=num/divided_by;
        printf("%ld : %ld = %d\n", num, divided_by, res);
        ta->res[ta->num_of_thread]=res;
        ta->divided_by=divided_by--;
        ta->has_result=true;
        printf("=============================================\n");
        pthread_mutex_unlock(&m);
    }    
}

int main()
{
    struct thread_args threads_args[NUM_OF_THREADS];
    pthread_t threads[NUM_OF_THREADS];
    int res[NUM_OF_THREADS];
    for(size_t i=0; i<NUM_OF_THREADS; ++i)
        res[i]=0;

    for(size_t i=0; i<NUM_OF_THREADS; ++i)
    {
        threads_args[i].num_of_thread=i;
        threads_args[i].res=res;
        threads_args[i].has_result=false;
        pthread_create(&threads[i], NULL, t1f, (void*)(threads_args+i));
    }
    for(size_t i=0; i<NUM_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Results threads work\n");
    for(size_t i=0; i<NUM_OF_THREADS; ++i)
    {
        if (threads_args[i].has_result)
            printf("In thread %ld: %ld : %ld  = %d\n", i, num, threads_args[i].divided_by, res[i]);
    }
    return 0;
}
