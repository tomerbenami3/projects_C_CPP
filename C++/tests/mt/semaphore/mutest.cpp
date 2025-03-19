#include "mu_test.h"
#include "semaphore.hpp"
#include <thread>

BEGIN_TEST(test_semaphore_basic)
{
    mt::MySemaphore sem(1);
    sem.acquire();
    sem.release();
    ASSERT_THAT(true);
}
END_TEST

BEGIN_TEST(test_semaphore_thread)
{
    mt::MySemaphore sem(0);

    std::thread t([&]() {
        sem.release();
    });

    sem.acquire();
    ASSERT_THAT(true);

    t.join();
}
END_TEST

BEGIN_TEST(test_semaphore_two_threads)
{
    mt::MySemaphore sem(1);
    bool thread_ran = false;

    std::thread t([&]() {
        sem.acquire();
        thread_ran = true;
        sem.release();
    });

    t.join();
    ASSERT_THAT(thread_ran);
}

END_TEST

BEGIN_SUITE(Simplest Semaphore Tests)
    TEST(test_semaphore_basic)
    TEST(test_semaphore_thread)
    TEST(test_semaphore_two_threads)
END_SUITE
