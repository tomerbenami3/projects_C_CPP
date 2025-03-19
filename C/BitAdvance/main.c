#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void Swap(unsigned char* _a, unsigned char* _b);
static void PrintBits(unsigned char num);
static void BuildLUTReverse(unsigned char* _count);
static unsigned char ReverseBits(unsigned char _num);
static int FindOffsetThirdBit(unsigned char _num);


void countBits(unsigned char num) {

    int i, counter = 0;

    for(i = 0; i < 8; ++i) {
        if (num & ( 1 << i)) {
            counter++;
        }
    }
    printf("%d are on\n", counter);
}

int ReverseBitsWithLUT(int _num) {

    static unsigned char count[256];
    static unsigned char flag;
    unsigned char *partition;

    if(!flag) {
        BuildLUTReverse(count);
        flag = 1;
    }

    partition = (unsigned char*)&_num;
    Swap(&count[partition[0]], &count[partition[3]]);
    Swap(&count[partition[1]], &count[partition[2]]);

    return _num;
}

int FindThirdLUT(unsigned int _num) {

    static int flag;
    static unsigned char globArr[255];
    static char* partition;

    if(!flag) {
        BuildThirdLUT(globArr);
        flag = 1;
    }

    return _num;
}

int main() {

    int number = 7, res;
    // int res = ReverseBitsWithLUT(number);
    // PrintBits(number);
    // PrintBits(res);
    res = FindOffsetThirdBit(number);
    printf("%d", res);

}

static int FindOffsetThirdBit(unsigned char _num) {

    int index, size = sizeof(unsigned char) * 8;
    unsigned char temp, mask = 1;
    int count = 0;


    for(index = 0; index < size; ++index) {
        
        count += mask & (_num >> index);
    
        if(count == 3) {
            return count;
        }
    }

    return -1;
}

static int FindOffsetThirdBitforLUT(unsigned char _num, int* _retindex, int* _prevCount) {

    int index, size = sizeof(int)*8;
    unsigned char temp, mask = 1;
    int count = 0;


    for(index = 0; index < size; ++index) {
        
        _prevCount += mask & (_num >> index);
    
        if(_prevCount == 3) {
            return count;
        }
    }

    return -1;
}

static void Swap(unsigned char* _a, unsigned char* _b) {
    unsigned char temp = *_a;
    *_a = *_b;
    *_b = temp;
}

static void BuildLUTReverse(unsigned char* _count) {

    unsigned char res = 0;
    int index;

    for(index = 0; index < 256; ++index) {
        _count[index] = ReverseBits(index);
    }
}

static unsigned char ReverseBits(unsigned char _num) {

    unsigned char index, temp, res = 0;

    for(index = 0; index < 8; ++index) {

        temp = 1 & (_num >> index);
        res |= temp;
        res <<= 1;
    }

    return res;
}

static void PrintBits(unsigned char num) {

    int i;

    for(i = 31; i >= 0; --i) {
        if(num & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}