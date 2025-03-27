# 🔢 Sorting Algorithms in C

This project provides implementations of multiple classic **sorting algorithms** in C. It is intended for educational purposes, algorithm comparison, and practical use in sorting integer arrays. Both simple and efficient algorithms are included — from Bubble Sort to Radix Sort.

---

## 🧠 Included Sorting Algorithms

| Function | Description |
|----------|-------------|
| `bubbleSort()` | Classic Bubble Sort |
| `ShakeSort()` | Bidirectional version of Bubble Sort (Cocktail Sort) |
| `quickSort()` | Recursive Quick Sort |
| `InsertionSort()` | Insertion Sort |
| `ShellSort()` | Shell Sort (gap-based insertion) |
| `Selection()` | Selection Sort |
| `CountingSort()` | Non-comparison counting sort (integers only) |
| `MergeSortRecursive()` | Recursive Merge Sort |
| `RadixSort()` | Radix Sort (base-10, non-comparison) |

---

## ➕ Utilities

| Function | Description |
|----------|-------------|
| `printArr()` | Prints an array of integers |
| `mergeSorted()` | Merges two sorted arrays into one |
| `CountingSortForRadix()` | Helper for digit-wise counting in Radix Sort |
| `CountRadixFrequencies()` | Generates digit frequency array for a given power |

---

## 🧪 Example Usage

```c
#include "sort.h"

int main() {
    int arr[] = {9, 2, 5, 1, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, size - 1);
    printArr(arr, size);

    return 0;
}
