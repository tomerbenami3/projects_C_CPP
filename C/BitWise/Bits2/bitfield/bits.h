#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OK 1;
#define NOT_IN_RANGE 1;

typedef struct {
    unsigned char highBits: 4;
    unsigned char lowBits: 4;
}Bits;


void Compress(unsigned char* name);

int setBits(unsigned char x, unsigned char y, int n, int p);

int setBitsToValue(unsigned int num, int leftIndex, int rightIndex, int value);

int checkPairs(unsigned char num);