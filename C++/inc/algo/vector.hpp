#include <vector>
#include <iterator>
#include <ctime>
#include <random>
#include <iostream>

namespace algo {

template <typename Iter>
void swap(Iter begin, Iter end);

template <typename Iter>
Iter partition(Iter begin, Iter end);

template <typename Iter>
void quicksort(Iter begin, Iter end);

template <typename Iter>
void shuffle(Iter begin, Iter end);


template <typename Iter>
void print(Iter begin, Iter end, std::ostream& os = std::cout, char const seperator = ',')
{
    os << "[";
    while(begin != end) {
        if(begin < end - 1) {
            os << *begin++ << seperator;
        } else {
            os << *begin++;
        }
    }
    os << "]";
    os << std::endl;
}


template <typename Iter>
void quicksort(Iter begin, Iter end)
{
    if(begin == end || begin == end - 1) {
        return;
    }

    Iter pivot_index = partition(begin, end);

    quicksort(begin, pivot_index);
    quicksort(pivot_index + 1, end);
}

template <typename Iter>
Iter partition(Iter begin, Iter end)
{
    // Iter pivot = begin;
    typename Iter::value_type pivot = *begin;
    Iter small_index = begin;
    Iter big_index = end;
    --big_index;

    while(true) {

        while(*small_index < pivot) {
            ++small_index;
        }

        while(*big_index > pivot) {
            --big_index;
        }

        if(small_index >= big_index) {
            break;
        }

        typename Iter::value_type temp = *small_index;
        *small_index = *big_index;
        *big_index = temp;

        ++small_index;
        --big_index;
    }

    typename Iter::value_type temp = *begin;
    // Iter temp = *begin;

    *begin = *big_index;
    *big_index = temp;

    return big_index; 
}

template <typename Iter>
void swap(Iter begin, Iter end)
{
    std::swap(begin, end);
}

template <typename Iter>
void shuffle(Iter begin, Iter end)
{
    size_t size = std::distance(begin, end);
    srand(time(NULL));

    while(begin != end) {

        std::swap(*begin, *(begin + (rand() % size)));

        ++begin;
        --size;
    }
}




}