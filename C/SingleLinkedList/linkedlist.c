#include <stdio.h>
#include "linkedlist.h"


Person* ListInsertHead(Person* _head, Person* _p) {

    if(_p == NULL) {
        return NULL;
    }

    _p->m_next = _head;

    return _p;
}

Person* ListRemoveHead(Person* _head, Person** _item) {

    if(_item == NULL) {
        return NULL;
    }

    if(_head == NULL) {
        *_item = NULL;
        return _head;
    } 

    *_item = _head;

    return _head->m_next;
}

Person* ListInsertByKey(Person* _head, int _key, Person* _p) {

    if(_p == NULL) {
        return _head;
    }

    if(_head == NULL || _head->m_id > _key) {
        _p->m_next = _head;
        return _p;
    }

    Person* prev_head, *current_head = _head;

    while(current_head != NULL && _key > current_head->m_next->m_id) {

            prev_head = current_head;
            current_head = current_head->m_next;
    }

    if(current_head == NULL || _key < current_head->m_id) {
        prev_head->m_next = _p;
        _p->m_next = current_head;
    }

    return _head;

}

Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p) {

    if(_p == NULL) {
        return _head;
    }

    if(_head == NULL || _head->m_id > _key) {
        _p->m_next = _head;
        return _p;
    }

    if(_key > _head->m_id) {
        _head->m_next = ListInsertByKeyRec(_head->m_next, _key, _p);
    }

    return _head;
}

Person* ListRemoveByKey(Person* _head, int _key, Person** _p) {

    if(_p == NULL) {
        return _head;
    }

    if(_head == NULL) {
        *_p = NULL;
        return _head;
    }

    Person* prev_head, *current_head;
    current_head = _head;
    prev_head = current_head;

    while(current_head != NULL || _key < current_head->m_id) {

            prev_head = current_head;
            current_head = current_head->m_next;
        }

        if(current_head == NULL || _key > current_head->m_id) {
            *_p = NULL;

        } else {

        *_p = current_head;
        prev_head->m_next = current_head->m_next;
        }

        return _head;
}

Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p) {

    if(_p == NULL) {
        return _head;
    }

    if(_head == NULL || _key > _head->m_id) {
        *_p = NULL;
        return _head;
    }

    if(_key == _head->m_id) {
        *_p = _head;
        return _head->m_next;
    }

    _head->m_next = ListRemoveByKeyRec(_head->m_next, _key, _p);

    return _head;
}

void PrintList(Person* _head) {

    if(_head == NULL) {
        return;
    }

    while(_head != NULL) {
        printf("ID: %d\tName: %s\tAge: %d\n", _head->m_id, _head->m_name, _head->m_age);
        _head = _head->m_next;
    }
    printf("\n");
}

Person* FindLastPersonRec(Person* _head) {

    if(_head == NULL) {
        return _head;
    }

    if(_head->m_next == NULL) {
        return _head;
    }

    return FindLastPersonRec(_head->m_next);
}

int CompareAge(Person* _head, int max) {

    if(_head == NULL) {
        return max;
    }

    if(_head->m_age > max) {
        max = _head->m_age;
    }
    return CompareAge(_head->m_next, max);
}

int FindOldestPersonRec(Person* _head) {

    if(_head == NULL) {
        return -1;
    }

    int maxAge = _head->m_age;

    return CompareAge(_head->m_next, maxAge);;

}