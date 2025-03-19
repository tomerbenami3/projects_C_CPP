#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__

#include <stdlib.h>

typedef unsigned char BYTE;

void MyMallocInit(void* _memory, size_t _memorySize);

void* MyMalloc(void* _memory, size_t _requiredBlockSize);

void MyFree(void* myBlock);


#endif /* __MYMALLOC_H__ */