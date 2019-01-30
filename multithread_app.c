#include <stdio.h>
#include <pthread.h>

static volatile int balance = 0;

void* deposit(void *args) {
    // Block B
    int i;
    for (i=0; i<1000000; i++) 
    // Block C
    {
        ++balance; // Place with uncontrolled access. Race condition place.
    }
    // Endblock C
    return NULL;
    // Endblock B
}

int main() {
    // Block A
    pthread_t p1, p2;
    printf("App start work with balance = %d\n", balance);

    pthread_create(&p1, NULL, deposit, NULL);
    pthread_create(&p2, NULL, deposit, NULL);
    // Endblock A

    // Block D
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("App finish work with balance = %d\n", balance);
    return 0;
    // Endblock D
}
