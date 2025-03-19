#include "../../inc/mu_test.h"
#include "../../inc/algebra/rational.hpp"


BEGIN_TEST(add_const_rational)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 13;
    double y = 14;
    double res = x / y;

    f.add(g);
    ASSERT_EQUAL(f.value(), res);

END_TEST

BEGIN_TEST(mul_const_rational)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 3;
    double y = 14;
    double res = x / y;

    f.mul(g);
    ASSERT_EQUAL(f.value(), res);

END_TEST

BEGIN_TEST(add_const_int)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 2;
    double y = 0.5;
    double res = x + y;

    f.add(2);
    ASSERT_EQUAL(f.value(), res);

END_TEST

BEGIN_TEST(mul_const_int)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 2;
    double y = 0.5;
    double res = x * y;

    f.mul(2);
    ASSERT_EQUAL(f.value(), res);

END_TEST

BEGIN_TEST(mul_rational_and_int)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 9;
    double y = 14;
    double res = x / y;

    f.mul(d);
    f.mul(g);
    ASSERT_EQUAL(f.value(), res);

END_TEST

BEGIN_TEST(add_add_mul_rational_and_int)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 165;
    double y = 98;
    double res = x / y;

    f.add(d);
    f.add(g);
    f.mul(g);
    ASSERT_EQUAL(f.value(), res);

END_TEST

BEGIN_TEST(add_2_rational_return_rational)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 13;
    double y = 14;
    double res = x / y;

    d = add(f, g);
    ASSERT_EQUAL(d.value(), res);

END_TEST

BEGIN_TEST(mul_2_rational_return_rational)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 3;
    double y = 14;
    double res = x / y;

    d = mul(f, g);
    ASSERT_EQUAL(d.value(), res);

END_TEST

BEGIN_TEST(add_rational_with_int)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 5;
    double y = 2;
    double res = x / y;

    d = add(f, 2);
    ASSERT_EQUAL(d.value(), res);

END_TEST

BEGIN_TEST(mul_rational_with_int)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 3;
    double y = 2;
    double res = x / y;

    d = mul(f, 3);
    ASSERT_EQUAL(d.value(), res);

END_TEST

BEGIN_TEST(mul_add_rational_with_int)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 27;
    double y = 14;
    double res = x / y;

    d = mul(f, d);
    d.add(g);
    ASSERT_EQUAL(d.value(), res);
END_TEST

BEGIN_TEST(reduce_rational)
    algebra::Rational f{48, 14};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 24;
    double y = 7;
    double res = x / y;
    f.reduce();
    ASSERT_EQUAL(f.value(), res);
END_TEST

BEGIN_TEST(get_value)
    algebra::Rational f{48, 14};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 48;
    double y = 14;
    double res = x / y;
    f.value();
    ASSERT_EQUAL(f.value(), res);
END_TEST

BEGIN_TEST(mul_and_add)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 27;
    double y = 14;
    double res = x / y;

    f.mul(d);
    f.add(g);
    ASSERT_EQUAL(f.value(), res);
END_TEST

BEGIN_TEST(print_test)
    algebra::Rational f{1, 2};
    algebra::Rational d{3};
    algebra::Rational const g{3, 7};

    double x = 1;
    double y = 2;
    double res = x / y;

    f.print();
    ASSERT_EQUAL(f.value(), res);
END_TEST

TEST_SUITE(Rational unit tests)
	TEST(add_const_rational)
	TEST(mul_const_rational)
	TEST(add_const_int)
	TEST(mul_const_int)
	TEST(mul_rational_and_int)
	TEST(add_add_mul_rational_and_int)
	TEST(add_2_rational_return_rational)
	TEST(mul_2_rational_return_rational)
	TEST(add_rational_with_int)
	TEST(mul_rational_with_int)
	TEST(mul_add_rational_with_int)
	TEST(reduce_rational)
	TEST(get_value)
	TEST(mul_and_add)
	TEST(print_test)

END_SUITE