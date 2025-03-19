#include "mu_test.h"
#include "sfinae.hpp"

using namespace sfinae;

BEGIN_TEST(square_int)
    auto check = square(4);
    ASSERT_EQUAL(check, 16);
END_TEST

BEGIN_TEST(square_double)
    auto check = square(2.5);
    ASSERT_EQUAL(check, 6.25);
END_TEST

BEGIN_TEST(square_vector_int)
    std::vector<int> vec = {1, 2, 3, 4}; 
    auto check = square(vec);  // 1^2 + 2^2 + 3^2 + 4^2 = 30
    ASSERT_EQUAL(check, 30);
END_TEST

BEGIN_SUITE(constexpr_tests)

    TEST(square_int)
    TEST(square_double)
    TEST(square_vector_int)

END_SUITE
