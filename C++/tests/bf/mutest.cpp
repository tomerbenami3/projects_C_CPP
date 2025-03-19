#include "mu_test.h"
#include "memory.hpp"
#include "input.hpp"
#include "output.hpp"
#include "cpu.hpp"
#include "compiler.hpp"
#include <vector>
#include <string>

BEGIN_TEST(vector_create)
    bf::Memory memory(200);
    ASSERT_EQUAL(memory.size(), 200);
END_TEST

BEGIN_TEST(pos_initial_location)
    size_t size = 200;
    bf::Memory memory(size);
    char* pos = memory.position();

    ASSERT_EQUAL_PTR(pos, &memory[size / 2]);

END_TEST

BEGIN_TEST(copy_constructor)
    size_t size = 200;
    bf::Memory memory(size);
    bf::Memory new_mem = memory;
    ASSERT_EQUAL(memory.size(), 200);
END_TEST

BEGIN_TEST(pos_movright)
    size_t size = 200;
    bf::Memory memory(size);
    memory.movright();
    memory.movright();
    char* pos = memory.position();
    ASSERT_EQUAL_PTR(pos, &memory[size / 2]+2);

END_TEST

BEGIN_TEST(pos_movleft)
    size_t size = 200;
    bf::Memory memory(size);
    memory.movleft();
    memory.movleft();
    char* pos = memory.position();
    ASSERT_EQUAL_PTR(pos, &memory[size / 2]-2);

END_TEST

BEGIN_TEST(print_value)
    size_t size = 200;
    bf::Memory memory(size);

    for(int index = 0; index < 97; ++index) {
        memory.add();
        
    }

    // memory.print();

    ASSERT_EQUAL_PTR(1, 1);
END_TEST

BEGIN_TEST(vector_extend_right)
    size_t size = 5;
    bf::Memory memory(size);
    memory.movright();
    memory.movright();
    memory.movright();
    ASSERT_EQUAL(memory.size(), 25);
    ASSERT_EQUAL_PTR(memory.position(), &memory[5]);
END_TEST

BEGIN_TEST(vector_extend_left)
    size_t size = 5;
    bf::Memory memory(size);
    memory.movleft();
    memory.movleft();
    memory.movleft();
    memory.movleft();
    ASSERT_EQUAL(memory.size(), 25);
    ASSERT_EQUAL_PTR(memory.position(), &memory[18]);
END_TEST

BEGIN_TEST(memory_allocation_from_both_sides)
    bf::Memory mem{5};
    mem.movleft();
    mem.movleft();
    mem.movleft();
    ASSERT_EQUAL(mem.size(), 25);
    ASSERT_EQUAL(*mem.position(), 0);
    ASSERT_EQUAL_PTR(mem.position(), &mem[19]);
    
    mem.movright();
    mem.movright();
    mem.movright();
    mem.movright();
    mem.movright();
    mem.movright();

    ASSERT_EQUAL(mem.size(), 45);
    ASSERT_EQUAL_PTR(mem.position(), &mem[25]);
END_TEST

// BEGIN_TEST(input_create)
//     std::string code = "[++[--]]";
//     bf::Compiler compiler;
//     // ASSERT_EQUAL(compiler.validate_brackets(code), true);
// END_TEST

// BEGIN_TEST(input_validate_brackets_test1)
//     bf::Input buf{"[+--+++.,[]]"};

//     ASSERT_THAT(buf.validate_brackets());
// END_TEST

// BEGIN_TEST(input_validate_brackets_test2)
//     bf::Input buf{"[+--+++.,[]]]"};

//     ASSERT_THAT(!buf.validate_brackets());
// END_TEST

// BEGIN_TEST(input_validate_brackets_test3)
//     bf::Input buf{"[+--+++.,[]"};

//     ASSERT_THAT(!buf.validate_brackets());
// END_TEST

// BEGIN_TEST(input_next_char)
//     bf::Input buf{"[+--+++.,[]"};

//     char ch = buf.next_char();

//     ASSERT_EQUAL(ch, '[');
// END_TEST

// BEGIN_TEST(cpu_create)
//     std::string buffer = "[+--+++.,[]";
//     bf::Cpu vm(buffer, 100);

//     ASSERT_EQUAL(1, 1);
// END_TEST

BEGIN_TEST(cpu_execute_test1)
    std::string code = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";

    bf::Compiler compiler;
    std::vector<bf::Instruction> code_segment = compiler.compile(code);

    bf::Cpu vm(100);
    vm.execute(code_segment);

    ASSERT_EQUAL(1, 1);
END_TEST

// BEGIN_TEST(cpu_execute_test2)
//     std::string code = "++++[++++>---<]>+.";

//     bf::Compiler compiler;
//     std::vector<bf::Instruction> code_segment = compiler.compile(code);

//     bf::Cpu vm(100);
//     vm.execute(code_segment);

//     ASSERT_EQUAL(1, 1);
// END_TEST

// BEGIN_TEST(cpu_execute_test2)
//     std::string code = "++++[->++++++++<]>..[-->+++<]>-.-[->++<]>.+++.-[-->+<]>.-[->++<]>.[++>---<]>.[->+++<]>++.++++++++.--------.+++++[->+++<]>.[->+++++<]>+++.---[----->+<]>.[--->+<]>-----.+++++++++.>++++++++++.[->+++<]>++..-[->++<]>.[-->+<]>+.-[->+++<]>+.-[--->+<]>+.--[->++<]>.>++++++++++.++[->++++++<]>.-[->+++++<]>++.+++++++..+++.[--->+<]>-----.---[->+++<]>.-[--->+<]>---.+++.------.--------.-[--->+<]>.";
//     bf::Compiler compiler;
//     std::vector<bf::Instruction> code_segment = compiler.compile(code);
//     bf::Cpu vm(100);
//     vm.execute(code_segment);

//     ASSERT_EQUAL(1, 1);
// END_TEST

TEST_SUITE(VM unit tests)
	TEST(vector_create)
	TEST(pos_initial_location)
	TEST(copy_constructor)
	TEST(pos_movright)
	TEST(pos_movleft)
	TEST(print_value)
	TEST(vector_extend_right)
	TEST(vector_extend_left)
	TEST(memory_allocation_from_both_sides)

	// TEST(input_create)
	// TEST(input_validate_brackets_test1)
	// TEST(input_validate_brackets_test2)
	// TEST(input_validate_brackets_test3)
	// TEST(input_next_char)

	// TEST(cpu_create)
	TEST(cpu_execute_test1)
	// TEST(cpu_execute_test2)

END_SUITE