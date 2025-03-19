#include "dlist.h"
#include <stdio.h>
#include <stdlib.h> // free

static int PrintInt(void* _element, void* _context)
{
    printf("%d\t",*(int*)_element);
    return 1;
}

static int FindInt(void* _element, void* _context)
{
    return (*(int*)_element == *(int*)_context);
}

static void TestListCreate1();
static void TestListDestroy1();
static void TestListPushHead1();
static void TestListPushHead2();
static void TestListPushHead3();
static void TestListPushTail1();
static void TestListPushTail2();
static void TestListPopHead1();
static void TestListPopTail1();
static void TestListItrBegin1();
static void TestListItrEnd1();
static void TestListForRach();



int main()
{
    TestListCreate1();
    TestListDestroy1();
    TestListPushHead1();
    TestListPushHead2();
    TestListPushHead3();
    TestListPushTail1();
    TestListPushTail2();
    TestListPopHead1();
    TestListPopTail1();
    TestListItrBegin1();
    TestListItrEnd1();
    TestListForRach();
}


static void TestListCreate1()
{
    List* list = ListCreate();
    if (list != NULL)
    {
        printf("TestListCreate1: PASS\n");
        ListDestroy(&list,NULL);
        return;
    }
    ListDestroy(&list,NULL);
    printf("TestListCreate1: FAIL\n");
}


static void TestListDestroy1()
{
    List* list = ListCreate();
    ListDestroy(&list,NULL);
    if (list != NULL)
    {
        printf("TestListDestroy1: FAIL\n");
        return;
    }
    printf("TestListDestroy1: PASS\n");
}


/* push item to the head of the list */
static void TestListPushHead1()
{
    List* list = ListCreate();
    int* item = (int*)malloc(sizeof(int));
    *item = 5;
    void* pushed;
    pushed = ListPushHead(list,item);
    pushed = ListItrGet(pushed);

    if (*item == *(int*)pushed)
    {
        printf("TestListPushHead1: PASS\n");
    }
    else
    {
        printf("TestListPushHead1: FAIL\n");
    }
    ListDestroy(&list,free);
}

static void TestListForRach()
{
    List* list = ListCreate();
    int* item = (int*)malloc(sizeof(int));

    for(int index = 1; index < 8; index++) {
        *item = index;
        ListPushHead(list,item);
    }
    
    ListItrForEach(ListItrBegin(list), ListItrEnd(list), PrintInt, NULL);

    // if (*item == *(int*)pushed)
    // {
    //     printf("TestListPushHead1: PASS\n");
    // }
    // else
    // {
    //     printf("TestListPushHead1: FAIL\n");
    // }
    ListDestroy(&list,free);
}

/* push NULL item to the head of the list */
static void TestListPushHead2()
{
    List* list = ListCreate();
    void* item = NULL;
    ListItr pushed;
    pushed = ListPushHead(list,item);

    if (pushed == NULL)
    {
        printf("TestListPushHead2: PASS\n");
    }
    else
    {
        printf("TestListPushHead2: FAIL\n");
    }
    ListDestroy(&list,NULL);
}

/* push 3 items to the head of the list */
static void TestListPushHead3()
{
    List* list = ListCreate();
    int i=0, j=2, k=4;
    void* pushed;
    
    pushed = ListPushHead(list,&i);
    pushed = ListItrGet(pushed);
    if (*(int*)pushed != i)
    {   
        printf("TestListPushHead3: FAIL\n");
        ListDestroy(&list,NULL);
        return;
    }
    pushed = ListPushHead(list,&j);
    pushed = ListItrGet(pushed);
    if (*(int*)pushed != j)
    {   
        printf("TestListPushHead3: FAIL\n");
        ListDestroy(&list,NULL);
        return;
    }
    pushed = ListPushHead(list,&k);
    pushed = ListItrGet(pushed);
    if (*(int*)pushed != k)
    {   
        printf("TestListPushHead3: FAIL\n");
        ListDestroy(&list,NULL);
        return;
    }
    printf("TestListPushHead3: PASS\n");
    ListDestroy(&list,NULL);
}


//push item to the tail of the list
static void TestListPushTail1()
{
    List* list = ListCreate();
    int item = 5;
    void* pushed;
    pushed = ListPushTail(list,&item);
    pushed = ListItrGet(pushed);
    if (item == *(int*)pushed)
    {
        printf("TestListPushTail1: PASS\n");
    }
    else
    {
        printf("TestListPushTail1: FAIL\n");
    }
    ListDestroy(&list,NULL);
}

/* push NULL item to the tail of the list */
static void TestListPushTail2()
{
    List* list = ListCreate();
    int item = 5;
    ListItr pushed;
    pushed = ListPushTail(list,NULL);
    if (pushed == NULL)
    {
        printf("TestListPushTail2: PASS\n");
    }
    else
    {
        printf("TestListPushTail2: FAIL\n");
    }
    ListDestroy(&list,NULL);
}


/* insert 1 item to head and  one to tail, pop head. expected: item1 == popped */
static void TestListPopHead1()
{
    List* list = ListCreate();
    int item1 = 5, item2 = 2;
    void* popped;
    ListPushHead(list,&item1);
    ListPushTail(list,&item2);
    popped = ListPopHead(list);

    if (item1 == *(int*)popped)
    {
        printf("TestListPopHead1: PASS\n");
    }
    else
    {
        printf("TestListPopHead1: FAIL\n");
    }
    ListDestroy(&list,NULL);
}


/* insert 1 item to head and  one to tail, pop tail. expected: item2 == popped */
static void TestListPopTail1()
{
    List* list = ListCreate();
    int item1 = 5, item2 = 2;
    void* popped;
    ListPushTail(list,&item2);
    ListPushHead(list,&item1);
    popped = ListPopTail(list);

    if (item2 == *(int*)popped)
    {
        printf("TestListPopTail1: PASS\n");
    }
    else
    {
        printf("TestListPopTail1: FAIL\n");
    }
    ListDestroy(&list,NULL);
}


/* test ListItrBegin on a non empty list. expected: return head */
static void TestListItrBegin1()
{
    List* list = ListCreate();
    int item = 5;
    ListItr head = ListPushHead(list,&item);
    ListItr begin = ListItrBegin(list);
    if (begin == head)
    {
        printf("TestListItrBegin1: PASS\n");
    }
    else
    {
        printf("TestListItrBegin1: FAIL\n");
    }
    ListDestroy(&list,NULL);
}


/* test ListItrEnd on a non empty list. expected: return tail */
static void TestListItrEnd1()
{
    List* list = ListCreate();
    int item = 5;
    ListItr head = ListPushHead(list,&item);
    ListItr end = ListItrEnd(list);
    if (end != head && end != NULL)
    {
        printf("TestListItrEnd1: PASS\n");
    }
    else
    {
        printf("TestListItrEnd1: FAIL\n");
    }
    ListDestroy(&list,NULL);
}