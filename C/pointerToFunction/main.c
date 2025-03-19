#include <stdio.h>
#include <string.h>
#include "sort.h"

static int CRT1(void* first, void* second) {

        if(*((int*)first) > *((int*)second)) {
            return 1;
        }
        else {
            return 0;
        }
    }

static int CRT2(void* first, void* second) {

        Person* p1, *p2;

        p1 = (Person*)first;
        p2 = (Person*)second;

        if(strcmp(p1->name, p2->name) > 0) {
            return 1;
        }
        else {
            return 0;
        }
    }

static int CRT5(void* first, void* second) {

        if(*((double*)first) > *((double*)second)) {
            return 1;
        }
        else {
            return 0;
        }
    }

int SumOfDigits(int num) {
    int temp, sum = 0;

    while(num > 0) {
        temp = num % 10;
        sum = sum + temp;
        num /= 10;
    }

    return sum;
}

static int CRT3(int first, int second) {

        first = SumOfDigits(first);
        second = SumOfDigits(second);

        if(first > second) {
            return 1;
        }
        else {
            return 0;
        }
    }

int countBits(unsigned char num) {

    int i, counter = 0;

    for(i = 0; i < 8; ++i) {
        if (num & ( 1 << i)) {
            counter++;
        }
    }

    return counter;
}

static int CRT4(int first, int second) {

        first = countBits(first);
        second = countBits(second);

        if(first > second) {
            return 1;
        }
        else {
            return 0;
        }
    }

int main() {

    int arr[] = {82,8,5,6,11,1,19,4,21,7};
    double doublearr[] = {82,8,5,6,11,1,19,4,21,7};

     Person people[5] = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35},
        {"Diana", 40},
        {"Eve", 45}
    };

    int (*funcPointer) (void* arr, int element_size, int size, Criteria func);
    funcPointer = bubbleSort;

    funcPointer(arr,sizeof(int), 10, CRT1);
    funcPointer(doublearr, sizeof(double), 10, CRT5);
    // funcPointer(people, sizeof(Person), 5, CRT2);

    // for(int i = 0; i < 5; i++) {
    //     printf("%s, %d --",people[i].name, people[i].age);
    // }

    return 0;
}
