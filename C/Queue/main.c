#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static int Print(void* _element, void* _context) {

    printf("%d\t", *(int*)_element);
    return 1;
}

static void CreateTest1(void) {

    Queue* qptr;
    int size = 0;

    qptr = QueueCreate(size);

    if(qptr == NULL) {
        printf("CreateTest1: PASS\n");
    } else {
        printf("CreateTest1: FAILED\\n");
    }
}

static void CreateTest2(void) {

    Queue* qptr;
    int size = -1;

    qptr = QueueCreate(size);

    if(qptr == NULL) {
        printf("CreateTest2: PASS\n");
    } else {
        printf("CreateTest2: FAILED\\n");
    }
}

static void DestroyTest1(void) {

    Queue* qptr = NULL;
    int size = 6;

    QueueDestroy(&qptr, free);

    if(qptr == NULL) {
        printf("DestroyTest2: PASS\n");
    } else {
        printf("DestroyTest2: FAILED\\n");
    }
}

static void DestroyTest2(void) {

    Queue* qptr = NULL;
    int size = 6;

    QueueDestroy(&qptr, free);

    if(qptr == NULL) {
        printf("DestroyTest2: PASS\n");
    } else {
        printf("DestroyTest2: FAILED\\n");
    }
}

static void DestroyTest3(void) {

    Queue* qptr = NULL;
    int size = 0;

    QueueDestroy(&qptr, free);

    if(qptr == NULL) {
        printf("DestroyTest2: PASS\n");
    } else {
        printf("DestroyTest2: FAILED\\n");
    }
}



int main(void) {

    Queue* qptr;
    int size = 4;
    int a = 1, b = 2, c = 3, d = 4, e = 1, f = 2;
    void* z;

    CreateTest1();
    CreateTest2();

    DestroyTest1();
    DestroyTest2();



    // qptr = QueueCreate(size);

    // QueueInsert(qptr, &a);
    // QueueInsert(qptr, &b);
    // QueueInsert(qptr, &c);
    // QueueInsert(qptr, &d);

    // QueueRemove(qptr, &z);
    // QueueRemove(qptr, &z);

    // QueueInsert(qptr, &e);
    // QueueInsert(qptr, &f);

    // QueueForEach(qptr, Print, NULL);

    return 0;
}

// static void CreateTest1() {

//     size_t size = 0;
// }
