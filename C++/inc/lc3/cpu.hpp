#ifndef LC3_CPU_H
#define LC3_CPU_H

#include "alu.hpp"
#include "memory.hpp"
#include "flags.hpp"
#include "isa.hpp"
#include "trap.hpp"
#include "file_manager.hpp"
#include "registerfile.hpp"

namespace lc3 {

class CPU {
public:
    CPU();
    ~CPU() = default;

    void load_program(std::string const& file_name);
    void load_program_BE(std::string const& file_name);
    void execute();

    void add();
    void m_and();
    void branch();
    void jump();
    void jsr();
    void load();
    void load_i();
    void load_register();
    void lea();
    void m_not();
    void ret();
    void store();
    void store_i();
    void store_register();
    void trap();
    void reserved();

    int16_t get_register_value(size_t index);
    void set_register_value(size_t index, int16_t value);

    int16_t get_pc();
    void set_pc(int16_t value);

private:
    Memory m_memory;
    RegisterFile m_registers;
    ALU m_alu;
    Flags m_flags;
    uint16_t m_command;
    ISA m_cur_instruction;
    int16_t m_pc;
    Trap m_trap;
    std::array<std::function<void()>, 16> m_opcodes;
    
};


}


#endif // LC3_CPU_H
