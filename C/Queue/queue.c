#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


struct Queue {
    void** m_que;
    size_t m_size;
    size_t m_head;
    size_t m_tail;
    size_t m_nItems;
};

Queue* QueueCreate(size_t _size) {

    Queue* qptr;

    if(_size == 0) {
        return NULL;
    }

    qptr = (Queue*)malloc(sizeof(Queue));

    if(qptr == NULL) {
        return NULL;
    }

    qptr->m_que = (void**)malloc(_size*sizeof(void*));

    if(qptr->m_que == NULL) {
        free(qptr);
        return NULL;
    }

    qptr->m_size = _size;
    qptr->m_head = 0;
    qptr->m_tail = 0;
    qptr->m_nItems = 0;

    return qptr;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy) {

    if(_queue == NULL || *_queue == NULL) {
        return;
    }

    Queue* qptr = *_queue;

    int i;

    for(i = qptr->m_head; i < qptr->m_tail; i = (i + 1) % qptr->m_size) {
        _itemDestroy(qptr->m_que[i]);
    }

    free(qptr->m_que);
    free(qptr);

    *_queue = NULL;
}

QueueResult QueueInsert(Queue* _queue,void* _item) {

    if(_queue == NULL || _item == NULL) {
        return QUEUE_UNINITIALIZED_ERROR;
    }

    if(_queue->m_nItems == _queue->m_size) {
        return QUEUE_OVERFLOW_ERROR;
    }

    _queue->m_que[_queue->m_tail] = _item;
    _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
    _queue->m_nItems += 1;

    return QUEUE_SUCCESS;
}

QueueResult QueueRemove(Queue* _queue,void** _item) {

    if(_queue == NULL) {
        return QUEUE_UNINITIALIZED_ERROR;
    }

    if(_item == NULL) {
        return QUEUE_DATA_UNINITIALIZED_ERROR;
    }

    *_item = _queue->m_que[_queue->m_head];
    _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
    _queue->m_nItems -= 1;

    return QUEUE_SUCCESS;
}

size_t QueueIsEmpty(Queue* _queue) {

    if(_queue == NULL) {
        return 0;
    }

    if(_queue->m_nItems == 0) {
        return 0;
    } 

    return 1;
}

size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context) {

    if(_queue == NULL) {
        return QUEUE_UNINITIALIZED_ERROR;
    }

    size_t i;

    for(i = 0; i < _queue->m_nItems; ++i) {
        if(_action(_queue->m_que[(i + _queue->m_head) % _queue->m_size], _context) == 0) {
            break;
        }
    }

    return i;
}