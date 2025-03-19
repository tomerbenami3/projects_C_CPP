#include "registerfile.hpp"
#include <stdexcept>

namespace lc3 {

RegisterFile::RegisterFile()
{
    m_registers.fill(0);
}

int16_t& RegisterFile::operator[](size_t index)
{
    if(index >= m_registers.size()) {
        throw std::out_of_range("invalid index");
    }
    return m_registers[index];
}


}