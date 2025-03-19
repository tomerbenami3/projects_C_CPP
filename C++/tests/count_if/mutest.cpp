#include "mu_test.h"
#include "count_if.hpp"

#include <vector>
#include <list>

BEGIN_TEST(vector_int)
    std::vector<int> v = {2,5,7,3,5,7,1,3,2};
    auto is_even = [](int count, int x) { count+= x % 2 == 0; return count; };
    size_t count_even = algo::count_if(v.begin(), v.end(), is_even);
    ASSERT_EQUAL(count_even, 2);
END_TEST

BEGIN_TEST(vector_double)
    std::list<double> v = {2,5,7,3,5,7,1,3,2};
    auto is_even = [](double count, double x) { count+= x > 2; return count; };

    size_t count_greater_than_two = algo::count_if(v.begin(), v.end(), is_even);
    ASSERT_EQUAL(count_greater_than_two, 6);
END_TEST

TEST_SUITE(count_if unit tests)
	TEST(vector_int)
	TEST(vector_double)

END_SUITE