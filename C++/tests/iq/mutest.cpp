#include "mu_test.h"
#include "containers.hpp"
#include <stack>
#include <memory>
#include <functional>
#include <stdexcept>
#include <vector>
#include <unordered_map>

BEGIN_TEST(min_stack_test)
{
    auto compare = [](const int& a, const int& b) { return a < b; };
    iq::MinStack<int> stack(compare);

    auto ptr1 = std::make_shared<int>(10);
    auto ptr2 = std::make_shared<int>(5);
    auto ptr3 = std::make_shared<int>(20);

    stack.push(ptr1);
    ASSERT_EQUAL(*stack.getMin(), 10);

    stack.push(ptr2);
    ASSERT_EQUAL(*stack.getMin(), 5);

    stack.push(ptr3);
    ASSERT_EQUAL(*stack.getMin(), 5);

    stack.pop();
    ASSERT_EQUAL(*stack.getMin(), 5);

    stack.pop();
    ASSERT_EQUAL(*stack.getMin(), 10);
}
END_TEST

BEGIN_TEST(resettable_slots_test)
{
    auto initial_value = std::make_shared<int>(42);
    iq::ResettableSlots<int> slots(10, initial_value);

    for (uint32_t i = 0; i < 10; ++i) {
        ASSERT_EQUAL(*slots.get(i), 42);
    }

    auto new_value = std::make_shared<int>(10);
    slots.set(4, new_value);
    ASSERT_EQUAL(*slots.get(4), 10);

    auto reset_value = std::make_shared<int>(77);
    slots.reset(reset_value);

    for (uint32_t i = 0; i < 10; ++i) {
        ASSERT_EQUAL(*slots.get(i), 77);
    }

    auto another_value = std::make_shared<int>(888);
    slots.set(1, another_value);
    ASSERT_EQUAL(*slots.get(1), 888);
    ASSERT_EQUAL(*slots.get(3), 77);
}
END_TEST

TEST_SUITE(MinStack and Resettable unit tests)
	TEST(min_stack_test)
	TEST(resettable_slots_test)

END_SUITE