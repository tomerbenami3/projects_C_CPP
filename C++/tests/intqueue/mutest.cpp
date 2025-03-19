#include "../../inc/mu_test.h"
#include "../../inc/ds/intstack.hpp"
#include "../../inc/ds/intqueue.hpp"
#include <iostream>

BEGIN_TEST(queue_create)
    size_t size = 128;
    ds::IntQueue queue(size);

    ASSERT_EQUAL(queue.capacity(), size);

END_TEST

BEGIN_TEST(queue_copy)
    size_t size = 100;
    ds::IntQueue queue(size);

    for(size_t i = 0; i < size / 2; ++i) {
        queue.enqueue(i);
    }
    ds::IntQueue& copy{queue};

    ASSERT_EQUAL(queue.size(), copy.size());

END_TEST

BEGIN_TEST(queue_copy_initialization)
    size_t size = 100;
    ds::IntQueue queue(size);

    for(size_t i = 0; i < size / 2; ++i) {
        queue.enqueue(i);
    }
    ds::IntQueue& copy = queue;

    ASSERT_EQUAL(queue.size(), copy.size());

END_TEST

BEGIN_TEST(queue_copy_assignment)
    size_t size = 100;
    ds::IntQueue queue(size);

    for(size_t i = 0; i < 10; ++i) {
        queue.enqueue(i);
    }
    ds::IntQueue copy;

    copy = queue;

    ASSERT_EQUAL(queue.size(), copy.size());

END_TEST

BEGIN_TEST(queue_enqueue)
    size_t size = 100;
    ds::IntQueue queue(size);

    for(size_t i = 0; i < 10; ++i) {
        queue.enqueue(i);
    }

    ASSERT_EQUAL(queue.size(), 10);

END_TEST

BEGIN_TEST(queue_dequeue)
    size_t size = 100;
    ds::IntQueue queue(size);

    for(size_t i = 0; i < 10; ++i) {
        queue.enqueue(i);
    }
    queue.enqueue(99);

    int number = queue.dequeue();

    ASSERT_EQUAL(number, 0);

END_TEST

BEGIN_TEST(queue_clear)
    size_t size = 100;
    ds::IntQueue queue(size);

    for(size_t i = 0; i < 10; ++i) {
        queue.enqueue(i);
    }
    queue.enqueue(99);

    for(size_t i = 0; i < 5; ++i) {
        queue.dequeue();
    }

    for(size_t i = 0; i < 10; ++i) {
        queue.enqueue(i);
    }
    queue.clear();

    ASSERT_EQUAL(queue.size(), 0);

END_TEST

TEST_SUITE(IntQueue unit tests)

	TEST(queue_create)
	TEST(queue_copy)
	TEST(queue_copy_initialization)
	TEST(queue_copy_assignment)
	TEST(queue_enqueue)
	TEST(queue_dequeue)
	TEST(queue_clear)

END_SUITE