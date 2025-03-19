#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "stack.h"

struct Stack
{
    Vector* m_vector;
};

int StatusConvert(VectorResult status) {

    switch(status) {
        case VECTOR_SUCCESS:
            return STACK_SUCCESS;
        case VECTOR_UNITIALIZED_ERROR:
            return STACK_UNITIALIZED_ERROR;
        case VECTOR_ALLOCATION_ERROR:
            return STACK_ALLOCATION_ERROR;
        case VECTOR_OVERFLOW:
            return STACK_OVERFLOW;
        case VECTOR_INDEX_OUT_OF_BOUNDS_ERROR:
            return STACK_IS_EMPTY;
        default:
            return -1;
    }
}


Stack* StackCreate(size_t _initialCapacity, size_t _blockSize) {
    
    Stack* sptr;

    if(_initialCapacity <= 0 && _blockSize <= 0) {
        return NULL;
    }

    sptr = (Stack*)malloc(sizeof(Stack));

    if(sptr == NULL) {
        return NULL;
    }

    sptr->m_vector = VectorCreate(_initialCapacity,_blockSize);

    return sptr;
}

void StackDestroy(Stack** _stack, void (*_elementDestroy)(void* _item)) {

    if(_stack == NULL || *_stack == NULL) {
        return;
    }
    Stack* sptr = *_stack;
    
    VectorDestroy(&sptr->m_vector,_elementDestroy);
    free(sptr);

    *_stack = NULL;
}

StackResult StackPush(Stack* _stack, void* _item) {

    if(_stack == NULL || _item == NULL) {
        return STACK_POINTER_ERROR;
    }

    int status = VectorAppend(_stack->m_vector, _item);

    return StatusConvert(status);

}

StackResult StackPop(Stack* _stack, void** _pValue) {

    if(_stack == NULL || _pValue == NULL) {
        return STACK_POINTER_ERROR;
    }

    return StatusConvert(VectorRemove(_stack->m_vector,_pValue));
}

StackResult StackTop(Stack* _stack, void** _pValue) {

    if(_stack == NULL || _pValue == NULL) {
        return STACK_POINTER_ERROR;
    }

    size_t index = VectorSize(_stack->m_vector);
    VectorGet(_stack->m_vector, index - 1, _pValue);

    return STACK_SUCCESS;
}

size_t StackSize(const Stack* _stack) {

    if(_stack == NULL) {
        return 0;
    }

    return VectorSize(_stack->m_vector);
}

size_t StackCapacity(const Stack* _stack) {

    if(_stack == NULL) {
        return 0;
    }

    return VectorCapacity(_stack->m_vector);
}

int StackIsEmpty(Stack* _stack) {

    if(_stack == NULL) {
        return 0;
    }

    size_t index = VectorSize(_stack->m_vector);

    if(index != 0) {
        return 0;
    }
    return 1;
}

size_t StackPrint(const Stack* _stack, StackElementAction _action, void* _context) {

    if(_stack == 0) {
        return 0;
    }

    VectorForEach(_stack->m_vector, _action, _context);

    return 0;
}