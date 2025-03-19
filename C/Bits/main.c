#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countBits(unsigned char num) {

    int i, counter = 0;

    for(i = 0; i < 8; ++i) {
        if (num & ( 1 << i)) {
            counter++;
        }
    }
    printf("%d are on\n", counter);
}

void countBitsint(unsigned int num) {

    int i, counter = 0;

    for(i = 0; i < sizeof(unsigned int) * 8; ++i) {
        if (num & ( 1 << i)) {
            counter++;
        }
    }
    printf("%d are on\n", counter);
}

void PrintBits(unsigned char num) {

    int i;

    for(i = 7; i >= 0; --i) {
        if(num & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

unsigned char Invert(unsigned char num) {
    
    int y = ~num;
    PrintBits(y);
    PrintBits(num);
    return 0;
}

void RotateBin(unsigned char num, int rotate) {

    unsigned char temp, mask = 1;

    for(int i = 0; i < rotate; ++i) {
        temp = num & mask;
        temp <<= 7;
        num >>= 1;
        num += temp;
    }
    PrintBits(num);
}

void Compress(unsigned char* name) {

    if(name == NULL) {
        return;
    }

    unsigned char temp;
    int size = strlen(name);
    int i, k = 0;

    // name[size] &= 0;

    for(i = 0; i < size; i+=2) {

        if(i == size - 1) {
            temp = name[i] - 'a' + 1;
            temp <<= 4;
            temp &= 0xf0;
            name[k++] = temp;
            break;
        }

        temp = name[i] - 'a' + 1;
        temp <<= 4;
        temp += name[i+1] - 'a' + 1;
        name[k++] = temp;
    }

    // PrintBits(temp);
// i = 6, k = 3, size = 5
    // if(size % 2 != 0) {
    //     name[k] = name[k] & 240;
    // }

    printf("\n");

    for(i = 0; i < k; ++i) {
    PrintBits(name[i]);
    }
}



int main() {

    unsigned char num = 213;
    unsigned int num2 = 321;
    unsigned char name[] = "abcde";

    countBits(num);

    // countBitsint(num2);

    // Invert(num);
    // PrintBits(num);
    // RotateBin(num,3);

    Compress(name);

    return 0;
}