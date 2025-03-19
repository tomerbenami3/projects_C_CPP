#include "../mutest/mu_test.h"
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "stack.h"
#include "outfix.h"

BEGIN_TEST(CreationTest1)
	int size = 10, blocksize = 4;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    if(vptr != NULL) {
        ASSERT_PASS();
    } else {
        ASSERT_FAIL("fail on demand");
    }
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(CreationTest1)
	// TEST(add_operations)
	// TEST(abs_function)

	// TEST(empty_struct_is_not_empty)
	// TEST(work_with_strings)
	// TEST(access_null_ptr_will_seg)

	// TEST(test_should_fail)
	// TEST(test_should_pass)


	// TEST(test_with_no_assert_should_fail)

	// IGNORE_TEST(test_should_fail)
	// IGNORE_TEST(test_should_pass)

	// TEST(test_with_no_assert_should_fail)
END_SUITE


/*
static int PrintIt(void* _element, size_t _index, void* _context) {
        printf("%d\n", *((int*)(_element)));
    return 1;
}

static int FindEl(void* _element, size_t _index, void* _context) {

    if(_element == _context) {
        return 0;
    }

    return 1;
}

static void _elementDestroy(void* item) {

    if(item == NULL) {
        return;
    }

    // free(item);
}

static void CreationTest1() {
    int size = 10, blocksize = 4;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    if(vptr != NULL) {
        printf("CreationTest1: PASS\n");
    } else {
        printf("CreationTest1: FAILED\n");
    }
}

static void CreationTest2() {
    int size = 0, blocksize = 0;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    if(vptr == NULL) {
        printf("CreationTest2: PASS\n");
    } else {
        printf("CreationTest2: FAILED\n");
    }
}

static void CreationTest3() {
    int size = 0, blocksize = 5;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    if(vptr != NULL) {
        printf("CreationTest3: PASS\n");
    } else {
        printf("CreationTest3: FAILED\n");
    }
}

static void CreationTest4() {
    int size = 5, blocksize = 0;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    if(vptr != NULL) {
        printf("CreationTest4: PASS\n");
    } else {
        printf("CreationTest4: FAILED\n");
    }
}

static void CreationTest5() {
    int size = -1, blocksize = 0;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    if(vptr == NULL) {
        printf("CreationTest5: PASS\n");
    } else {
        printf("CreationTest5: FAILED\n");
    }
}

static void DestroyTest1() {
    int size = 10, blocksize = 4;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    VectorDestroy(&vptr, NULL);

    if(vptr == NULL) {
        printf("DestroyTest1: PASS\n");
    } else {
        printf("DestroyTest1: FAILED\n");
    }
}

static void VectorAppendTest1() {
    int size = 10, blocksize = 4;
    int a = 1;
    Vector* vptr = NULL;

    int VecorResult = VectorAppend(vptr, &a);

    if(VecorResult == VECTOR_UNITIALIZED_ERROR) {
        printf("VectorAppendTest1: PASS\n");
    } else {
        printf("VectorAppendTest1: FAILED\n");
    }

    VectorDestroy(&vptr, NULL);
}

static void VectorAppendTest2() {
    int size = 4, blocksize = 0;
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int res;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    for(int i = 0; i < size; ++i) {
        res = VectorAppend(vptr,arr + i);
        if(res != VECTOR_SUCCESS) {
            break;
        }
    }

    if(res == VECTOR_OVERFLOW) {
        printf("VectorAppendTest2: PASS\n");
    } else {
        printf("VectorAppendTest2: FAILED\n");
    }

    VectorDestroy(&vptr, NULL);
}

static void VectorAppendTest3() {
    int size = 4, blocksize = 0;
    int res;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);

    res = VectorAppend(vptr,NULL);

    if(res == VECTOR_UNITIALIZED_ERROR) {
        printf("VectorAppendTest3: PASS\n");
    } else {
        printf("VectorAppendTest3: FAILED\n");
    }

    VectorDestroy(&vptr, NULL);
}

static void VectorAppendTest4() {
    int size = 4, blocksize = -5;
    int res;
    Vector* vptr;

    vptr = VectorCreate(size, blocksize);
    res = VectorAppend(vptr,NULL);

    // printf("%d\n", res);

    if(res == VECTOR_ALLOCATION_ERROR) {
        printf("VectorAppendTest4: PASS\n");
    } else {
        printf("VectorAppendTest4: FAILED\n");
    }

    VectorDestroy(&vptr, NULL);
}

static void VectorRemoveTest1() {
    int size = 10, blocksize = 4;
    int res;
    void* z;
    Vector* vptr = NULL;

    res = VectorRemove(vptr, &z);

    if(res == VECTOR_UNITIALIZED_ERROR) {
        printf("VectorRemoveTest1 PASS\n");
    } else
        printf("VectorRemoveTest1 FAILED\n");

    VectorDestroy(&vptr,_elementDestroy);
}

static void VectorRemoveTest2() {
    int size = 10, blocksize = 4;
    int res;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);
    VectorAppend(vptr, &z);
    res = VectorRemove(vptr, &z);

    if(res == VECTOR_UNITIALIZED_ERROR) {
        printf("VectorRemoveTest2 PASS\n");
    } else
        printf("VectorRemoveTest2 FAILED\n");

    VectorDestroy(&vptr,_elementDestroy);
}

static void VectorRemoveTest3() {
    int size = 10, blocksize = 4;
    int res;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);
    res = VectorRemove(vptr, &z);

    if(res == VECTOR_UNDERFLOW) {
        printf("VectorRemoveTest3 PASS\n");
    } else
        printf("VectorRemoveTest3 FAILED\n");

    VectorDestroy(&vptr,_elementDestroy);
}

static void VectorRemoveTest4() {
    int size = 10, blocksize = 4;
    int res, a = 1, b = 2, c = 3;
    void* z = NULL, *x;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);

    VectorRemove(vptr, &z);
    VectorRemove(vptr, &z);
    VectorRemove(vptr, &z);
    res = VectorRemove(vptr, &z);

    // printf("%d\n", res);

    if(res == VECTOR_UNDERFLOW) {
        printf("VectorRemoveTest4 PASS\n");
    } else
        printf("VectorRemoveTest4 FAILED\n");

    VectorDestroy(&vptr,_elementDestroy);
}

static void VectorRemoveTest5() {
    int size = 4, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);
    VectorAppend(vptr, &d);
    VectorAppend(vptr, &e);
    VectorAppend(vptr, &f);

    size_t cap = VectorCapacity(vptr);
    size_t sizeOf = VectorSize(vptr);

    printf("%zu, %zu\n", cap, sizeOf);

    VectorForEach(vptr,PrintIt,NULL);
    
    // res = VectorRemove(vptr, &z);

    if(result == VECTOR_UNDERFLOW) {
        printf("VectorRemoveTest5 PASS\n");
    } else
        printf("VectorRemoveTest5 FAILED\n");

    VectorDestroy(&vptr,_elementDestroy);
}

static void VectorGetTest1() {
    int size = 10, blocksize = 4;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);

    result = VectorGet(NULL,1,&z);
    
    if(result == VECTOR_ALLOCATION_ERROR) {
        printf("VectorGetTest1 PASS\n");
    } else {
        printf("VectorGetTest1 FAILED\n");
    }
    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorGetTest2() {
    int size = 10, blocksize = 4;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);

    result = VectorGet(vptr,4,&z);
    
    if(result == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR) {
        printf("VectorGetTest2 PASS\n");
    } else {
        printf("VectorGetTest2 FAILED\n");
    }

    VectorDestroy(&vptr,_elementDestroy);
}

static void VectorSetTest1() {
    int size = 10, blocksize = 4;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);

    result = VectorSet(NULL,2,&f);
    
    if(result == VECTOR_UNITIALIZED_ERROR) {
        printf("VectorSetTest1 PASS\n");
    } else {
        printf("VectorSetTest1 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorSetTest2() {
    int size = 10, blocksize = 4;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);

    result = VectorSet(vptr,6,&f);
    
    if(result == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR) {
        printf("VectorSetTest2 PASS\n");
    } else {
        printf("VectorSetTest2 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorSetTest3() {
    int size = 10, blocksize = 4;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);

    result = VectorSet(vptr,1,NULL);

    if(result == VECTOR_UNITIALIZED_ERROR) {
        printf("VectorSetTest3 PASS\n");
    } else {
        printf("VectorSetTest3 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorSizeTest1() {
    int size = 10, blocksize = 4;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);

    result = VectorSize(vptr);

    // printf("%d\n", result);

    if(result == 3) {
        printf("VectorSizeTest1 PASS\n");
    } else {
        printf("VectorSizeTest1 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorSizeTest2() {
    int size = 4, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);
    VectorAppend(vptr, &d);
    VectorAppend(vptr, &c);

    result = VectorSize(vptr);

    // printf("%d\n", result);

    if(result == 5) {
        printf("VectorSizeTest2 PASS\n");
    } else {
        printf("VectorSizeTest2 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorSizeTest3() {
    int size = 4, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    result = VectorSize(NULL);

    // printf("%d\n", result);

    if(result == 0) {
        printf("VectorSizeTest3 PASS\n");
    } else {
        printf("VectorSizeTest3 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorCapacityTest1() {
    int size = 10, blocksize = 4;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);

    result = VectorCapacity(vptr);

    printf("%d\n", result);

    if(result == size) {
        printf("VectorCapacityTest1 PASS\n");
    } else {
        printf("VectorCapacityTest1 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorCapacityTest2() {
    int size = 3, blocksize = 1;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);
    VectorAppend(vptr, &d);
    VectorAppend(vptr, &e);
    VectorAppend(vptr, &f);

    result = VectorCapacity(vptr);

    // printf("%d\n", result);

    if(result == 6) {
        printf("VectorCapacityTest2 PASS\n");
    } else {
        printf("VectorCapacityTest2 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorCapacityTest3() {
    int size = 4, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    result = VectorCapacity(vptr);

    // printf("%d\n", result);

    if(result == 0) {
        printf("VectorCapacityTest3 PASS\n");
    } else {
        printf("VectorCapacityTest3 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorForEachTest1() {
    int size = 10, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);
    VectorAppend(vptr, &d);
    VectorAppend(vptr, &e);
    VectorAppend(vptr, &f);

    result = VectorForEach(vptr,PrintIt,NULL);

    printf("%d\n", result);

    if(result == VectorSize(vptr)) {
        printf("VectorForEachTest1 PASS\n");
    } else {
        printf("VectorForEachTest1 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorForEachTest2() {
    int size = 10, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);
    VectorAppend(vptr, &d);
    VectorAppend(vptr, &e);
    VectorAppend(vptr, &f);

    result = VectorForEach(NULL,PrintIt,NULL);

    // printf("%d\n", result);

    if(result == 0) {
        printf("VectorForEachTest2 PASS\n");
    } else {
        printf("VectorForEachTest2 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorForEachTest3() {
    int size = 10, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);
    VectorAppend(vptr, &d);
    VectorAppend(vptr, &e);
    VectorAppend(vptr, &f);

    result = VectorForEach(vptr,NULL,NULL);

    // printf("%d\n", result);

    if(result == 0) {
        printf("VectorForEachTest3 PASS\n");
    } else {
        printf("VectorForEachTest3 FAILED\n");
    }

    // VectorDestroy(&vptr,_elementDestroy);
}

static void VectorForEachTest4() {
    int size = 10, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* z = NULL, *x = NULL;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);
    VectorAppend(vptr, &d);
    VectorAppend(vptr, &e);
    VectorAppend(vptr, &f);

    result = VectorForEach(vptr,FindEl,&c);

    printf("%d\n", result);

    if(result == 2) {
        printf("VectorForEachTest4 PASS\n");
    } else {
        printf("VectorForEachTest4 FAILED\n");
    }

    VectorDestroy(&vptr,_elementDestroy);
}

static void VectorForEachTest5() {
    int size = 10, blocksize = 2;
    int result;
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, x = 15;
    Vector* vptr = NULL;

    vptr = VectorCreate(size, blocksize);

    VectorAppend(vptr, &a);
    VectorAppend(vptr, &b);
    VectorAppend(vptr, &c);
    VectorAppend(vptr, &d);
    VectorAppend(vptr, &e);
    VectorAppend(vptr, &f);

    result = VectorForEach(vptr,FindEl,&x);

    printf("%d\n", result);

    if(result == VectorSize(vptr)) {
        printf("VectorForEachTest5 PASS\n");
    } else {
        printf("VectorForEachTest5 FAILED\n");
    }

    VectorDestroy(&vptr,_elementDestroy);
}



int main() {

    void* z;
    int size = 10, blocksize = 4;

    // CreationTest1();
    // CreationTest2();
    // CreationTest3();
    // CreationTest4();
    // CreationTest5();

    // DestroyTest1();

    // VectorAppendTest1();
    // VectorAppendTest2();
    // VectorAppendTest3();
    // VectorAppendTest4(); //?

    // VectorRemoveTest1();
    // // VectorRemoveTest2(); // ?
    // VectorRemoveTest3();
    // // VectorRemoveTest4(); // res = 5?
    // // VectorRemoveTest5(); //? why segmentation fault

    // VectorGetTest1();
    // // VectorGetTest2();

    // VectorSetTest1();
    // VectorSetTest2();
    // VectorSetTest3();

    // VectorSizeTest1();
    // VectorSizeTest2();
    // VectorSizeTest3();

    // VectorCapacityTest1();
    // VectorCapacityTest2();
    // VectorCapacityTest3();

    // VectorForEachTest1();
    // VectorForEachTest2();
    // VectorForEachTest3();
    // VectorForEachTest4();
    // VectorForEachTest5();

///////////////////////////////////

    // Stack* sptr;

    // sptr = StackCreate(size, blocksize);

    // int a = 1, b = 2, c = 3, d = 5;

    // StackPush(sptr, &a);
    // StackPush(sptr, &b);
    // StackPush(sptr, &c);
    // StackPop(sptr, &z);
    // printf("--%d--\n", *(int*)z);
    // StackPush(sptr, &d);

    // // StackTop(sptr, &z);
    // // printf("--%d--\n", *(int*)z);

    // int isEmpty = StackIsEmpty(sptr);

    // printf("%d-----\n", isEmpty);

    // StackPrint(sptr, PrintIt, NULL);

    char source[] = "(2+4)*5+3";
    char target[30];

    int status = checkBracketsTypes(source);

    ConvertInToOutfix(source, target);


    return 0;
}
*/