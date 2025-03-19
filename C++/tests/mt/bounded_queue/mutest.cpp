#include "mu_test.h"
#include "bounded_queue.hpp"
#include <iostream>
#include <thread>

BEGIN_TEST(test_enqueue_dequeue)
{
    mt::BoundedQueue<int, 5> queue;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    ASSERT_THAT(queue.size() == 3);

    int val1 = queue.dequeue();
    int val2 = queue.dequeue();
    
    ASSERT_THAT(val1 == 10);
    ASSERT_THAT(val2 == 20);
    ASSERT_THAT(queue.size() == 1);
}
END_TEST

BEGIN_TEST(test_clear_queue)
{
    mt::BoundedQueue<int, 5> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    queue.clear();
    ASSERT_THAT(queue.is_empty());
}
END_TEST

BEGIN_TEST(test_queue_full)
{
    mt::BoundedQueue<int, 3> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    ASSERT_THAT(queue.is_full());

    int val = queue.dequeue();
    ASSERT_THAT(val == 1);
    ASSERT_THAT(!queue.is_full());
}
END_TEST

BEGIN_TEST(test_queue_empty)
{
    mt::BoundedQueue<int, 3> queue;

    ASSERT_THAT(queue.is_empty());

    queue.enqueue(42);
    ASSERT_THAT(!queue.is_empty());

    int val = queue.dequeue();
    ASSERT_THAT(queue.is_empty());
    ASSERT_THAT(val == 42);
}
END_TEST

BEGIN_TEST(test_multithreading)
{
    mt::BoundedQueue<int, 10> queue;

    auto producer = [&queue]() {
        for (int i = 0; i < 5; ++i) {
            queue.enqueue(i);
        }
    };

    auto consumer = [&queue]() {
        for (int i = 0; i < 5; ++i) {
            queue.dequeue();
        }
    };

    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    ASSERT_THAT(queue.is_empty());
}
END_TEST

BEGIN_TEST(test_concurrent_enqueues)
{
    mt::BoundedQueue<int, 10> queue;

    auto producer = [&queue](int start) {
        for (int i = start; i < start + 5; ++i) {
            queue.enqueue(i);
        }
    };

    std::thread t1(producer, 0);
    std::thread t2(producer, 5);

    t1.join();
    t2.join();

    ASSERT_THAT(queue.size() == 10);
}
END_TEST

BEGIN_TEST(test_concurrent_dequeues)
{
    mt::BoundedQueue<int, 10> queue;

    for (int i = 0; i < 10; ++i) {
        queue.enqueue(i);
    }

    auto consumer = [&queue]() {
        for (int i = 0; i < 5; ++i) {
            queue.dequeue();
        }
    };

    std::thread t1(consumer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    ASSERT_THAT(queue.is_empty());
}
END_TEST

BEGIN_SUITE(Bounded Queue Thread-Safe Tests)
    TEST(test_enqueue_dequeue)
    TEST(test_clear_queue)
    TEST(test_queue_full)
    TEST(test_queue_empty)
    TEST(test_multithreading)
    TEST(test_concurrent_enqueues)
    TEST(test_concurrent_dequeues)
END_SUITE
