#ifndef LC3_ALU_H
#define LC3_ALU_H

#include <array>
#include <cstdint>

namespace lc3 {


class ALU {
public:
    ALU() = default;
    ~ALU() = default;

    void add(int16_t& sr1, int16_t& sr2, int16_t& dr);
    void m_and(int16_t& sr1, int16_t& sr2, int16_t& dr);
    void m_not(int16_t sr1, int16_t& dr);
    
};


}


#endif // LC3_ALU_H
