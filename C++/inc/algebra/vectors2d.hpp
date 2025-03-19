#ifndef ALGEBRA_VECTOR_HPP
#define ALGEBRA_VECTOR_HPP

#include <cstddef>
#include <iostream>
#include <cmath>
#include <cassert>
#include "rational.hpp"

namespace algebra {

struct Vector2f {
    typedef double value_type;
    double x;
    double y;

    Vector2f(value_type x = 0, value_type y = 0) 
    : x{x}
    , y{y} 
    {

    }

    value_type& operator[](int i) {
        return i == 0? x : y;
    }
    value_type const& operator[](int i) const {
        return i == 0? x : y;
    }
};

struct Vector2i {
    typedef double value_type;
    value_type x;
    value_type y;

    Vector2i(value_type x = 0, value_type y = 0) 
    : x{x}
    , y{y} 
    {

    }

    value_type& operator[](int i) {
        return i == 0? x : y;
    }

    value_type const& operator[](int i) const {
        return i == 0? x : y;
    }
};

/// @brief check if vectors are empty
/// @tparam T type
/// @param v vector
/// @return true if empty, flase if not empty
template<typename T>
bool is_diminshing(T v)
{
    return v[0] == 0 && v[1] == 0;
}

/// @brief generates a new vector
/// @tparam T 
/// @return 
template<typename T>
T generate()
{
    T v;
    typename T::value_type x = rand() % 100;
    typename T::value_type y = rand() % 100;

    return T{x, y};
}

/// @brief fill existing vector with desired type
/// @tparam T type
/// @param begin start of the array
/// @param end end of the array
template<typename T>
void fill(T* begin, T* end)
{
    if(begin == nullptr || end == nullptr) {
        return;
    }
    intptr_t size = end - begin;
    assert(size > 0);
    intptr_t i = 0;

    while(begin + i != end) {
        begin[i] = generate<T>();
        ++i;
    }
}

/// @brief apply a function on every member in the array and fill the result in Output
/// @tparam T type of member
/// @tparam Output the type of the output array
/// @tparam F function pointer
/// @param begin start address of the array
/// @param end end address of the array
/// @param output_begin start of the target array
/// @param func function to apply on all the members
template<typename T, typename Output, typename F>
intptr_t transform_function(T* begin, T* end, Output* output_begin, F* func)
{
    if(begin == nullptr || end == nullptr) {
        return -1;
    }
    intptr_t size = end - begin;
    assert(size > 0);

    intptr_t i = 0;
    while(begin + i != end) {
        output_begin[i] = func(begin[i]);
        ++i;
    }
    return size;
}

/// @brief apply a binary function on all elements in two arrays and insert the result into boolean array
/// @tparam T type of the arrays
/// @tparam F pointer to function
/// @param first_begin start of the first array
/// @param first_end end of the first array
/// @param second_begin start of the second array
/// @param bi_array boolean array - target
/// @param bi_func function to apply
template<typename T, typename F>
intptr_t transform_function(T* first_begin, T* first_end, T* second_begin, bool* bi_array, F bi_func)
{
    if(first_begin == nullptr || first_end == nullptr || second_begin == nullptr || bi_array == nullptr) {
        return -1;
    }
    intptr_t size = first_end - first_begin;
    assert(size > 0);
    intptr_t i = 0;

    while(first_begin + i != first_end) {
        bi_array[i] = bi_func(first_begin[i], second_begin[i]);
        ++i;
    }
    return size;
}

/// @brief calculate the normal and reduce of all the elements of an array
/// @tparam T type
/// @tparam REDUCE pointer to the reduce function
/// @tparam Output target array - holds the results
/// @tparam TRANSFORM pointer to the reduce function
/// @param begin start of the array
/// @param end end of the array
/// @param output target array, holds the results
/// @param transforming_func pointer to normalize function
/// @param reduce_func pointer to reduce function
/// @return result
template<typename T, typename Output, typename TRANSFORM, typename REDUCE>
Output transform_reduce_function(T* begin, T* end, Output initial, TRANSFORM transforming_func, REDUCE reduce_func)
{
    if(begin == nullptr || end == nullptr) {
        return -1;
    }
    intptr_t i = 0;
    size_t size = end - begin;
    assert(size > 0);

    Output result = initial;

    while(begin + i != end) {
        result = reduce_func(transforming_func(begin[i]), result);
        ++i;
    }
    return result;
}


}

#endif // ALGEBRA_VECTOR_HPP
