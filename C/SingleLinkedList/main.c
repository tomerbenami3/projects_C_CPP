#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

static void InsertTest1(Person* persons);

int main(void) {

Person persons[5] = {
        {10, "Alice", 85, &persons[1]},
        {20, "Bob", 30, &persons[2]},
        {30, "Charlie", 65, &persons[3]},
        {40, "David", 40, &persons[4]},
        {50, "Eve", 45, NULL}
    };

    InsertTest1(persons);
    Person* p_last;
    int maxAge;

    p_last = FindLastPersonRec(persons);

    maxAge = FindOldestPersonRec(persons);


    PrintList(persons);

    PrintList(p_last);
    printf("%d\n", maxAge);

    return 0;
    
}

static void InsertTest1(Person* persons) {

    Person p1 = {
        25, "Tomer", 15, NULL
    };
    Person p2 = {
        15, "Alon", 15, NULL
    };

    Person* p_remove;
    
    

    // ListInsertByKey(persons, 25, &p1);
    // ListInsertByKeyRec(persons, 15, &p2);

    // PrintList(persons);

    // printf("\n");

    // ListRemoveByKey(persons, 40, &p_remove);
    // PrintList(persons);

    // printf("\n");
    // ListRemoveByKeyRec(persons, 30, &p_remove);
    // PrintList(persons);

}