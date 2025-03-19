#include "memory.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>


namespace lc3 {

Memory::Memory(size_t size)
{
    m_memory.resize(size, 0);
}

Memory::~Memory()
{}

size_t fixed_addr(int16_t addr)
{
    return static_cast<size_t>(addr);
}

int16_t Memory::read(int16_t address) const
{
    size_t fixed_address = static_cast<uint16_t>(fixed_addr(address));

    if(fixed_address >= m_memory.size()) {
        throw std::out_of_range("invalid index in memory read\n");
    }

    return m_memory[fixed_address];
}

void Memory::write(int16_t address, int16_t value)
{
    size_t fixed_address = fixed_addr(address);

    if(fixed_address >= m_memory.size()) {
        throw std::out_of_range("invalid index2\n");
    }

    m_memory[address] = value;
}

}
