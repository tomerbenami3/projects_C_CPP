#include "compiler.hpp"
#include "input.hpp"
#include <vector>

namespace bf {


Compiler::Compiler()
{
}

bool validate_brackets(std::string buffer)
{
    double counter = 0;

    for(size_t index = 0; buffer[index] != '\0'; ++index) {
        if(counter < 0) {
            break;
        }
        if(buffer[index] == '[') {
            ++counter;
        } else if(buffer[index] == ']') {
            --counter;
        }
    }

    return counter == 0;
}

// size_t Compiler::get_jump_address()
// {
//     size_t temp = m_pos;

//     while(m_buffer[temp] != ']') {
//         ++temp;
//     }

//     return temp+1;
// }

size_t Compiler::size()
{
    return m_buffer.size();
}

size_t Compiler::get_position()
{
    return m_pos;
}

void Compiler::set_position(size_t position)
{
    m_pos = position;
}

std::vector<Instruction> Compiler::compile(const std::string& buffer)
{

    if(!validate_brackets(buffer)) {
        std::cout << "compilation error";
        exit(1);
    }

    std::vector<Instruction> instructions;

    for (char ch : buffer) {
        switch (ch) {
            case '+':
                instructions.push_back(Instruction::INC);
                break;
            case '-':
                instructions.push_back(Instruction::DEC);
                break;
            case '<':
                instructions.push_back(Instruction::LEFT);
                break;
            case '>':
                instructions.push_back(Instruction::RIGHT);
                break;
            case '.':
                instructions.push_back(Instruction::PRINT);
                break;
            case ',':
                instructions.push_back(Instruction::READ);
                break;
            case '[':
                instructions.push_back(Instruction::BEGIN_LOOP);
                break;
            case ']':
                instructions.push_back(Instruction::END_LOOP);
                break;
            default:
                break;
        }
    }

    instructions.push_back(Instruction::HALT);

    return instructions;
}

bool validate_char(char ch)
{
    std::string code = "[].,+-><";
    if(static_cast<int>(code.find(ch)) != -1) {
        return true;
    }
    return false;
}

}
