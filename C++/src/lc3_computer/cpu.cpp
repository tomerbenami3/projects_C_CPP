#include "cpu.hpp"
#include <stdexcept>
#include <iostream>
#include <bitset>

namespace lc3 {

CPU::CPU()
: m_memory(default_size)
, m_command(0)
, m_cur_instruction(m_command)
, m_pc(3000)
, m_trap(m_memory, m_registers)
, m_opcodes{}
{
    m_opcodes[0x0] = [this]() { branch(); };
    m_opcodes[0x1] = [this]() { add(); };
    m_opcodes[0x2] = [this]() { load(); };
    m_opcodes[0x3] = [this]() { store(); };
    m_opcodes[0x4] = [this]() { jsr(); };
    m_opcodes[0x5] = [this]() { m_and(); };
    m_opcodes[0x6] = [this]() { load_register(); };
    m_opcodes[0x7] = [this]() { store_register(); };
    m_opcodes[0x8] = [this]() { reserved(); };
    m_opcodes[0x9] = [this]() { m_not(); };
    m_opcodes[0xA] = [this]() { load_i(); };
    m_opcodes[0xB] = [this]() { store_i(); };
    m_opcodes[0xC] = [this]() { jump(); };
    m_opcodes[0xD] = [this]() { reserved(); };
    m_opcodes[0xE] = [this]() { lea(); };
    m_opcodes[0xF] = [this]() { trap(); };
}

void CPU::execute() {
    
    while(m_command)
    {
        m_command = m_memory.read(m_pc);
        uint16_t opcode = m_cur_instruction.get_opcode();
        m_pc++;
        // std::cout << "COMMAND - "<< std::bitset<16>(m_command) << '\n';
        if (opcode < m_opcodes.size() && m_opcodes[opcode]) {
            m_opcodes[opcode]();
        } else {
            throw std::runtime_error("Invalid opcode");
        }
    }
}

void CPU::load_program(std::string const& file_name)
{
    FileManager file(file_name);
    int16_t instruction;

    while(file.read_next_instruction(instruction)) {
        m_memory.write(m_pc, instruction);
        ++m_pc;
    }
    m_pc = 0x3000;
    m_command = m_memory.read(m_pc);
}

void CPU::load_program_BE(std::string const& file_name)
{
    FileManager file(file_name);
    int16_t instruction = file.read_next_instruction(instruction);

    m_pc = (instruction >> 8 & 0xFF) | (instruction << 8);
    int16_t m_temp_pc = m_pc;

    while (file.read_next_instruction(instruction)) {
        instruction = (instruction >> 8 & 0xFF) | (instruction << 8);

        m_memory.write(m_temp_pc, instruction);
        // std::cout << std::bitset<16>(instruction) << '\n';
        ++m_temp_pc;
    }

    m_command = m_memory.read(m_pc);
}

void CPU::add()
{
    int16_t dr = m_cur_instruction.get_dr();
    int16_t sr1 = m_cur_instruction.get_sr1();
    bool imm_flag = m_cur_instruction.get_imm_flag();

    int16_t sr2_value = imm_flag ? m_cur_instruction.get_imm_val() : m_registers[m_cur_instruction.get_sr2()];


    int16_t result = 0;
    m_alu.add(m_registers[sr1], sr2_value, result);

    m_registers[dr] = result;
    m_flags.update_flags(result);
}

void CPU::m_and()
{
    int16_t dr = m_cur_instruction.get_dr();
    int16_t sr1 = m_cur_instruction.get_sr1();
    bool imm_flag = m_cur_instruction.get_imm_flag();

    int16_t sr2_value = imm_flag ? m_cur_instruction.get_imm_val() : m_registers[m_cur_instruction.get_sr2()];

    int16_t result = 0;
    m_alu.m_and(m_registers[sr1], sr2_value, result);

    m_registers[dr] = result;

    m_flags.update_flags(result);
}

void CPU::branch()
{
    bool n = m_cur_instruction.get_nflag();
    bool z = m_cur_instruction.get_zflag();
    bool p = m_cur_instruction.get_pflag();

    if ((n && m_flags.get_nflag()) || (z && m_flags.get_zflag()) || (p && m_flags.get_pflag())) {
        m_pc += m_cur_instruction.offset_9();
    }
}

void CPU::jump()
{
    m_pc = m_registers[m_cur_instruction.get_sr1()];
}

void CPU::jsr()
{
    m_registers[7] = m_pc;
    if (m_cur_instruction.get_jsr()) {
        m_pc += m_cur_instruction.offset_11();
    } else {
        m_pc = m_registers[m_cur_instruction.get_sr1()];
    }
}


void CPU::load()
{
    int16_t dr_index = m_cur_instruction.get_dr();
    m_registers[dr_index] = m_memory.read(m_pc + m_cur_instruction.offset_9());
    m_flags.update_flags(m_registers[dr_index]);
}

void CPU::load_i()
{
    int16_t dr = m_cur_instruction.get_dr();
    int16_t address = m_memory.read(m_pc + m_cur_instruction.offset_9());
    m_registers[dr] = m_memory.read(address);
    m_flags.update_flags(m_registers[dr]);
}

void CPU::load_register()
{
    int16_t dr = m_cur_instruction.get_dr();
    int16_t base = m_registers[m_cur_instruction.get_sr1()];
    m_registers[dr] = m_memory.read(base + m_cur_instruction.offset_6());
    m_flags.update_flags(m_registers[dr]);
}

void CPU::lea()
{
    int16_t dr = m_cur_instruction.get_dr();
    m_registers[dr] = m_pc + m_cur_instruction.offset_9();
    m_flags.update_flags(m_registers[dr]);
}

void CPU::m_not()
{
    int16_t dr = m_cur_instruction.get_dr();
    int16_t sr = m_cur_instruction.get_sr1();

    m_alu.m_not(m_registers[sr], m_registers[dr]);
    m_flags.update_flags(m_registers[dr]);
}

void CPU::ret()
{
    m_pc = m_registers[7];
}


void CPU::store()
{
    int16_t sr = m_cur_instruction.get_sr1();
    int16_t address = m_pc + m_cur_instruction.offset_9();
    m_memory.write(address, m_registers[sr]);
}

void CPU::store_i()
{
    int16_t sr = m_cur_instruction.get_sr1();
    int16_t address = m_memory.read(m_pc + m_cur_instruction.offset_9());
    m_memory.write(address, m_registers[sr]);
}

void CPU::store_register()
{
    int16_t sr = m_cur_instruction.get_dr();
    int16_t base = m_registers[m_cur_instruction.get_sr1()];
    int16_t offset = m_cur_instruction.offset_6();

    int16_t address = base + offset;

    m_memory.write(address, m_registers[sr]);
}

void CPU::trap()
{
    // m_registers[7] = m_pc;
    // m_pc = m_memory.read(m_cur_instruction.trap_vect8());
    m_trap.execute(m_cur_instruction.trap_vect8());
}

void CPU::reserved()
{
    throw std::runtime_error("Reserved instruction encountered!");
}

int16_t CPU::get_register_value(size_t index)
{
    return m_registers[index];
}

void CPU::set_register_value(size_t index, int16_t value)
{
    m_registers[index] = value;
}

int16_t CPU::get_pc() {
    return m_pc;
}

void CPU::set_pc(int16_t value) {
    m_pc = value;
}

}