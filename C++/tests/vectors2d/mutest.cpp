#include "../../inc/mu_test.h"
#include "../../inc/algebra/vectors2d.hpp"
#include <cmath>

template<typename T, typename Output>
Output add(T item) {
    return item[0] + item[1];
}

template<typename T>
bool compare(T lhs, T rhs) {
    return lhs[0] == rhs[0] && lhs[1] == rhs[1];
}

template<typename T, typename Output>
Output normalize(T item) {
   return std::sqrt((std::pow(item[0],2)) + (std::pow(item[1],2)));
}

template<typename Output>
Output reduce(Output item, Output total) {
   return item + total;
}

BEGIN_TEST(vector_generate)
    algebra::Vector2i v;

    v = algebra::generate<algebra::Vector2i>();
    ASSERT_THAT(!algebra::is_diminshing(v));
END_TEST

BEGIN_TEST(vector_fill_array)
    algebra::Vector2i v[5];
    algebra::fill(v, v + 5);

    ASSERT_THAT(!algebra::is_diminshing(v[0]));
    ASSERT_THAT(!algebra::is_diminshing(v[1]));
    ASSERT_THAT(!algebra::is_diminshing(v[2]));
    ASSERT_THAT(!algebra::is_diminshing(v[3]));
    ASSERT_THAT(!algebra::is_diminshing(v[4]));

END_TEST

BEGIN_TEST(vector_transform_array_int)
    algebra::Vector2i v[5] = { {1, 2}, {3, 4}, {6 , 7}, {1, 2}, {3, 4}};
    int w[5];
    algebra::transform_function<algebra::Vector2i>(v, v + 5, w, add<algebra::Vector2i,int>);
    ASSERT_EQUAL(w[0], 3);
    ASSERT_EQUAL(w[1], 7);
    ASSERT_EQUAL(w[2], 13);

END_TEST

BEGIN_TEST(vector_transform_array_float)
    algebra::Vector2f v[2];
    v[0][0] = 0.25;
    v[0][1] = 0.25;
    v[1][0] = 2;
    v[1][1] = 2;
    double w[5];
    algebra::transform_function<algebra::Vector2f>(v, v + 5, w, add<algebra::Vector2f,double>);
    ASSERT_EQUAL(w[0], 0.5);

END_TEST

BEGIN_TEST(vector_binary_function_array)
    algebra::Vector2i v[5] = { {1, 2}, {3, 4}, {6 , 7}, {1, 2}, {3, 4}};
    algebra::Vector2i w[5] = { {1, 2}, {3, 4}, {4 , 4}, {31, 123}, {3, 4}};
    bool bi_array[5];
    algebra::transform_function(v, v + 5, w, bi_array, compare<algebra::Vector2i>);
    ASSERT_EQUAL(bi_array[0], 1);
    ASSERT_EQUAL(bi_array[1], 1);
    ASSERT_EQUAL(bi_array[2], 0);
    ASSERT_EQUAL(bi_array[3], 0);
    ASSERT_EQUAL(bi_array[4], 1);

END_TEST

BEGIN_TEST(vector_transform_and_reduce)
    algebra::Vector2i v[2] = { {3, 4}, {3, 4}};
    double initial = 0.0;
    double res = algebra::transform_reduce_function<algebra::Vector2i, double>(v, v + 2, initial, normalize<algebra::Vector2i, double>, reduce<double>);
    ASSERT_EQUAL(res, 10);

END_TEST


TEST_SUITE(Vector unit tests)
	TEST(vector_generate)
	TEST(vector_fill_array)
	TEST(vector_transform_array_int)
	TEST(vector_transform_array_float)
	TEST(vector_binary_function_array)
	TEST(vector_transform_and_reduce)

END_SUITE