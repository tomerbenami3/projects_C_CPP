#ifndef LC3_TRAP_H
#define LC3_TRAP_H

#include "memory.hpp"
#include "registerfile.hpp"
#include <array>
#include <functional>

namespace lc3 {


class Trap {
public:
    Trap(Memory& memory, RegisterFile& registers);
    ~Trap() = default;

    void execute(uint16_t trap_vector);

private:
    void getc();
    void out(); 
    void puts();
    void in(); 
    void putsp();
    void halt();

private:
    Memory& m_memory;
    RegisterFile& m_registers;
    std::array<std::function<void()>, 0x26> m_functions;
};


}


#endif // LC3_TRAP_H
