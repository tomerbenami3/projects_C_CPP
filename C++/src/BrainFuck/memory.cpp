#include "memory.hpp"
#include <iostream>
#include <cstddef>

namespace bf {


Memory::Memory(size_t size)
: m_memory(size, 0)
, m_pos{&m_memory[size/2]}
{

}

Memory::Memory(Memory const& other)
: m_memory(other.m_memory.size(), 0)
, m_pos(&m_memory[0])
{
    for(size_t index = 0; index < other.m_memory.size(); ++index) {
        m_memory[index] = other.m_memory[index];
    }
    intptr_t offset = other.m_pos - &m_memory[0];
    m_pos += offset;

}

Memory& Memory::operator=(Memory const& other)
{
    if(this != &other) {
        m_memory = other.m_memory;
        intptr_t offset = other.m_pos - &other.m_memory[0];
        m_pos = &m_memory[offset];
    }
    return *this;
}

char& Memory::operator[](size_t const index)
{
    return m_memory[index];
}

void Memory::extend_memory_right()
{
    size_t const block_size = 20;

    intptr_t offset = m_pos - &m_memory[0];
    m_memory.resize(m_memory.size() + block_size, 0);

    m_pos = &m_memory[offset];

}

void Memory::extend_memory_left()
{
    size_t const block_size = 20;
    size_t old_size = m_memory.size();

    m_memory.resize(m_memory.size() + block_size, 0);

    for(size_t index = old_size; index > 0; --index) {
        std::swap(m_memory[index + block_size - 1], m_memory[index - 1]);
    }

    m_pos = &m_memory[block_size];
}



void Memory::add()
{
    ++(*m_pos);
}

void Memory::sub()
{
    --(*m_pos);
}

void Memory::print()
{
    std::cout << *m_pos << std::endl;
}

char& Memory::read()
{
    return *m_pos;
}

void Memory::write(char ch)
{
    *m_pos = ch;
}

void Memory::movright()
{
    if(m_pos == &m_memory[m_memory.size() - 1]) {
        extend_memory_right();
    }
    ++m_pos;
}

void Memory::movleft()
{
    if(m_pos == &m_memory[0]) {
        extend_memory_left();
    }
    --m_pos;
}

size_t Memory::size()
{
        return m_memory.size();
}

char* Memory::position()
{
    return m_pos;
}

}
    