#include "flags.hpp"

namespace lc3 {

Flags::Flags()
{
    m_flags.fill(0);
}

void Flags::update_flags(int16_t const& res)
{
    m_flags[0] = res >> 15;
    m_flags[1] = (res == 0);
    m_flags[2] = !m_flags[0] && !m_flags[1];
}

bool Flags::get_nflag()
{
    return m_flags[0];
}

bool Flags::get_zflag()
{
    return m_flags[1];
}

bool Flags::get_pflag()
{
    return m_flags[2];
}


}