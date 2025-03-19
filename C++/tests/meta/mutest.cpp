#include "mu_test.h"
#include "meta.hpp"

using namespace meta;

BEGIN_TEST(bit_count1)
    constexpr int check = bit_count_v<3>;
    ASSERT_EQUAL(check, 2);
END_TEST

BEGIN_TEST(bit_count2)
    constexpr int check = bit_count_v<15>;
    ASSERT_EQUAL(check, 4);
END_TEST

BEGIN_TEST(power1)
    constexpr uint64_t check = power_v<2, 10>();
    ASSERT_EQUAL(check, 1024);
END_TEST

BEGIN_TEST(power2)
    constexpr uint64_t check = power_v<5, 4>();
    ASSERT_EQUAL(check, 625);
END_TEST


BEGIN_SUITE(constexpr_tests)

    TEST(bit_count1)
    TEST(bit_count2)
    TEST(power1)
    TEST(power2)

END_SUITE
