#ifndef SFINAE_HPP
#define SFINAE_HPP

#include <cstddef>
#include <type_traits>
#include <numeric>
#include <iostream>


namespace sfinae {

template <typename T>
typename std::enable_if_t<std::is_arithmetic_v<T>, T>
square(T const& value)
{
    std::cout << "here 1";
    return value * value;
}

template <typename Container>
typename std::enable_if<!std::is_arithmetic_v<Container> &&
        std::is_arithmetic_v<typename Container::value_type>,
    typename Container::value_type>::type square(const Container& container) 
    {
        std::cout << "here 2";
        return 
            std::accumulate(container.begin(), container.end(), 
            typename Container::value_type(0), 
            [](auto sum, auto val) { return sum + val * val; });
    }

}

#endif //SFINAE_HPP