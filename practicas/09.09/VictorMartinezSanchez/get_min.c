
#include "get_min.h"

void *getMin(void *arg) {
    int *array = (int *)arg;

    int i, idx=0 , min = array[0];
    for(i=1; i<TAM; ++i) {
        if(array[i] < min) {
            min = array[i];
            idx = i;
        }
    }

    //printf("Thread => Min value: %d\n", min);
    pthread_exit((void *)&array[idx]);
}
