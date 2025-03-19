#include <stdio.h>
#include <stdlib.h>

int func2() {

    printf("In func2\n");
    exit(1);
}

void func1(int a, int b, int c, int d, int e, int f, int g) {

    printf("In func1\n");

    long* ptr;
    ptr = &g;
    --ptr;
    *ptr = (long)func2;

    return;
}

int main() {
    printf("in Main\n");
    func1(1, 2, 3, 4, 5, 6, 7);
    printf("After func1\n");

    return 0;
}