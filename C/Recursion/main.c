#include <stdio.h>
#include <string.h>
#include <math.h>

int CalcPow(int n, int k) {

    if(k == 0) {
        return 1;
    }

    return CalcPow(n, k - 1) * n;
}

int SumArray(int arr[], int size) {

    if(size == 0) {
        return 0;
    }

    return SumArray(arr, size - 1) + arr[size - 1];
}

int AvgArray(int arr[], int size) {

    if(size == 1) {
        return arr[size];
    }

    return ((AvgArray(arr, size - 1) * size + arr[size]) / size);
}

int FindMax(int arr[], int size) {

    if(size == 1) {
        return arr[size];
    }

    int x = FindMax(arr, size - 1);

    if(x > arr[size]) {
        return x;
    } else {
        return arr[size];
    }
}

int Fibonacci(int n) {

    if(n <= 0) {
        return 0;
    }

    if(n == 1) {
        return 1;
    }

    int temp;

    temp = Fibonacci(n - 1) + Fibonacci(n - 2);

    return temp;
}

void swap(char* x, char* y) {
    char temp = *x;
    *x = *y;
    *y = temp;

    return;
}

int FiboIteratio(int n) {

    int i, temp;

    int n0 = 0, n1 = 1;

    while(i < n) {
        temp = n0 + n1;
        n0 = n1;
        n1 = temp;
        i++;
    }

    return temp;
}

char* ReverseStringRec(char* str, int size) {

    if(size <= 0) {
        return str;
    }

    char temp = str[0];
    str[0] = str[size - 1];
    str[size - 1] = temp;

    ReverseStringRec(str + 1, size - 2);


    return str;
}

int IsPalindrum(char num[], int size) {

     if(size <= 0) {
        return 0;
     }

    if(num[0] != num[size - 1]) {
        return 1;
    }

    return IsPalindrum(num + 1, size - 2);
}

void PrintMove(char from, char to, int n) {
    printf("move %d from %c to %c", n, from, to);
}

void Hanoi (int n, char from, char to, char via) {

    if(n == 1) {
        PrintMove(from, to, 1);
    }

    Hanoi(n-1, from, via, to);
    PrintMove(from, to, n);
    Hanoi(n-1, via, to, from);

}

int main() {

    int x;
    int arr[] = {1, 2, 3, 4, 5, 9};
    char str[] = "123456";
    int size_str = strlen(str);
    char palindrum[] = "12321";
    int size_palindrum = strlen(palindrum);

    
    // char* newstr = ReverseStringRec(str, size_str);
    // int IsPali = IsPalindrum(palindrum, size_palindrum);

    // printf("%d\n", IsPali);
    

    // x = CalcPow(5, 4);

    x = AvgArray(arr, 5);
    // x = FindMax(arr, 5);
    // x = Fibonacci(6);
    // x = FiboIteratio(6);
    printf("%d", x);

    return 0;
}