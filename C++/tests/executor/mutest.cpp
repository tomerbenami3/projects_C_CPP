#include "mu_test.h"
#include "periodic_executor.hpp"
#include "abstract_task.hpp"
#include "monotonic_clock.hpp"


class Task1 : public executor::AbstractTask
{
public:
    void run() override {
        std::cout << "Task1: Running first task!" << std::endl;
    }
};

class Task2 : public executor::AbstractTask
{
public:
    void run() override {
        std::cout << "Task2: Executing the second task!" << std::endl;
    }
};

class Task3 : public executor::AbstractTask
{
public:
    void run() override {
        std::cout << "Task3: Performing the third task!" << std::endl;
    }
};

BEGIN_TEST(test1)
    Task1 task1;
    Task2 task2;
    Task3 task3;
    executor::MonotonicClock mono;
    executor::PeriodicExecutor pe{mono};

    pe.addTask(task1, 3000, 3);
    pe.addTask(task2, 2000, 5);
    pe.addTask(task3, 4000, 9);

    pe.run();
    ASSERT_THAT(1);
END_TEST

TEST_SUITE(Periodic Executor unit tests)
	TEST(test1)

END_SUITE