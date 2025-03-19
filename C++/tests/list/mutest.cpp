#include "../../inc/mu_test.h"
#include "../../inc/ds/list.hpp"

template <typename T>
bool print(T data)
{
    std::cout << "data: " << data << "\n";
    return 1;
}

BEGIN_TEST(list_ctor)
    ds::List<int>list;
    ASSERT_EQUAL(list.size(), 0);

END_TEST

BEGIN_TEST(list_push_head)
    ds::List<int>list;
    list.push_head(10);

    ASSERT_EQUAL(list.size(), 1);

END_TEST

BEGIN_TEST(list_pop_head)
    ds::List<int>list;
    list.push_head(10);
    ASSERT_EQUAL(list.size(), 1);
    int item = list.pop_head();
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_EQUAL(item, 10);

END_TEST

BEGIN_TEST(list_push_tail)
    ds::List<int>list;
    list.push_head(10);
    ASSERT_EQUAL(list.size(), 1);

END_TEST

BEGIN_TEST(list_pop_tail)
    ds::List<int>list;
    list.push_tail(10);
    ASSERT_EQUAL(list.size(), 1);
    int item = list.pop_tail();
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_EQUAL(item, 10);

END_TEST

BEGIN_TEST(list_copy_ctor)
    ds::List<int>list1;
    list1.push_head(10);
    list1.push_tail(20);

    ds::List<int>list2(list1);

    ASSERT_EQUAL(list2.size(), 2);

END_TEST

BEGIN_TEST(list_copy_ctor_and_pop_head)
    ds::List<int>list1;
    list1.push_head(10);

    ds::List<int>list2(list1);
    int item = list2.pop_head();

    ASSERT_EQUAL(item, 10);

END_TEST

BEGIN_TEST(list_copy_ctor_and_pop_tail)
    ds::List<int>list1;
    list1.push_head(10);
    list1.push_tail(20);

    ds::List<int>list2(list1);
    int item = list2.pop_tail();

    ASSERT_EQUAL(item, 20);

END_TEST

BEGIN_TEST(list_size_cctor)
    ds::List<int>list1;
    list1.push_head(10);
    list1.push_tail(20);

    ds::List<int>list2(list1);
    int item = list2.pop_tail();
    item = list2.pop_head();

    ASSERT_EQUAL(item, 10);
    ASSERT_EQUAL(list2.size(), 0);
    ASSERT_EQUAL(list1.size(), 2);

END_TEST

BEGIN_TEST(list_assignment_operator)
    ds::List<int>list1;
    list1.push_head(10);
    list1.push_tail(20);

    ds::List<int>list2;

    list2 = list1;
    
    ASSERT_EQUAL(list2.size(), 2);
    ASSERT_EQUAL(list1.size(), 2);

END_TEST

BEGIN_TEST(list_is_empty)
    ds::List<int>list1;
    list1.push_head(10);
    list1.push_tail(20);

    int item = list1.pop_tail();
    item = list1.pop_head();
    
    ASSERT_EQUAL(item, 10);
    ASSERT_THAT(list1.empty());

END_TEST

BEGIN_TEST(list_clear)
    ds::List<int>list1;
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_tail(20);
    list1.push_tail(20);
    list1.push_tail(20);
    list1.push_tail(20);

    list1.clear();
    ASSERT_EQUAL(list1.size(), 0);
    ASSERT_THAT(list1.empty());

END_TEST

BEGIN_TEST(list_foreach)
    ds::List<int>list1;
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_head(10);
    list1.push_tail(20);
    list1.push_tail(20);
    list1.push_tail(20);
    list1.push_tail(20);

    // ds::<int>::for_each(list1, print, NULL);
    // size_t amount = ds::List<int>for_each(list1, print<int, void*>, nullptr);

    // ASSERT_EQUAL(amount, 9);

END_TEST


TEST_SUITE(List unit tests)
	TEST(list_ctor)
	TEST(list_push_head)
	TEST(list_pop_head)
	TEST(list_push_tail)
	TEST(list_pop_tail)
	// TEST(list_pop_tail_from_empty_list)
	TEST(list_copy_ctor)
	TEST(list_copy_ctor_and_pop_head)
	TEST(list_copy_ctor_and_pop_tail)
	TEST(list_size_cctor)
	TEST(list_assignment_operator)
	TEST(list_is_empty)
	TEST(list_clear)
	TEST(list_foreach)

END_SUITE