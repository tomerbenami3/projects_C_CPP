#include "../../inc/mu_test.h"
#include "../../inc/algo/vector.hpp"
#include <vector>

BEGIN_TEST(vector_print)
    std::vector<int> vi = {1,2,3,4,5,6,7,8,9};
    algo::print(vi.begin(), vi.end(), std::cout);
    ASSERT_THAT(1);

END_TEST

BEGIN_TEST(vector_sort)
    std::vector<int> vi = {4,7,2,3,5,9,1,13,3};
    algo::quicksort(vi.begin(), vi.end());
    algo::print(vi.begin(), vi.end(), std::cout);
    ASSERT_THAT(1);

END_TEST

BEGIN_TEST(vector_shuffle)
    std::vector<int> vi = {1,2,3,4,5,6,7,8,9};
    algo::shuffle(vi.begin(), vi.end());
    algo::print(vi.begin(), vi.end(), std::cout);
    ASSERT_THAT(1);

END_TEST

//assdasaaaaaaaaaaaa
TEST_SUITE(vector unit tests)
	TEST(vector_print)
	TEST(vector_sort)
	TEST(vector_shuffle)

END_SUITE