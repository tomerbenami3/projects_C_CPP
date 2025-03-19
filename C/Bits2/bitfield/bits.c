#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bits.h"


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

void Compress(unsigned char* name) {

    if(name == NULL) {
        return;
    }

    Bits* num;

    unsigned char temp;
    int size = strlen(name);
    int i, j;


    for(i = 0, j = 0; i < size; i+=2, ++j) {

        num = &name[j];

        if(i == size - 1) {
            num->lowBits = 0;
            num->highBits = name[i] - 'a' + 1;
            break;
        }

        num->lowBits = name[i] - 'a' + 1;
        num->highBits = name[i+1] - 'a' + 1;
        
    }

    for(i = 0; i <= j; ++i) {
        PrintBits(name[i]);
    }

}

int setBits(unsigned char x, unsigned char y, int n, int p) {

    int i;
    unsigned char mask = pow(2,n) - 1;
    unsigned char temp, invertedTemp;

    temp = y & mask;
    temp <<= p - n;

    invertedTemp = mask;
    invertedTemp <<= p - n;
    invertedTemp = ~invertedTemp;

    x &= invertedTemp;
    x |= temp;

    PrintBits(x);


    return OK;
}

int setBitsToValue(unsigned int num, int leftIndex, int rightIndex, int value) {

    unsigned char temp;
    unsigned char mask = pow(2,leftIndex - rightIndex) - 1;

    if(leftIndex < 0 || leftIndex > 31 || rightIndex < 0 || rightIndex > 31) {
        return NOT_IN_RANGE;
    }

    if(leftIndex < rightIndex) {
        return NOT_IN_RANGE;
    }

    if(value) {
        temp = mask << rightIndex;
        temp = num | temp;
        PrintBits(temp);
    } else {
        temp = mask << rightIndex;
        temp = ~temp;
        temp = num & temp;
        PrintBits(temp);
    }

    return OK;

}

int checkPairs(unsigned char num) {

    int i, counter = 0;
    unsigned char temp1 = 1;
    unsigned char temp2 = 2;
    unsigned char res1, res2;

    for(i = 0; i <= 8; i += 2) {
        
        res1 = num & temp1;
        res2 = num & temp2;

        if(res1 == res2) {
            counter++;
        }

        temp1 <<= 2;
        temp2 <<= 2;
    }

    printf("%d\n", counter);

    return 0;

}