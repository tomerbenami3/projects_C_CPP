#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sort.h"

#define OK 0
#define POINTER_ERROR 1

void swap(int* x, int* y);
void printArr(int arr[], int n);
int Partition(int* arr, int begin, int end);
void ShiftRight(int* arr, int start, int end);
int FindMin(int* arr, int size);
int* mergeSorted(int* arr1, int size1, int* arr2, int size2, int* arr);
int MergeRec(int* arr, int* temparr, int begin, int end);
int FindMax(int* arr, int size);

int bubbleSort(int* arr, int n) {

    if (arr == NULL) {
        return POINTER_ERROR;
    }

    int size = n;

    while(size > 0) {
        for(int i = 0; i < size - 1; ++i) {
            if(arr[i] > arr[i + 1]) {
               swap(arr + i, arr + i + 1);
            }
        }
        --size;
    }

    return OK;
}

int ShakeSort(int* arr, int n) {

    if (arr == NULL) {
        return POINTER_ERROR;
    }

    int size = n;

    while(size > 0) {
        for(int i = 0; i < size - 1; ++i) {
            if(arr[i] > arr[i + 1]) {
               swap(arr + i, arr + i + 1);
            }
        }
        --size;

        for(int i = size - 1; i > 0; --i) {
            if(arr[i] < arr[i - 1]) {
               swap(arr + i, arr + i - 1);
            }
        }
    }

    return OK;
}

void quickSort(int* arr, int begin, int end) {

    if (arr == NULL) {
        return;
    }
    if(begin >= end) {
        return;
    }

    int pivot_index = Partition(arr, begin, end);

    quickSort(arr, begin, pivot_index - 1);
    quickSort(arr, pivot_index + 1, end);

    return;
}

void Insertion(int* arr, int size, int unsorted_index, int gap) {

    int sorted_index;

    sorted_index = unsorted_index - gap;
        int temp = arr[unsorted_index];

        while(sorted_index >= 0 && temp < arr[sorted_index]) {
            arr[sorted_index + gap] = arr[sorted_index];
            sorted_index -= gap;
        }
        arr[sorted_index + gap] = temp;
}

void InsertionSort(int* arr, int size) {

    int unsorted_index, sorted_index;

    for(unsorted_index = 1; unsorted_index < size; ++unsorted_index) {

        Insertion(arr, size, unsorted_index, 1);
        
    }

}

void ShellSort(int* arr, int size) {

    int gap = size / 2, index;
    while(gap > 0) {

        for(index = gap; index < size; ++index) {

            Insertion(arr, size, index, gap);

        }
        gap /= 2;
    }
}

void Selection(int* arr, int size) {

    int index, min_index;

    for(index = 0; index < size; ++index) {
        min_index = FindMin(arr + index, size - index);
        swap(&arr[index], &arr[index + min_index]);
    }
}

int* CountFrequencies(int* arr, int* freqArr, int size) {

    int index;

    for(index = 0; index < size; ++index) {
        ++freqArr[arr[index]];
    }

    return freqArr;
}

int* Cumulate(int* freqArr, int* cumuArr, int size) {

    int index;

    cumuArr[0] = freqArr[0];

    for(index = 1; index < size; ++index) {

        cumuArr[index] = cumuArr[index - 1] + freqArr[index];
    }

    return cumuArr;
}

// int* PopulateOriginArr(arr, )

int* CountingSort(int* arr, int size) {

    int index;

    int* freqArr = (int*)calloc(size, sizeof(int));
    freqArr = CountFrequencies(arr, freqArr, size);

    int* cumuArr = (int*)calloc(size, sizeof(int));
    cumuArr = Cumulate(freqArr, cumuArr, size);

    int* tempArr = (int*)calloc(size, sizeof(int));

    for(index = size - 1; index >= 0; index--) {
        tempArr[cumuArr[arr[index]] - 1] = arr[index];
        cumuArr[arr[index]]--;
    }

    return tempArr;
}

int* CountRadixFrequencies(int* arr, int* freqArr, int size, int power) {

    int index;

    for(index = 0; index < size; ++index) {
        ++freqArr[(arr[index] / power) % 10];
    }

    return freqArr;
}

