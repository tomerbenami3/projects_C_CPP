#ifndef BF_COMPILER_H
#define BF_COMPILER_H

#include "input.hpp"
#include <string>
#include <vector>

namespace bf {

enum class Instruction {
    INC, DEC, LEFT, RIGHT, PRINT, READ, BEGIN_LOOP, END_LOOP, HALT
};

class Compiler
{
public:
    Compiler();
    ~Compiler() = default;

    // size_t get_jump_address();
    size_t get_position();
    void set_position(size_t position);
    size_t size();

    std::vector<Instruction> compile(const std::string& buffer);

private:
    std::string m_buffer;
    size_t m_pos;
};

bool validate_brackets();
bool validate_char(char ch);
    
}

#endif // BF_COMPILER_H