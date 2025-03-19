#include "mu_test.h"
#include "object_pool.hpp"
#include <iostream>
#include <cassert>

BEGIN_TEST(test_no_ramp_policy_exception)
{
    auto pool = dp::ObjectPool<int, dp::NoRampPolicy<int>>::create(1, dp::NoRampPolicy<int>(), dp::ObjectFactory<int>());

    auto obj1 = pool->take();

    bool exceptionThrown = false;
    try {
        auto obj2 = pool->take();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    ASSERT_THAT(exceptionThrown);
}
END_TEST


BEGIN_TEST(test_ramp_up_policy_expansion)
{
    auto pool = dp::ObjectPool<int, dp::RampUpPolicy<int>>::create(2, dp::RampUpPolicy<int>(3), dp::ObjectFactory<int>());

    auto obj1 = pool->take();
    auto obj2 = pool->take();
    auto obj3 = pool->take();  // Should expand

    bool exceptionThrown = false;
    try {
        auto obj4 = pool->take();  // Should expand
        auto obj5 = pool->take();  // Should expand - max
        auto obj6 = pool->take();  // Overflow
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }

    ASSERT_THAT(exceptionThrown);
}
END_TEST



BEGIN_TEST(test_object_recycling)
{
    auto pool = dp::ObjectPool<int, dp::NoRampPolicy<int>>::create(2, dp::NoRampPolicy<int>(), dp::ObjectFactory<int>());

    {
        auto obj1 = pool->take();
        *obj1 = 42;
    }

    auto obj2 = pool->take();
    ASSERT_THAT(*obj2 == 42);
}
END_TEST

BEGIN_TEST(test_shrink_back_policy)
{
    auto pool = dp::ObjectPool<int, dp::RampUpPolicy<int>, dp::ObjectFactory<int>>::create(2, dp::RampUpPolicy<int>(5), dp::ObjectFactory<int>());

    {
        auto obj1 = pool->take();
        auto obj2 = pool->take();
        auto obj3 = pool->take(); // Pool size expanded
    }  // objects go out of scope

    // pool should shrink back to its initial sizee
    ASSERT_THAT(pool->size() == 2);  // Should be back to initial size
}
END_TEST

BEGIN_TEST(test_pool_destruction_with_active_objects)
{
    std::weak_ptr<dp::ObjectPool<int, dp::RampUpPolicy<int>>> weakPoolRef;
    std::shared_ptr<int> obj1, obj2;

    {
        auto pool = dp::ObjectPool<int, dp::RampUpPolicy<int>>::create(2, dp::RampUpPolicy<int>(3), dp::ObjectFactory<int>());

        weakPoolRef = pool;

        obj1 = pool->take();
        obj2 = pool->take();

        ASSERT_THAT(!weakPoolRef.expired());
    }

    ASSERT_THAT(!weakPoolRef.expired());

    obj1.reset();
    ASSERT_THAT(!weakPoolRef.expired());

    obj2.reset();
    ASSERT_THAT(weakPoolRef.expired());
}
END_TEST 

BEGIN_SUITE(Object Pool Tests)

    TEST(test_no_ramp_policy_exception)
    TEST(test_ramp_up_policy_expansion)
    TEST(test_object_recycling)
    TEST(test_shrink_back_policy)
    TEST(test_pool_destruction_with_active_objects)

END_SUITE
