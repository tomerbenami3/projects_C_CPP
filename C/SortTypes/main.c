#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "sort.h"


#define SIZE 10


int main() {

    int arr[SIZE], i, marr[SIZE];
    int target[SIZE];

    for(i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 1000;
        // marr[i] = rand() % 30;
    }

    clock_t time1, time2, timediff;
    
    // time1 = clock();
    // printArr(arr,SIZE);
    // quickSort(arr, 0 , SIZE - 1);
    // ShiftRight(arr, 2, 5);
    // InsertionSort(arr, SIZE);
    // ShellSort(arr, SIZE);
    // FindMin(arr, SIZE);
    // Selection(arr, SIZE);
    // CountingSort(arr,SIZE);
    printArr(arr,SIZE);
    // printArr(marr, SIZE);
    // MergeSortRecursive(arr, 0, SIZE);
    // InsertionSort(arr,SIZE);
    // InsertionSort(marr,SIZE);
    // mergeSorted(arr, SIZE, marr, SIZE, target);
    RadixSort(arr, SIZE);
    printArr(arr,SIZE);
    // time2 = clock();
    // timediff = ((double)(time2 - time1));
    
    // printf("time: %f", (double)timediff / CLOCKS_PER_SEC);


    return 0;
}