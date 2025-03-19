#include "rpn/token.hpp"
#include "mu_test.h"

using namespace rpn;

BEGIN_TEST(tokenizer1)
    std::string_view input = "331 42 * 19 x - *";
    auto tokens = tokenize(input);

    ASSERT_EQUAL(tokenTypeToString(tokens[0].type), "NUMBER");
    ASSERT_EQUAL(std::get<int>(tokens[0].value), 331);
    ASSERT_EQUAL(tokenTypeToString(tokens[1].type), "NUMBER");
    ASSERT_EQUAL(std::get<int>(tokens[1].value), 42);
    ASSERT_EQUAL(tokenTypeToString(tokens[2].type), "OPERATOR");
    ASSERT_EQUAL(std::get<char>(tokens[2].value), '*');
    ASSERT_EQUAL(tokenTypeToString(tokens[3].type), "NUMBER");
    ASSERT_EQUAL(std::get<int>(tokens[3].value), 19);
    ASSERT_EQUAL(tokenTypeToString(tokens[4].type), "VARIABLE");
    ASSERT_EQUAL(std::get<std::string_view>(tokens[4].value), "x");
    ASSERT_EQUAL(tokenTypeToString(tokens[5].type), "OPERATOR");
    ASSERT_EQUAL(std::get<char>(tokens[5].value), '-');
END_TEST

BEGIN_SUITE(tokenizer_tests)
    TEST(tokenizer1)
END_SUITE
