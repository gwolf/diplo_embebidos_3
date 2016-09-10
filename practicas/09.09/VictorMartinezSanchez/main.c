/*
 * Victor Martinez Sanchez
 *
 */ 
#include <stdio.h>
#include <pthread.h>

#include "get_min.h"
#include "get_max.h"

#ifndef TAM
#define TAM 17
#endif


int main(int argc, char **argv) {
    int array[TAM] = {1,5,2,6,104,7,11,6,3,32,2,7,2,9,5,3,12};
    pthread_t p_thread_1, p_thread_2;

    int *max = NULL, *min = NULL;

    if(pthread_create(&p_thread_1, NULL, &getMax, (void *)&array[0])) {
        perror("Error, pthread_create");
        return -1;
    }

    if(pthread_create(&p_thread_2, NULL, &getMin, (void *)&array[0])) {
        perror("Error, pthread_create");
        return -1;
    }

    pthread_join(p_thread_1, (void **)&max);
    pthread_join(p_thread_2, (void **)&min);

    printf("The threads have finished\n");
    printf("Min value: %d\n", *min);
    printf("Max value: %d\n", *max);

    return 0;
}

