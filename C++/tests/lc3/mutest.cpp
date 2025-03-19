#include "mu_test.h"
#include "flags.hpp"
#include "memory.hpp"
#include "file_manager.hpp"
#include "cpu.hpp"
#include "isa.hpp"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstdint>

#include <unistd.h>

#include <sys/errno.h>
#include <sys/termios.h>

static struct termios original_tio;

static void disable_input_buffering() {
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

static void restore_input_buffering() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

void create_test_binary_file(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to create test binary file");
    }

    uint16_t instructions[] = {0x1234, 0x5678, 0x9ABC, 0x0000};
    file.write(reinterpret_cast<const char*>(instructions), sizeof(instructions));
    file.close();
}

void create_test_instruction_file(const std::string& filename, uint16_t ins) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to create instruction file");
    }

    std::vector<uint16_t> instructions = {
        ins,
    };

    file.write(reinterpret_cast<const char*>(instructions.data()), instructions.size() * sizeof(uint16_t));
    file.close();
}


BEGIN_TEST(flags_test1)
lc3::Flags flags;
flags.update_flags(123);

ASSERT_THAT(!flags.get_nflag());
ASSERT_THAT(!flags.get_zflag());
ASSERT_THAT(flags.get_pflag());

END_TEST


BEGIN_TEST(flags_test2)
lc3::Flags flags;
flags.update_flags(0);

ASSERT_THAT(!flags.get_nflag());
ASSERT_THAT(flags.get_zflag());
ASSERT_THAT(!flags.get_pflag());

END_TEST


BEGIN_TEST(flags_test3)
lc3::Flags flags;
flags.update_flags(-123);

ASSERT_THAT(flags.get_nflag());
ASSERT_THAT(!flags.get_zflag());
ASSERT_THAT(!flags.get_pflag());

END_TEST

BEGIN_TEST(memory_test1)
lc3::Memory memory(256);
memory.write(100, 123);
int16_t value = memory.read(100);
ASSERT_THAT(value == 123);

memory.write(200, -456);
value = memory.read(200);
ASSERT_THAT(value == -456);

END_TEST

BEGIN_TEST(file_manager_test1)
{
    const std::string test_file = "test_instructions.bin";
    create_test_binary_file(test_file);

    lc3::FileManager fileManager(test_file);
    int16_t instruction_out = 0;

    ASSERT_THAT(fileManager.read_next_instruction(instruction_out));
    ASSERT_THAT(instruction_out == 0x1234);

    ASSERT_THAT(fileManager.read_next_instruction(instruction_out));
    ASSERT_THAT(instruction_out == 0x5678);

    ASSERT_THAT(fileManager.read_next_instruction(instruction_out));
    ASSERT_THAT(instruction_out == static_cast<int16_t>(0x9ABC));

    ASSERT_THAT(fileManager.read_next_instruction(instruction_out));
    ASSERT_THAT(instruction_out == 0x0000);

    ASSERT_THAT(!fileManager.read_next_instruction(instruction_out));
}
END_TEST


BEGIN_TEST(file_manager_test_all_zero_instruction)
{
    const std::string test_file = "test_all_zero.bin";

    std::ofstream file(test_file, std::ios::binary);
    uint16_t instruction = 0x0000;
    file.write(reinterpret_cast<const char*>(&instruction), sizeof(instruction));
    file.close();

    lc3::FileManager fileManager(test_file);

    int16_t instruction_out = 0;
    bool success = fileManager.read_next_instruction(instruction_out);
    ASSERT_THAT(success);
    ASSERT_THAT(instruction_out == 0x0000);

    success = fileManager.read_next_instruction(instruction_out);
    ASSERT_THAT(!success);
}
END_TEST

BEGIN_TEST(cpu_add_test)
{
    const std::string test_file = "test_instructions.bin";
    create_test_instruction_file(test_file, 0b0001001011000010);

    lc3::CPU cpu;
    cpu.load_program(test_file);

    cpu.set_register_value(2, 5);
    cpu.set_register_value(3, 7);
    cpu.add();
    ASSERT_EQUAL(cpu.get_register_value(1), 12);
}
END_TEST

BEGIN_TEST(cpu_and_test)
{
    const std::string test_file = "test_instructions.bin";
    create_test_instruction_file(test_file, 0b0101001011000010);

    lc3::CPU cpu;
    cpu.load_program(test_file);

    cpu.set_register_value(2, 0b1100);
    cpu.set_register_value(3, 0b1010);
    cpu.m_and();
    ASSERT_EQUAL(cpu.get_register_value(1), 0b1000);
}
END_TEST

BEGIN_TEST(cpu_branch)
const std::string test_file = "test_instructions.bin";
create_test_instruction_file(test_file, 0b0001001011000010);

lc3::CPU cpu;
cpu.load_program(test_file);


cpu.set_register_value(2,-10);
cpu.set_register_value(3,5);
cpu.add();

create_test_instruction_file(test_file, 0b0000100000000100);
cpu.load_program(test_file);

cpu.branch();
ASSERT_EQUAL(cpu.get_pc(),3004);

END_TEST

BEGIN_TEST(cpu_addImm)
const std::string test_file = "test_instructions.bin";
create_test_instruction_file(test_file, 0b0001001011111110);

lc3::CPU cpu;
cpu.load_program(test_file);

cpu.set_register_value(3,5);
cpu.add();
ASSERT_EQUAL(cpu.get_register_value(1), 3);

END_TEST

// BEGIN_TEST(run_first_program_hello)
// {
//     const std::string test_file = "hello.bin";
//     lc3::CPU cpu;
//     cpu.load_program_BE(test_file);

//     cpu.execute();

//     ASSERT_THAT(1);
// }
// END_TEST

// BEGIN_TEST(run_second_program_print10)
// {
//     const std::string test_file = "print10.bin";
//     lc3::CPU cpu;
//     cpu.load_program_BE(test_file);

//     cpu.execute();

//     ASSERT_THAT(1);
// }
// END_TEST

BEGIN_TEST(run_third_program_2048)
{
    disable_input_buffering();

    const std::string test_file = "2048.bin";
    lc3::CPU cpu;
    cpu.load_program_BE(test_file);

    cpu.execute();

    ASSERT_THAT(1);
    restore_input_buffering();
}
END_TEST

BEGIN_SUITE(lc3_ tests)
    TEST(flags_test1)
    TEST(flags_test2)
    TEST(flags_test3)
    TEST(memory_test1)
    TEST(file_manager_test1)
    TEST(file_manager_test_all_zero_instruction)

    TEST(cpu_add_test)
    TEST(cpu_and_test)
    TEST(cpu_branch)
    TEST(cpu_addImm)
    // TEST(cpu_load_and_execute_test)

    // TEST(run_first_program_hello)
    // TEST(run_second_program_print10)
    TEST(run_third_program_2048)


END_SUITE