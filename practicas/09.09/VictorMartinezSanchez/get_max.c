
#include "get_max.h"

void *getMax(void *arg) {
    int *array = (int *)arg;
    
    int i, idx=0 , max = array[0];
    for(i=1; i<TAM; ++i) {
        if(array[i] > max) {
            max = array[i];
            idx = i;
        }
    }

    //printf("Thread => Max value: %d\n", max);
    pthread_exit((void *)&array[idx]);
}
