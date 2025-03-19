#include "../../inc/mu_test.h"
#include "../../inc/ds/intstack.hpp"
#include <iostream>


BEGIN_TEST(stack_create)
    size_t size = 10;
    ds::IntStack stack(size);

    ASSERT_EQUAL(stack.capacity(), size);

END_TEST

BEGIN_TEST(stack_copy)
    size_t size = 10;
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
    }
    ds::IntStack& copy{stack};

    ASSERT_EQUAL(stack.size(), copy.size());

END_TEST

BEGIN_TEST(stack_copy_initialization)
    size_t size = 10;
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
    }
    ds::IntStack& copy = stack;

    ASSERT_EQUAL(stack.size(), copy.size());

END_TEST

BEGIN_TEST(stack_copy_assignment)
    size_t size = 10;
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
    }
    ds::IntStack copy;

    copy = stack;

    ASSERT_EQUAL(stack.size(), copy.size());

END_TEST

BEGIN_TEST(stack_push)
    size_t size = 10;
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
    }

    ASSERT_EQUAL(stack.size(), size);

END_TEST

BEGIN_TEST(stack_pop)
    size_t size = 10;
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
    }
    size_t x = stack.pop();

    ASSERT_EQUAL(x, size - 1);

END_TEST

BEGIN_TEST(stack_top)
    size_t size = 10;
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
    }
    int x = stack.top();
    int compare = (int)(size - 1);
    ASSERT_EQUAL(x, compare);

END_TEST

BEGIN_TEST(stack_capacity)
    size_t size = 10;
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
    }

    ASSERT_EQUAL(stack.capacity(), capacity);

END_TEST

BEGIN_TEST(stack_size)
    size_t size = 10;
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
    }

    ASSERT_EQUAL(stack.size(), size);

END_TEST

BEGIN_TEST(stack_is_empty)
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    ASSERT_EQUAL(stack.is_empty(), true);

END_TEST

BEGIN_TEST(stack_is_full)
    size_t capacity = 20;
    ds::IntStack stack(capacity);

    for(size_t i = 0; i < capacity; ++i) {
        stack.push(i);
    }

    ASSERT_EQUAL(stack.is_full(), true);

END_TEST

BEGIN_TEST(stack_drain)
    size_t size = 5;
    size_t capacity = 20;
    ds::IntStack stack(capacity);
    ds::IntStack drain(capacity);

    for(size_t i = 0; i < size; ++i) {
        stack.push(i);
        drain.push(i*2);
    }
    stack.StackDrain(drain);

    ASSERT_EQUAL(stack.size(), size*2);

END_TEST

BEGIN_TEST(stack_spill)
    size_t size = 5;
    size_t capacity = 20;
    ds::IntStack stack(capacity);
    ds::IntStack drain(capacity);

    for(size_t i = 0; i < size; ++i) {
        drain.push(i);
    }
    stack.StackSpill(drain);
    int item = stack.pop();
    ASSERT_EQUAL(item, 0);

END_TEST

BEGIN_TEST(stack_swap)
    size_t capacity = 20;
    size_t size = 5;
    ds::IntStack stack1(capacity);
    ds::IntStack stack2(capacity);

    for(size_t i = 1; i < size+1; ++i) {
        stack1.push(i);
        stack2.push(i+size);
    }

    stack1.StackSwap(stack2);

    ASSERT_EQUAL(stack1.top(), 10);

END_TEST



TEST_SUITE(Rational unit tests)
	TEST(stack_create)
	TEST(stack_copy)
	TEST(stack_copy_initialization)
	TEST(stack_copy_assignment)
	TEST(stack_push)
	TEST(stack_pop)
	TEST(stack_top)
	TEST(stack_capacity)
	TEST(stack_size)
	TEST(stack_is_empty)
	TEST(stack_is_full)
	TEST(stack_drain)
	TEST(stack_spill)
	TEST(stack_swap)

END_SUITE