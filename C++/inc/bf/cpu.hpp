#ifndef BF_CPU_H
#define BF_CPU_H

#include "memory.hpp"
#include "input.hpp"
#include "output.hpp"
#include "compiler.hpp"
#include <vector>
#include <stack>
#include <array>

namespace bf {

class Cpu {
public:
    Cpu(size_t memory_size);
    ~Cpu() = default;

    void print();
    void read();
    void beginloop();
    void endloop();
    void halt();
    void execute(std::vector<Instruction> instructions);
    size_t get_jump_address();

private:
    Memory m_memory;
    Input m_command;
    Output m_output;
    Compiler m_compiler;
    std::stack<size_t> m_stack;
    std::array<std::function<void()>, 9> m_functions;
    size_t inst_index;
};
   
}

#endif // BF_CPU_H