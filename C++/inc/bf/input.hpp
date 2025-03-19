#ifndef BF_INPUT_H
#define BF_INPUT_H

#include <string>
#include <iostream>

namespace bf {

class Input {
public:
    Input(std::istream& m_is = std::cin);
    ~Input() = default;

    char read_char();
    // bool validate_brackets();
    // size_t get_jump_address();

    // size_t get_position();
    // void set_position(size_t position);
    // size_t size();


private:
    std::istream& m_istream;
};

}

#endif // BF_INPUT_H