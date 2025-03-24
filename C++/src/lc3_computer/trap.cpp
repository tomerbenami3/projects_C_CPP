#include "trap.hpp"
#include "iostream"
#include <cstdint>

namespace lc3 {

Trap::Trap(Memory& memory, RegisterFile& registers)
: m_memory(memory)
, m_registers(registers)
, m_functions{}
{
    m_functions[0x20] = [this]() { getc(); };
    m_functions[0x21] = [this]() { out(); };
    m_functions[0x22] = [this]() { puts(); };
    m_functions[0x23] = [this]() { in(); };
    m_functions[0x24] = [this]() { putsp(); };
    m_functions[0x25] = [this]() { halt(); };
}

void Trap::execute(uint16_t trap_vector)
{
    if (!m_functions[trap_vector]) {
        throw std::runtime_error("Invalid TRAP vector");
    }
    m_functions[trap_vector]();
}

void Trap::getc()
{
    char c;
    std::cin.get(c);
    m_registers[0] = static_cast<int16_t>(c);
}

void Trap::out()
{
    char c = static_cast<char>(m_registers[0] & 0xFF);
    std::cout << c;
}

void Trap::puts()
{
    int16_t address = m_registers[0];
    char c;
    while ((c = static_cast<char>(m_memory.read(address) & 0xFF)) != '\0') {
        std::cout << c;
        ++address;
    }
}

void Trap::in()
{
    std::cout << "Enter a character: ";
    char c;
    std::cin.get(c);
    m_registers[0] = static_cast<int16_t>(c);
    std::cout << c;
}

void Trap::putsp()
{
    int16_t address = m_registers[0];
    int16_t word;
    while ((word = m_memory.read(address)) != 0) {
        char c1 = static_cast<char>(word & 0xFF);
        char c2 = static_cast<char>((word >> 8) & 0xFF);
        std::cout << c1;
        if (c2 != '\0') {
            std::cout << c2;
        }
        ++address;
    }
}

void Trap::halt()
{
    std::cout << "HALT: Program execution stopped." << std::endl;
    std::exit(0);
}

}
