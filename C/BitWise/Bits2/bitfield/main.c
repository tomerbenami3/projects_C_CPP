#include <stdio.h>
#include "bits.h"

int main() {

    unsigned char x = 170;
    unsigned char y = 167;
    int n = 3, p = 6;

    unsigned char name[] = "abcde";

    Compress(name);

    // setBits(x,y,n,p);
    // setBitsToValue(170,6,3,0);
    // checkPairs(98);

    return 0;
}
