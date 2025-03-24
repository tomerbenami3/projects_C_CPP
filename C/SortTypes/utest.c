#include "mu_test.h"


BEGIN_TEST(_equality_on_integers)
	int a = 42;
	long s = 43;

	ASSERT_EQUAL_INT(a, 42);
	ASSERT_EQUAL_INT(s, 43);


	--s;

	ASSERT_EQUAL_INT(s, a);
END_TEST

BEGIN_TEST(add_operations)
	int n = 42;
	int r = n++;

	ASSERT_EQUAL_INT(n, 43);
	ASSERT_EQUAL_INT(r, n-1);
	ASSERT_THAT(n < r);
END_TEST

BEGIN_TEST(abs_function)
	int n[] = {0, 2, 42, ~0, -2, -42};

	for(size_t i = 0; i < sizeof(n)/sizeof(*n); ++i){
		int abs_val = abs(n[i]);

		ASSERT_THAT( abs_val >= 0);
	}

END_TEST

BEGIN_TEST(empty_struct_is_not_empty)
	struct S{int x;};

	ASSERT_THAT(sizeof(struct S) != 0);

	ASSERT_NOT_EQUAL_INT(sizeof(struct S), 0);
END_TEST

BEGIN_TEST(work_with_strings)
	char str[] = "hello";
	str[0] = 'H';

	ASSERT_EQUAL_STR(str, "Hello");
	ASSERT_NOT_EQUAL_STR(str, "hello");
END_TEST



BEGIN_TEST(access_null_ptr_will_seg)
	int* p = 0;
	ASSERT_THAT(p == 0);
	/* next line will blow the segment */
	*p = 666;

	ASSERT_FAIL("we should not reach this");
END_TEST

BEGIN_TEST(test_should_fail)
	ASSERT_FAIL("fail on demand");
END_TEST

BEGIN_TEST(test_should_pass)
    int x = 8;
	if ( x > 5) {
		ASSERT_PASS();
	} else {
		ASSERT_FAIL("fail on demand");
	}
END_TEST


BEGIN_TEST(test_with_no_assert_should_fail)
	const char *some = "stupid";
	++some;
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	IGNORE_TEST(_equality_on_integers)
	TEST(add_operations)
	TEST(abs_function)

	TEST(empty_struct_is_not_empty)
	TEST(work_with_strings)
	TEST(access_null_ptr_will_seg)

	TEST(test_should_fail)
	TEST(test_should_pass)


	TEST(test_with_no_assert_should_fail)

	IGNORE_TEST(test_should_fail)
	IGNORE_TEST(test_should_pass)

	TEST(test_with_no_assert_should_fail)
END_SUITE
