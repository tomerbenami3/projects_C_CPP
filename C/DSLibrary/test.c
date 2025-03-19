#include "../mutest/mu_test.h"
#include "../Vectornew/vector.h"
#include "../Vector/stack.h"


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
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
export LD_LIBRARY_PATH
*/