#include <stdio.h>
#include <pthread.h>

#define NUM_OF_THREADS 100

int g_glob = 0;

void* printFunc(void* tid) {

    int local = 0;

    for(int i = 0; i < 100; i++) {
        g_glob++;
        local++;
    printf("Thread number %d, global: %d, Local: %d\n", *(int*)tid, g_glob, local);
    }


    pthread_exit(tid);

    return tid;
}

int main() {

    pthread_t threads[NUM_OF_THREADS];
    int i, status;
    int arrAddress[100];

    for(i = 1; i <= 100; ++i) {
        arrAddress[i] = i;
    }


    for(i = 0; i < NUM_OF_THREADS; ++i) {

        pthread_create(&threads[i], NULL, &printFunc, arrAddress + i);
    }

    for(i = 0; i< NUM_OF_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}