void CountingSortForRadix(int* arr, int size, int power) {

    int* temp = (int*)malloc(size*sizeof(int));
    int* countArr = (int*)calloc(10,sizeof(int));
    int index;

    for(index = 0; index < size; ++index) {
        ++countArr[(arr[index] / power) % 10];
    }

    for(index = 1; index < 10; ++index) {
        countArr[index] += countArr[index - 1];
    }

    for(index = size - 1; index >= 0; --index) {
        temp[countArr[(arr[index] / power) % 10] - 1] = arr[index];
        --countArr[(arr[index] / power) % 10];
    }

    for(index = 0; index < size; ++index) {
        arr[index] = temp[index];
    }

}

int CountDigits(int* arr, int size) {

    int numOfDigits = 0;

    int num = FindMax(arr, size);

    while(num != 0) {
        num /= 10;
        ++numOfDigits;
    }

    return numOfDigits;
}

int RadixSort(int* arr, int size) {

    if(arr == NULL) {
        return -1;
    }

    int max = FindMax(arr, size);

    for(int power = 1; max / power > 0; power *= 10) {
        CountingSortForRadix(arr, size, power);
    }

    return 0;
}

int MergeRec(int* arr, int* temparr, int begin, int end) {

    if(begin >= end) {
        return 1;
    }

    int mid = (end + begin) / 2;
    MergeRec(arr, temparr, begin, mid);
    MergeRec(arr, temparr, mid, end - 1);
    mergeSorted(arr + begin + 1, mid, arr + mid + begin + 1, end - mid, temparr);
    // mergeSorted(arr, mid - 1, arr, end - mid, temparr);
    printArr(temparr, end);


    return 1;
}

int MergeSortRecursive(int* arr, size_t begin, size_t end) {

    if(arr == NULL) {
        return -1;
    }

    int* tempArr = (int*)malloc(end * sizeof(int));

    if(tempArr == NULL) {
        return -1;
    }

    MergeRec(arr, tempArr, begin, end);

    return 1;

}

int FindMax(int* arr, int size) {

    int index, max = arr[0];

    for(index = 0; index < size; ++index) {
        if(arr[index] > max) {
            max = arr[index];
        }
    }
    return max;
}

int FindMin(int* arr, int size) {

    int index, min = arr[0], min_index;

    for(index = 0; index < size; ++index) {
        if(arr[index] <= min) {
            min = arr[index];
            min_index = index;
        }
    }
    return min_index;
}

void ShiftRight(int* arr, int start, int end) {

    int i;

    for(i = end; i > start; --i) {
        arr[i] = arr[i - 1];
    }
    
    return;
}

int Partition(int* arr, int begin, int end) {

    int pivot = arr[begin];
    int small_index = begin, big_index = end;


    if(end == 1) {
        return 1;
    }

    while(small_index < big_index) {


        while(arr[small_index] <= pivot) {
            ++small_index;
        }

        while(arr[big_index] > pivot) {
            --big_index;
        }

        if(small_index < big_index) {
            swap(&arr[small_index], &arr[big_index]);
        }
    }

    swap(&arr[big_index], &arr[begin]);
    
    return big_index;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void printArr(int arr[], int n) {
    for(int i = 0; i < n; ++i) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int* mergeSorted(int* arr1, int size1, int* arr2, int size2, int* arr) {

    int i, j, merge_index;

        // error check

        for(i = 0, j = 0, merge_index = 0; merge_index < size1 + size2;) {

            if(arr1[i] < arr2[j]) {
                arr[merge_index] = arr1[i];
                ++merge_index, ++i;
            } else {
                arr[merge_index] = arr2[j];
                ++merge_index, ++j;
            }

            if(i == size1) {
                for(;j < size2; ++j, ++merge_index) {
                    arr[merge_index] = arr2[j];
                }
                // printArr(arr, size1 + size2);
                break;
            }
            if(j == size2) {
                for(;i < size1; ++i, ++merge_index) {
                    arr[merge_index] = arr1[i];
                }
                // printArr(arr, size1 + size2);
                break;
            }        
        }

    return arr;
}
