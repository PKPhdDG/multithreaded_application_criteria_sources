#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t m;

bool check_access(const char *fname)
{
    bool value = false;
    pthread_mutex_lock(&m);
    value = access(fname, F_OK) != -1;
    pthread_mutex_unlock(&m);
    return value;
}

bool write_to_file(const char *fname, const char *data)
{
	FILE *file_handler;
    pthread_mutex_lock(&m);
	if(!(file_handler = fopen(fname, "w")))
	{
        pthread_mutex_unlock(&m);
		return false;
	}
	fprintf(file_handler, "%s", data);
	fclose(file_handler);
    pthread_mutex_unlock(&m);
    return true;    
}

void* t1f(void *args)
{
	const char *fname = (const char *)args;
    if (check_access(fname)) write_to_file(fname, "Thread 1");
	return NULL;
}

void* t2f(void *args)
{
	const char *fname = (const char *)args;
    write_to_file(fname, "Thread 2");
	return NULL;
}

int main() {
    pthread_t t1, t2;
    const char fname[] = "logfile.txt";

    pthread_create(&t1, NULL, t1f, (void *)fname);
    pthread_create(&t2, NULL, t2f, (void *)fname);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
