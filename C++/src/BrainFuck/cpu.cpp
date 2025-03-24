#include "cpu.hpp"
#include <stack>
#include <string>


namespace bf {

Cpu::Cpu(size_t memory_size)
: m_memory(memory_size)
, m_compiler()
, m_stack()
, m_functions {
    [&]() { m_memory.add(); },
    [&]() { m_memory.sub(); },
    [&]() { m_memory.movleft(); },
    [&]() { m_memory.movright(); },
    [&]() { print(); },
    [&]() { read(); },
    [&]() { beginloop(); },
    [&]() { endloop(); },
    [&]() { halt(); },
}
, inst_index(0)
{
}

void Cpu::execute(std::vector<Instruction> instructions)
{
    while(1) {
        // std::cout << "loop number" << index << "\n";
        m_functions[static_cast<int>(instructions[inst_index])]();
        ++inst_index;
        }
    }

// void Cpu::beginloop() {

//     size_t jump_addr = m_compiler.get_jump_address();

//             if(m_memory.read() != 0) {
//                 m_stack.push(inst_index - 1);
//             } else {
//                 m_compiler.set_position(jump_addr);
//             }
// }

// void Cpu::endloop() {

//     if(m_stack.empty()) {
//         return;
//     }

//     size_t loop_addr = m_stack.top();
//     m_stack.pop();
//     m_compiler.set_position(loop_addr);
// }

void Cpu::beginloop()
{
    if(m_memory.read() != 0){
        if(!m_stack.empty()){
            m_stack.pop();
        }
        m_stack.push(inst_index - 1);
    }
    else{
        inst_index = m_stack.top();
        m_stack.pop();
    }
}

void Cpu::endloop()
{
    size_t temp = inst_index;
    inst_index = m_stack.top();
    m_stack.pop();
    m_stack.push(temp);
}

void Cpu::print()
{
    char ch = m_memory.read();
    m_output.print(ch);
}

void Cpu::read() {
    char ch = m_command.read_char();
    m_memory.write(ch);
}

void Cpu::halt() {
    std::cout << "exit from program";
    exit(1);
}

// size_t Cpu::get_jump_address()
// {
//     size_t temp = m_pos;
//     size_t depth = 0;

//     while (temp < m_buffer.size()) {
//         if (m_buffer[temp] == '[') {
//             ++depth; 
//         } else if (m_buffer[temp] == ']') {
//             --depth;
//             if (depth == 0) {
//                 return temp + 1;
//             }
//         }
//         ++temp;
//     }
//     return temp + 1;
// }

}