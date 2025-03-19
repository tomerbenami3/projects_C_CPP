#include <cstdint>
#include <iostream>

int CountBits(uint64_t num)
{
    uint64_t mask = 1;
    int count = 0;

    while(mask != 0) {
        if((num & mask) != 0) {
            ++count;
        }
        mask <<= 1;
    }

    return count;
}

int CheckPairs(uint64_t num) {
    uint64_t mask = 3;
    int count = 0;

    while(num != 0) {
        if((num & mask) == 3) {
            ++count;
        }
        num >>= 1;
    }
    return count;
}

int ToggleForMaxPairs(uint64_t num) {
    int max_pairs = CheckPairs(num);
    uint64_t mask = 1;
    int bit_index = 0;

    while(bit_index < 64) {
        if((num & mask) == 0) {
            uint64_t toggled_num = num | mask;
            int current_pairs = CheckPairs(toggled_num);
            if (current_pairs > max_pairs) {
                max_pairs = current_pairs;
            }
        }
        mask <<= 1;
        ++bit_index;
    }
    return max_pairs;
}


int main() {
    uint64_t num = 819; // 1100110011
    uint64_t num2 = 947; //1100110011
    uint64_t num3 = 951; //1110110111
    int on_bits;
    int pairs;
    int maxpairs;

    on_bits = CountBits(num);
    std::cout << on_bits << " bits are on\n";
    on_bits = CountBits(num2);
    std::cout << on_bits << " bits are on\n";
    on_bits = CountBits(num3);
    std::cout << on_bits << " bits are on\n";
    pairs = CheckPairs(num);
    std::cout << pairs << " pairs\n";
    pairs = CheckPairs(num2);
    std::cout << pairs << " pairs\n";
    pairs = CheckPairs(num3);
    std::cout << pairs << " pairs\n";

    maxpairs = ToggleForMaxPairs(num3);
    std::cout << maxpairs << " max pairs\n";
}