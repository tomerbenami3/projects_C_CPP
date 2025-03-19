#ifndef LC3_ISA_H
#define LC3_ISA_H

#include <cstdint>

namespace lc3 {


class ISA {

public:
    ISA(uint16_t& instruction);
    ~ISA();

    int16_t get_opcode();
    int16_t get_sr1();
    int16_t get_sr2();
    int16_t get_dr();
    bool get_imm_flag();
    bool get_jsr();
    int16_t get_imm_val();
    int16_t offset_6();
    int16_t offset_9();
    int16_t offset_11();
    int16_t trap_vect8();
    bool get_nflag();
    bool get_zflag();
    bool get_pflag();

    int16_t sign_extension(int16_t offset, int msb);
    
private:
    uint16_t& m_instruction;
    
};


}


#endif // LC3_ISA_H
