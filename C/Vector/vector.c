#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct Vector {
    void** m_items;
    size_t m_originalSize;
    size_t m_size;
    size_t m_nItems;
    size_t m_blockSize;
};

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize) {

    Vector* vptr;

    if(_initialCapacity <= 0 && _blockSize <= 0) {
        return NULL;
    }

    vptr = (Vector*)malloc(sizeof(Vector));

    if(vptr == NULL) {
        return NULL;
    }

    vptr->m_items = (void**)malloc(_initialCapacity*sizeof(void*));

    if(vptr->m_items == NULL) {
        free(vptr);
        return NULL;
    }

    vptr->m_blockSize = _blockSize;
    vptr->m_originalSize = _initialCapacity;
    vptr->m_size = _initialCapacity;
    vptr->m_nItems = 0;

    return vptr;
}

// void _elementDestroy(void* item) {

//     if(item == NULL) {
//         return;
//     }

//     free(item);
// }

void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item)) {

    int i;

    if(_vector == NULL || *_vector == NULL || (*_vector)->m_items == NULL) {
        return;
    }

    Vector* vptr = *_vector;

    if(_elementDestroy != NULL) {
        for(i = 0; i < vptr->m_nItems; ++i) {
            _elementDestroy(vptr->m_items[i]);
        }
    }
    free(vptr->m_items);
    free(vptr);
    
    *_vector = NULL;
}

Vector* HandleAllocationIncrease(Vector* _vector) {

    void** temp;

    if(_vector->m_nItems == _vector->m_size) {

        if(_vector->m_blockSize == 0) {
        return NULL;
        
        }
        temp = (void**)realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize)*sizeof(void*));

        if(temp != NULL) {
            _vector->m_items = temp;
        } else {
            return NULL;
        }
        _vector->m_size += _vector->m_blockSize;
    }
    return _vector;
}

VectorResult VectorAppend(Vector* _vector, void* _item) {

    if(_vector == NULL || _item == NULL) {
        return VECTOR_UNITIALIZED_ERROR;
    }
    
    if(_vector->m_blockSize < 0) {
        return VECTOR_UNITIALIZED_ERROR;
    }

    _vector = HandleAllocationIncrease(_vector);

    _vector->m_items[_vector->m_nItems] = _item;
    _vector->m_nItems += 1;

    return VECTOR_SUCCESS;
}

Vector* HandleAllocationDecrease(Vector* _vector) {

    void** temp;

    if(_vector->m_size - _vector->m_nItems >= 2*_vector->m_blockSize) {
        temp = realloc(_vector->m_items, (_vector->m_size - _vector->m_blockSize)*sizeof(void*));

        if(temp != NULL) {
            _vector->m_items = temp;
        } else {
            return NULL;
        }
        _vector->m_size -= _vector->m_blockSize;
    }
    return _vector;
}

VectorResult VectorRemove(Vector* _vector, void** _pValue) {

    if(_vector == NULL || _pValue == NULL) {
        return VECTOR_UNITIALIZED_ERROR;
    }
    if(_vector->m_nItems == 0) {
        return VECTOR_UNDERFLOW;
    }

    *_pValue = _vector->m_items[_vector->m_nItems - 1];
    _vector->m_nItems-= 1;

    if(_vector->m_nItems > _vector->m_originalSize) {
        _vector = HandleAllocationDecrease(_vector);
    }

    return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue) {

    if(_vector == NULL || _pValue == NULL) {
        return VECTOR_ALLOCATION_ERROR;
    }

    if(_index >= _vector->m_nItems) {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    *_pValue = _vector->m_items[_index];

    return VECTOR_SUCCESS;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value) {

    if(_vector == NULL || _value == NULL) {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if(_index > _vector->m_nItems) {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

     _vector->m_items[_index] = _value;

    return VECTOR_SUCCESS;
}

size_t VectorSize(const Vector* _vector) {

    if(_vector == NULL) {
        return 0;
    }

    return _vector->m_nItems;
}

size_t VectorCapacity(const Vector* _vector) {

    if(_vector == NULL) {
        return 0;
    }

    return _vector->m_size;
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context) {

    if(_vector == NULL || _action == NULL) {
        return 0;
    }
    int i;

    for(i = 0; i < _vector->m_nItems; ++i) {
        if(_action(_vector->m_items[i], i, _context) == 0)
 			break;
        
        }
 		return i;
}