#include "mu_test.h"
#include "thread_pool_executor.hpp"
#include <iostream>

const size_t QUEUE_CAPACITY = 10;


BEGIN_TEST(test_thread_pool_basic)
{
    mt::ThreadPoolExecutor<QUEUE_CAPACITY> pool(2);
    pool.shutdown_immediate();
    ASSERT_THAT(true);
}
END_TEST

BEGIN_TEST(test_submit_trivial_case)
{
    mt::ThreadPoolExecutor<QUEUE_CAPACITY> pool(10);
    for (int i=0; i< 10; ++i){
        pool.submit([]{
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
    }

    pool.shutdown_graceful();

    ASSERT_THAT(1);
}
END_TEST

BEGIN_TEST(test_submit_more_tasks_then_threads)
{
    mt::ThreadPoolExecutor<10> pool(5);
    for (int i = 0; i < 20; ++i){
        pool.submit([]{
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
    }
    pool.shutdown_immediate();

    ASSERT_THAT(1);
}
END_TEST

BEGIN_TEST(test_submit_more_threads_then_tasks)
{
    mt::ThreadPoolExecutor<10> pool(15);
    for (int i = 0; i< 12; ++i){
        pool.submit([]{
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
    }
    pool.shutdown_immediate();

    ASSERT_THAT(1);
    // new code 2 - main
}
END_TEST


BEGIN_TEST(test_thread_pool_tasks_size)
{
    mt::ThreadPoolExecutor<QUEUE_CAPACITY> pool(36);
    pool.submit([]() { std::this_thread::sleep_for(std::chrono::milliseconds(100)); });

    pool.shutdown_graceful();
    ASSERT_EQUAL(pool.worker_size(), 0);
    // a new code
}
END_TEST

BEGIN_TEST(test_thread_pool_worker_size)
{
    constexpr size_t WORKER_COUNT = 3;
    mt::ThreadPoolExecutor<QUEUE_CAPACITY> pool(WORKER_COUNT);

    ASSERT_THAT(pool.worker_size() == WORKER_COUNT);
    pool.shutdown_graceful();
}
END_TEST

BEGIN_TEST(test_thread_pool_add_workers)
{
    constexpr size_t INITIAL_WORKERS = 2;
    constexpr size_t WORKERS_TO_ADD = 3;

    mt::ThreadPoolExecutor<QUEUE_CAPACITY> pool(INITIAL_WORKERS);

    size_t added = pool.add_workers(WORKERS_TO_ADD);
    size_t expected_total = INITIAL_WORKERS + added;

    ASSERT_THAT(pool.worker_size() == expected_total);
    pool.shutdown_graceful();
}
END_TEST


BEGIN_SUITE(ThreadPoolExecutor Basic Test)

    TEST(test_thread_pool_basic)
    TEST(test_submit_trivial_case)
    TEST(test_submit_more_tasks_then_threads)
    TEST(test_submit_more_threads_then_tasks)
    TEST(test_thread_pool_tasks_size)
    TEST(test_thread_pool_worker_size)
    TEST(test_thread_pool_add_workers)

END_SUITE
