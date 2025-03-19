#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

void printArr(int arr[], int n);

int Add(int a, int b) {
    return a + b;
}

int bubbleSort(void* arr,int element_size, int n, Criteria func) {

    if (arr == NULL || func == NULL) {
        return POINTER_ERROR;
    }
    char* aptr = arr;
    void* temp = (void*)malloc(element_size);

    int size = n;

    while(size > 0) {
        for(size_t i = 0; i < size - 1; i++) {
            if(func(aptr + i*element_size, aptr + i*element_size + element_size)) {
               swap(aptr + i*element_size, aptr + i*element_size + element_size, element_size, temp);
            }
        }
        --size;
    }
    printArr(arr,n);

    return OK;
}

void printArr(int arr[], int n) {
    for(int i = 0; i < n; ++i) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void swap(void* x, void* y, int element_size, void* temp) {
    memcpy(temp,x,element_size);
    memcpy(x, y,element_size);
    memcpy(y,temp,element_size);
}