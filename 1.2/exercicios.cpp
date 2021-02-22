#include "pthread.h"
#include <iostream>
#define NUM_THREADS 5

void* print(void *thread_id){
    fprintf(stdout, "This is thread %i\n", (int)(size_t) thread_id);
    pthread_exit(thread_id);
}

int main(){
    // Threads vector
    pthread_t threads[NUM_THREADS];
    int status;

    // Thread return value
    void *thread_return;

    for(int i=0; i<NUM_THREADS; i++){
        fprintf(stdout, "Creating thread %i\n", i);
        status = pthread_create(&threads[i], NULL, print, (void*)(size_t) i);
        if(status!=0){
            fprintf(stdout, "Error");
            return status;
        }
    }

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], &thread_return);
        fprintf(stdout,"Finish thread %i com retorno de %i\n", i, (int)(size_t)thread_return);
    }

    return 0;
}


