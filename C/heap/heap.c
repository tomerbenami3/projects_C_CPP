#include <stdlib.h>
#include <stdbool.h>
#include "../Vectornew/vector.h"
#include "heap.h"

#define COMPARE _heap->_pfLess
#define VECTOR _heap->m_vec
#define HEAP_SIZE _heap->m_heapSize

struct Heap {
    Vector* m_vec;
    size_t m_heapSize;
    LessThanComparator _pfLess;
};

HeapResultCode ConvertEnum(VectorResult _vector);
static void Swap(void* x, void* y);
static void VectorElementSwap(Vector *_vec, int _index1, int _index2);

int Heapify(Heap* _heap, int index) {

    Vector* vptr = VECTOR;
    
    void *father, *left, *right;

    VectorGet(vptr, index, &father);
    VectorGet(vptr, index*2 + 1, &left);
    VectorGet(vptr, index*2 + 2, &right);

    int status = COMPARE(left,right);

    if(status > 0 && COMPARE(left, father)) {
        VectorElementSwap(_heap->m_vec,index,index*2 + 1);
        return 1;
    }
    else if (status <= 0 && COMPARE(right, father)) { 
        VectorElementSwap(_heap->m_vec,index ,index*2 + 2);
        return -1;
    }
    
    return 0;
}

Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess) {

    if(_vector == NULL || _pfLess == NULL) {
        return NULL;
    }
    
    Heap* heap = (Heap*)malloc(sizeof(Heap));

    if(heap == NULL) {
        return NULL;
    }

    heap->m_vec = _vector;
    heap->m_heapSize = VectorSize(_vector);
    heap->_pfLess = _pfLess;

    int heapIndex;

    for(heapIndex = heap->m_heapSize / 2 ; heapIndex > 0; --heapIndex) { // start heapify from downest father, to the root
        Heapify(heap, heapIndex - 1); // (heapIndex-1) -> to brake the loop in 0 index, (due to use of size_t) 
    }

    return heap;
}

Vector* HeapDestroy(Heap** _heap) {

    if(_heap == NULL || *_heap == NULL) {
        return NULL;
    }

    Vector* vptr;
    Heap* h = *_heap;

    vptr = h->m_vec;
    free(h);

    *_heap = NULL;

    return vptr;
}

HeapResultCode HeapInsert(Heap* _heap, void* _element) {

    if(_heap == NULL) {
        return HEAP_NOT_INITIALIZED;
    }

    if(_element == NULL) {
        return ITEN_NOT_INITIALIZED;
    }
    Vector* vptr = VECTOR;
    void *father, *son;

    int status = ConvertEnum(VectorAppend(vptr,_element));

    if (status != HEAP_SUCCESS)
    {
        return status;
    }

    int heapInd = _heap->m_heapSize++;
    while(heapInd > 0)
    {
        VectorGet(vptr, heapInd, &son);
        VectorGet(vptr, (heapInd - 1)/2, &father);
        if(COMPARE(father, son) > 0)
        {
            break;
        }
        else{
            VectorElementSwap(_heap->m_vec,heapInd, (heapInd-1)/2);
            heapInd = (heapInd-1)/2;
        }
    }
    return HEAP_SUCCESS;
}


const void* HeapPeek(const Heap* _heap)
{
    if (_heap == NULL)
    {
        return NULL;
    }

    void* top;
    VectorGet(VECTOR, 0, &top);
    return top;
}

void* HeapExtract(Heap* _heap)
{
    if (_heap == NULL)
    {
        return NULL;
    }

    void *toRemove, *toHeapify;
    int heapInd = 0;
    int direction;
    VectorGet(VECTOR, 0, &toRemove);
    VectorGet(VECTOR, _heap->m_heapSize - 1,&toHeapify);
    VectorElementSwap(_heap->m_vec, 0, _heap->m_heapSize - 1);

    _heap->m_heapSize -= 1;

    VectorRemove(VECTOR, &toRemove);

    while (heapInd > HEAP_SIZE/2)
    {
        direction = Heapify(_heap, heapInd);

        if (direction == 1)
        {
            heapInd = heapInd*2 + 1;
        }
        else if(direction == -1)
        {
            heapInd = heapInd*2 + 2;
        }
        else if(direction == 0)
        {
            break;
        }
    }
    
    return toRemove;

}

size_t HeapSize(const Heap* _heap)
{
    if (_heap == NULL)
    {
        return 0;
    }

    return HEAP_SIZE;
}

size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
    if (_heap == NULL || _act == NULL)
    {
        return 0;
    }

    return VectorForEach(VECTOR, (VectorElementAction)_act, _context);
}


static void Swap(void* x, void* y) {
    void* temp;
    temp = x;
    x = y;
    y = temp;
}

static void VectorElementSwap(Vector *_vec, int _index1, int _index2)
{
    void *temp1, *temp2;
    VectorGet(_vec,_index1,&temp1);
    VectorGet(_vec,_index2,&temp2);
    VectorSet(_vec,_index1, temp2);
    VectorSet(_vec,_index2, temp1);
}

HeapResultCode ConvertEnum(VectorResult _vector) {
    
    switch(_vector) {
        case VECTOR_SUCCESS:
            return HEAP_SUCCESS;
        case VECTOR_UNITIALIZED_ERROR:
            return HEAP_NOT_INITIALIZED;
        case VECTOR_ALLOCATION_ERROR:
            return HEAP_REALLOCATION_FAILED;
        case VECTOR_INDEX_OUT_OF_BOUNDS_ERROR:
            return HEAP_INDEX_OUT_OF_BOUNDS_ERROR;
        case VECTOR_OVERFLOW:
            return HEAP_OVERFLOW;
        case VECTOR_UNDERFLOW:
            return HEAP_UNDERFLOW;
    }
}