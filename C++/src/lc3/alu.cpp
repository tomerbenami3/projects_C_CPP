#include "alu.hpp"

namespace lc3 {

void ALU::add(int16_t& sr1, int16_t& sr2, int16_t& dr)
{
    dr = sr1 + sr2;
}

void ALU::m_and(int16_t& sr1, int16_t& sr2, int16_t& dr)
{
    dr = sr1 & sr2;
}
void ALU::m_not(int16_t sr1, int16_t& dr)
{
    dr = ~sr1;
}


}
