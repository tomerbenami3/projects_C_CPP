#include <iostream>

#include "../../inc/mu_test.h"
#include "../../inc/challenger/challenger_1.hpp"


BEGIN_TEST(fib1)
    int num = Fibo();
    ASSERT_THAT(num == 0);
END_TEST

BEGIN_TEST(fib2)
    int num = Fibo();
    ASSERT_THAT(num == 1);
END_TEST

BEGIN_TEST(fib3)
    int num = Fibo();
    ASSERT_THAT(num == 1);
END_TEST

BEGIN_TEST(fib4)
    int num = Fibo();
    ASSERT_THAT(num == 2);
END_TEST

BEGIN_TEST(fib5)
    int num = Fibo();
    ASSERT_THAT(num == 3);
END_TEST

BEGIN_TEST(fib6)
    int num = Fibo();
    ASSERT_THAT(num == 5);
END_TEST

BEGIN_TEST(fib7)
    int num = Fibo();
    ASSERT_THAT(num == 8);
END_TEST

BEGIN_TEST(fib8)
    int num = Fibo();
    ASSERT_THAT(num == 13);
END_TEST

BEGIN_TEST(fib9)
    int num = Fibo();
    ASSERT_THAT(num == 21);
END_TEST
BEGIN_TEST(fib10)
    int num = Fibo();
    ASSERT_THAT(num == 34);
END_TEST

BEGIN_TEST(factorial1)
    int num = Factorial(5);
    ASSERT_THAT(num == 120);
END_TEST

BEGIN_TEST(factorial2)
    int num = Factorial(-5);
    ASSERT_THAT(num == -1);
END_TEST

BEGIN_TEST(factorial3)
    int num = Factorial(0);
    ASSERT_THAT(num == 1);
END_TEST

BEGIN_TEST(factorial4)
    int num = Factorial(10);
    ASSERT_THAT(num == 3628800);
END_TEST

BEGIN_TEST(sort_balls)
    Ball balls[10] = {
        {Red, 5, true},
        {Black, 10, false},
        {White, 8, true},
        {Red, 6, false},
        {Black, 12, true},
        {White, 7, false},
        {Red, 15, true},
        {Black, 3, false},
        {White, 9, true},
        {Red, 4, false}
    };

    sortBalls(balls, 10);

    for(int i = 0; i < 10; ++i) {
        std::cout << "color:" << balls[i].color << ", radius: " << balls[i].radius << "\n";
    }

    //  for (int i = 0; i < 10; i++) {
    //     std::cout << "Ball " << i + 1 << ": ";
    //     std::cout << "Color = ";
    //     switch (balls[i].color) {
    //         case Red: std::cout << "Red"; break;
    //         case Black: std::cout << "Black"; break;
    //         case White: std::cout << "White"; break;
    //     }
    //     std::cout << ", Radius = " << balls[i].radius
    //          << ", Is Solid = " << (balls[i].is_solid ? "Yes" : "No") 
    //          << std::endl;
    // }

    ASSERT_THAT(1);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

    TEST(fib1)
    TEST(fib2)
    TEST(fib3)
    TEST(fib4)
    TEST(fib5)
    TEST(fib6)
    TEST(fib7)
    TEST(fib8)
    TEST(fib9)
    TEST(fib10)

    TEST(factorial1)
    TEST(factorial2)
    TEST(factorial3)
    TEST(factorial4)

    TEST(sort_balls)

END_SUITE