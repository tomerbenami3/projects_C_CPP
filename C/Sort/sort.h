#ifndef __SORT_H__
#define __SORT_H__

/// @brief bubble sort
/// @param arr , array
/// @param n , size of array
/// @return , sorted array.
int bubbleSort(int* arr, int n);

/// @brief shake sort
/// @param arr array
/// @param n size of array
/// @return sorted array
int ShakeSort(int* arr, int n);

/// @brief quick sort
/// @param arr array
/// @param begin start index
/// @param end end index, size of the array
void quickSort(int* arr, int begin, int end);

/// @brief Insertion Sort
/// @param arr array
/// @param size size
void InsertionSort(int* arr, int size);

/// @brief Shell sort
/// @param arr array
/// @param size size of the array
void ShellSort(int* arr, int size);

/// @brief Selection sort
/// @param arr array
/// @param size size of the array
void Selection(int* arr, int size);

int* CountingSort(int* arr, int size);

int MergeSortRecursive(int* arr, size_t begin, size_t end);

void printArr(int arr[], int n);

int* mergeSorted(int* arr1, int size1, int* arr2, int size2, int* arr);

int RadixSort(int* arr, int size);

void CountingSortForRadix(int* arr, int size, int power);

int* CountRadixFrequencies(int* arr, int* freqArr, int size, int power);

#endif