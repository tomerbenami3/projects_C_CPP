#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "search.h"

#define SIZE 100000

int main() {

    int arr[SIZE], i, index;
    int target[SIZE];

    for(i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 120000;
    }

    clock_t time1, time2, timediff;

    time1 = clock();

    for(int i = 0; i < 10000; ++i) {
        index = Search4Times(arr, SIZE, 120001);
    }

    time2 = clock();
    timediff = ((double)(time2 - time1));

    printf("time: %f\n index: %d", (double)timediff / 1000000, index);

    return 0;
}