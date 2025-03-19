#include <stdlib.h>
#include "mymalloc.h"


void MyMallocInit(void* _memory, size_t _memorySize) {

    if(_memory == NULL || _memorySize <= 3 * sizeof(long)) {
        return;
    }

    *(long*)_memory = _memorySize;
    *((long*)_memory + 1) = _memorySize - 3 * sizeof(long);
    *(((long*)_memory + (_memorySize / sizeof(long)) - 1)) =  0;

}

void* MyMalloc(void* _memory, size_t _requiredBlockSize) {

    if(_memory == NULL || _requiredBlockSize == 0) {
        return NULL;
    }

    _requiredBlockSize = (_requiredBlockSize + sizeof(long) - 1) & ~(sizeof(long) - 1);

    long* memptr = (long*)_memory + 1;

    while(*memptr != 0) {
        long blockSize = *memptr;
        if(blockSize > 0 && blockSize >= (long)_requiredBlockSize) {
            
            if(blockSize >= (long)_requiredBlockSize + 2 * sizeof(long)) {

                long* newBlock = memptr + 1 + (_requiredBlockSize / sizeof(long));
                *newBlock = blockSize - _requiredBlockSize - sizeof(long);

                long* newFooter = newBlock + (*newBlock / sizeof(long));
                *newFooter = *newBlock;

                *memptr = -_requiredBlockSize;
            } else {
                *memptr = -blockSize; 
            }

            return (void*)(memptr + 1);
        }

        memptr += 1 + (labs(blockSize) / sizeof(long));
    }
        return NULL;
}

void MyFree(void* myBlock) {
    if (myBlock == NULL) {
        return;
    }

    long* header = (long*)myBlock - 1;
    long blockSize = -(*header);
    *header = blockSize;

    long* footer = header + 1 + (blockSize / sizeof(long));
    *footer = blockSize;

    long* nextHeader = footer + 1;
    if (*nextHeader > 0) {
        blockSize += *nextHeader + sizeof(long);
        *header = blockSize;
        long* nextFooter = nextHeader + (*nextHeader / sizeof(long)) + 1;
        *nextFooter = blockSize;
    }

    long* prevFooter = header - 1;
    if (*prevFooter > 0) {
        long prevBlockSize = *prevFooter;
        long* prevHeader = header - (prevBlockSize / sizeof(long)) - 2;
        blockSize += prevBlockSize + sizeof(long);
        *prevHeader = blockSize;
        *footer = blockSize;
    }
}
