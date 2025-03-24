#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

struct Vector
{
    void** m_items;
    size_t m_originalSize;  /* original allocated space for items */
    size_t m_size;          /* current allocated space for items */
    size_t m_nItems;        /* current number of items */
    size_t m_blockSize;     /* the chunk size to be allocated when no space */
};


Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
    if (_initialCapacity == 0 && _blockSize == 0)
    {
        return NULL;
    }

    /* assign address to the vector */
    Vector* vectorPtr = (Vector*)malloc(sizeof(Vector));
    if (vectorPtr == NULL)
    {
        return NULL;
    }
    /* allocate address to items vector, with the given initial capacity */
    vectorPtr->m_items = (void**)malloc(_initialCapacity * sizeof(void*));
    if (vectorPtr->m_items == NULL)
    {   
        free(vectorPtr);
        return NULL;
    }
    /* assign the given values to the items vector */
    vectorPtr->m_originalSize = _initialCapacity;
    vectorPtr->m_size = _initialCapacity;
    vectorPtr->m_blockSize = _blockSize;
    vectorPtr->m_nItems = 0;

    return vectorPtr;
}

/*_elementDestroy will get a null, unless the (*_vector->m_items[]) array contains a dynamic memory allocation (str,struct,other used malloc)*/
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{   
    size_t i;
    if (_vector == NULL || *_vector == NULL || (*_vector)->m_items == NULL){
        return; /* if these are NULL, we assume no vector created, or its already been destroyed */
    }

    if (_elementDestroy != NULL)
    {
        /* will be used if memory was allocated dynamically into m_items */
        for(i=0; i < (*_vector)->m_nItems; i++){
            _elementDestroy((*_vector)->m_items[i]);
        }
    }

    free((*_vector)->m_items);
    (*_vector)->m_items = NULL;
    free(*_vector);
    *_vector = NULL;
}


VectorResult VectorAppend(Vector* _vector, void* _item)
{
    void** temp_items_ptr; //needed to avoid losing _vector->m_items in case that realloc fail
    if (_vector == NULL || _item == NULL)
    {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if (_vector->m_size == _vector->m_nItems)
    {
    	if (_vector->m_blockSize == 0)
    	{
    		return VECTOR_OVERFLOW;
    	}
        temp_items_ptr = (void**)realloc(_vector->m_items,(_vector->m_size + _vector->m_blockSize) * (sizeof(void*)));
        if (temp_items_ptr == NULL)
        {
            return VECTOR_ALLOCATION_ERROR;
        }
        
        _vector->m_items = temp_items_ptr;
        _vector->m_size += _vector->m_blockSize; // update the current allocated size
    }

    _vector->m_items[_vector->m_nItems] = _item;
    _vector->m_nItems += 1;
    return VECTOR_SUCCESS;
}


VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
    void** temp_items_ptr;
    size_t new_size;
    if(_vector == NULL || _vector->m_items == NULL || _pValue == NULL)
    {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if (_vector->m_nItems == 0)
    {
        return VECTOR_UNDERFLOW;
    }

    *_pValue = _vector->m_items[_vector->m_nItems -1];
    _vector->m_items[_vector->m_nItems -1] = NULL;
    _vector->m_nItems -= 1;

    /* check if a memory shrink is needed */
    if(_vector->m_size > _vector->m_nItems + 2*(_vector->m_blockSize))
    {   
        new_size = _vector->m_originalSize;
        /* check if the new size is at least m_originalSize */
         if (_vector->m_nItems + _vector->m_blockSize < _vector->m_originalSize)
        {
            new_size = _vector->m_originalSize; // Keep original size if less
        }
        else
        {
            new_size = _vector->m_nItems + _vector->m_blockSize; // Shrink based on current items
        }

        temp_items_ptr = (void**)realloc(_vector->m_items, new_size * sizeof(void*));

        if(temp_items_ptr != NULL){
            _vector->m_items = temp_items_ptr;
            _vector->m_size = new_size;
        }
    }
    return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
    if (_vector == NULL || _pValue == NULL)
    {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if (_index >= _vector->m_nItems)
    {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    *_pValue = _vector->m_items[_index];
    return VECTOR_SUCCESS; 
}

VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
    if (_vector == NULL || _value == NULL)
    {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if (_index >= _vector->m_nItems)
    {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    _vector->m_items[_index] = _value;
    return VECTOR_SUCCESS;
}


size_t VectorSize(const Vector* _vector)
{
    if (_vector == NULL)
    {
        return 0;
    }

    return _vector->m_nItems;
}


size_t VectorCapacity(const Vector* _vector)
{
    if (_vector == NULL)
    {
        return 0;
    }

    return _vector->m_size;

}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{   
    size_t index;
    void* element;
    if (_vector == NULL ||_action == NULL)
    {
        return 0;
    }

    for(index=0; index<_vector->m_nItems; index++)
    {   
        /* get the relevant element */
        VectorGet(_vector,index,&element);

        if(_action(element, index, _context ) == 0)
        {
            break;
        }
    }
    return index;
}