#ifndef UDL_HPP
#define UDL_HPP

#include <cstddef>


namespace meta {

template <uint64_t N>
constexpr uint64_t bit_count_v = (N == 0) ? 0 : (N & 1) + bit_count_v<(N >> 1)>;

// template <uint64_t Base, uint64_t Exponent>
// constexpr uint64_t power_v = Base * power_v<Base, Exponent - 1>;

template <uint64_t Base, uint64_t Exponent>
constexpr uint64_t power_v() {
    if constexpr (Exponent == 0)
        return 1;
    else if constexpr (Exponent % 2 == 0)
        return power_v<Base * Base, Exponent / 2>();
    else
        return Base * power_v<Base * Base, (Exponent - 1) / 2>();
}

}

#endif //UDL_HPP