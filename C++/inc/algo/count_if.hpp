#ifndef ALGO_COUNT_IF_H
#define ALGO_COUNT_IF_H

#include <cstddef>
#include <numeric>

namespace algo {
template <typename Iterator, typename Predicate>
size_t count_if(Iterator begin, Iterator end, Predicate predicate)
{
    return std::accumulate(begin, end, 0 ,predicate);

}

template <typename Predicate1, typename Predicate2>
size_t count_if(Iterator begin, Iterator end, Predicate predicate)
{
    return std::accumulate(begin, end, 0 ,predicate);

}

};

#endif // ALGO_COUNT_IF_H