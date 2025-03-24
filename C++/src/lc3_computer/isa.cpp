#include "isa.hpp"

namespace lc3
{

ISA::ISA(uint16_t& instruction)
: m_instruction(instruction)
{

}

ISA::~ISA()
{

}

int16_t ISA::get_opcode()
{
    return (m_instruction >> 12);
}

int16_t ISA::get_sr1()
{
    return (m_instruction >> 6) & 7;
}

int16_t ISA::get_sr2()
{
    return (m_instruction & 7);
}

int16_t ISA::get_dr()
{
    return (m_instruction >> 9) & 7;
}

bool ISA::get_imm_flag()
{
    return (m_instruction >> 5) & 1;
}
bool ISA::get_jsr()
{
    return (m_instruction >> 11) & 1;
}

int16_t ISA::get_imm_val()
{
    return sign_extension(m_instruction & 0x1F, 4);
}

int16_t ISA::offset_6()
{
    return sign_extension(m_instruction & 0x3F, 5);
}

int16_t ISA::offset_9()
{
    return sign_extension(m_instruction & 0x1FF, 8);
}

int16_t ISA::offset_11()
{
    return sign_extension(m_instruction & 0x7FF, 10);
}

int16_t ISA::trap_vect8()
{
    return m_instruction & 0xFF;
}

bool ISA::get_nflag()
{
    return (m_instruction >> 11) & 1;
}
bool ISA::get_zflag()
{
    return (m_instruction >> 10 & 1);
}

bool ISA::get_pflag()
{
    return (m_instruction >> 9) & 1;
}

int16_t ISA::sign_extension(int16_t offset, int msb) {
    bool is_negative = offset & (1 << msb);

    if (is_negative) {
        offset |= ~((1 << (msb + 1)) - 1);
    } else {
        offset &= (1 << (msb + 1)) - 1;
    }

    // if(is_negative) {
    //     while()
    // }

    return offset;
}


}
