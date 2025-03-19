#define OK 0
#define SIZE_ERROR 1
#define POINTER_ERROR 2

typedef struct {
    char name[20];
    int age;
}Person;

/*
description: a pointer to a function
input: 2 integers
output: int - true or false
error: by implementation*/
typedef int(*Criteria)(void* first, void* second);

/*
description: sort by a generic criteria
input: array, size of the array, pointer to a function
output: status
error: by implementation*/
int bubbleSort(void* arr,int element_size, int n, Criteria func);

void swap(void* x, void* y, int element_size, void* temp);