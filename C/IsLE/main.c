#include <stdio.h>

int IsLE() {

    int num = 5;
    unsigned char* p = (unsigned char*)&num;
    p += 1;
    
    printf("%d\n", *p);
    printf("%p\n", p);

    return 1;

}


int main() {

    int i = 5;

    IsLE();
    return 0;
}