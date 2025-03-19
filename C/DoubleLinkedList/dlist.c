#include <stdlib.h> //malloc
#include "dlist.h"

#define END &lptr->m_tail 

typedef struct Node Node;

 struct Node {
    void* m_data;
    Node* m_next;
    Node* m_prev;
};

struct List
{
    Node m_head;
    Node m_tail;
};

static void Insert(Node* _ref, Node* _new_node) {

    _new_node->m_prev = _ref->m_prev;
    _new_node->m_next = _ref;
    _ref->m_prev->m_next = _new_node;
    _ref->m_prev = _new_node;

    return;
}

static void* Remove(Node* _node_to_remove) {
    _node_to_remove->m_next->m_prev = _node_to_remove->m_prev;
    _node_to_remove->m_prev->m_next = _node_to_remove->m_next;

    void* data = _node_to_remove->m_data;
    free(_node_to_remove);

    return data;
}

List* ListCreate(void) {

    List* list = (List*)malloc(sizeof(List));

    if(list == NULL) {
        return NULL;
    }

    list->m_head.m_next = &list->m_tail;
    list->m_head.m_prev = &list->m_head;

    list->m_tail.m_prev = &list->m_head;
    list->m_tail.m_next = &list->m_tail;

    return list;
}

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item)) {

    if(_pList == NULL || *_pList == NULL) {
        return;
    }

    List* lptr = *_pList;
    Node* current_node = lptr->m_head.m_next;
    

    while(current_node != END) {

        current_node = current_node->m_next;

        if(_elementDestroy) {
        _elementDestroy(current_node->m_prev->m_data);
        }

        free(current_node->m_prev);
    }

    free(lptr);

    *_pList = NULL;
}

ListItr ListPushHead(List* _list, void* _item) {

    if(_list == NULL || _item == NULL) {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));

    if(new_node == NULL) {
        return NULL;
    }
    new_node->m_data = _item;
    Insert(_list->m_head.m_next, new_node);

    return new_node;
}

ListItr ListPushTail(List* _list, void* _item) {

    if(_list == NULL || _item == NULL) {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));

    if(new_node == NULL) {
        return NULL;
    }
    new_node->m_data = _item;
    Insert(&_list->m_tail, new_node);

    return new_node;
}

void* ListPopHead(List* _list) {

    if(_list == NULL) {
        return NULL;
    }

    if(_list->m_head.m_next == &_list->m_tail) {
        return NULL;
    } 

    return Remove(_list->m_head.m_next);
}

void* ListPopTail(List* _list) {

    if(_list == NULL) {
        return NULL;
    }

    if(_list->m_tail.m_prev == &_list->m_head) {
        return NULL;
    }

    return Remove(_list->m_tail.m_prev);
}

ListItr ListItrBegin(const List* _list) {

    if(_list == NULL) {
        return NULL;
    }

    return _list->m_head.m_next;
}

ListItr ListItrEnd(const List* _list) {

    if(_list == NULL) {
        return NULL;
    }

    return &_list->m_tail;
}

int ListItrEquals(const ListItr _a, const ListItr _b) {

    return (_a == _b);
}

ListItr ListItrNext(ListItr _itr) {

    if(_itr == NULL) {
        return _itr;
    }

    Node* node = (Node*)_itr;

    return node->m_next;
}

ListItr ListItrPrev(ListItr _itr) {

    if(_itr == NULL || ((Node*)_itr)->m_prev == ((Node*)_itr)->m_prev->m_prev) {
        return _itr;
    }

    Node* node = (Node*)_itr;

    return node->m_prev;
}

void* ListItrGet(ListItr _itr) {

    if(_itr == NULL) {
        return NULL;
    }

    Node* node = (Node*)_itr;

    return node->m_data;
}

void* ListItrSet(ListItr _itr, void* _element) {

    if(_itr == NULL || _element == NULL || ((Node*)_itr)->m_next == ((Node*)_itr)) {
        return NULL;
    }

    Node* node = (Node*)_itr;

    void* data = node->m_data;
    node->m_data = _element;

    return data;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element) {

    if(_itr == NULL || _element == NULL) {
        return NULL;
    }

    Node* node = (Node*)_itr;
    Node* new_node = (Node*)malloc(sizeof(Node));

    if(new_node == NULL) {
        return NULL;
    }

    new_node->m_data = _element;
    Insert(_itr, new_node);
    return new_node;
}

void* ListItrRemove(ListItr _itr) {

    if(_itr == NULL || ((Node*)_itr)->m_next == ((Node*)_itr)) {
        return NULL;
    }

    Node* node = (Node*)_itr;

    return Remove(node);
}

size_t ListSize(const List* _list) {

    if(_list == NULL) {
        return 0;
    }

    size_t countSize = 0;

    Node* current_node = _list->m_head.m_next;

    while(current_node != &_list->m_tail) {
        current_node = current_node->m_next;
        countSize += 1;
    }

    return countSize;
}

size_t ListIsEmpty(List* _list) {

    if(_list == NULL) {
        return 0;
    }

    return (_list->m_head.m_next == &_list->m_tail);
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context) {

    if(_begin == NULL || _end == NULL || _action == NULL) {
        return NULL;
    }

    Node* node_begin = (Node*)_begin;
    Node* node_end = (Node*)_end;

    while(node_begin != node_end || node_begin != node_begin->m_next) {

        if(_action(node_begin->m_data, _context) == 0) {
            break;
        }

        node_begin = node_begin->m_next;
    }

    return node_begin;
}