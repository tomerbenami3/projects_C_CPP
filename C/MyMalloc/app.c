#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void MyMallocInit(void* _memory, size_t _memorySize);
void* MyMalloc(void* _memory, size_t _requiredBlockSize);
void MyFree(void* myBlock);

#define MEMORY_SIZE 1024

int main() {
    char memory[MEMORY_SIZE];

    MyMallocInit(memory, MEMORY_SIZE);

    void* block1 = MyMalloc(memory, 100);
    void* block2 = MyMalloc(memory, 200);
    void* block3 = MyMalloc(memory, 150);

    printf("Block1: %p\n", block1);
    printf("Block2: %p\n", block2);
    printf("Block3: %p\n", block3);

    MyFree(block2);
    printf("Block2 freed.\n");

    MyFree(block3);
    printf("Block3 freed. Adjacent free blocks should coalesce.\n");

    MyFree(block1);
    printf("Block1 freed. Entire memory should now be a single free block.\n");

    void* block4 = MyMalloc(memory, 400);
    printf("Block4: %p\n", block4);

    return 0;
}
