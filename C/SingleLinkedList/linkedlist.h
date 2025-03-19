#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__


typedef struct Person Person;

struct Person{
    int m_id;
    char m_name[128];
    int m_age;
    Person* m_next;
};

/*
p - pointer to the new node we want to insert
head - can be NULL
*/

Person* ListInsertHead(Person* _head, Person* _p);

Person* ListRemoveHead(Person* _head, Person** _item);

Person* ListInsertByKey(Person* _head, int _key, Person* _p);

Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p); //head->next = ListInsertByKeyRec(head->next...)

Person* ListRemoveByKey(Person* _head, int _key, Person** _p);

Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p);

void PrintList(Person* _head);

Person* FindLastPersonRec(Person* _head);

int FindOldestPersonRec(Person* _head);


#endif /* __LINKEDLIST_H__ */