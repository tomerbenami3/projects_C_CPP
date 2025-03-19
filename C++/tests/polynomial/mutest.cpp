#include "../../inc/mu_test.h"
#include "../../inc/algebra/rational.hpp"
#include "polynomial.hpp"


BEGIN_TEST(ctor_poly)
    Algebra::Polynomial f(5);
    int size = f.size();

    ASSERT_EQUAL(6, size);
END_TEST

BEGIN_TEST(init_poly)
    Algebra::Polynomial f(5);
    f[0] = {2, 3};
    f[3] = {-4, 7};
    f[5] = {1, 2};
    ASSERT_EQUAL(f[0].value(), (double)2/3);
END_TEST

BEGIN_TEST(insert_rational_array_to_poly)

    Algebra::Rational c[] = {
                  Algebra::Rational{1,2}, Algebra::Rational{2,3},
                  Algebra::Rational{0},Algebra::Rational{4,5}
               };
    Algebra::Polynomial p{c, c+4};

    // p.print_poly();
    ASSERT_EQUAL(p[3].value(), (double)4/5);
END_TEST

BEGIN_TEST(init_empty_poly)
    Algebra::Polynomial  q;
    ASSERT_EQUAL(q.size(), 1);
END_TEST

BEGIN_TEST(calc_value_in_poly)
    Algebra::Polynomial f(3);
    f[0] = {1, 2};
    f[1] = {1, 3};
    f[2] = {2, 7};

    Algebra::Rational r = f({1,1});
    
    ASSERT_EQUAL(r.value(), (double)47/42);
END_TEST

BEGIN_TEST(derive_poly)
    int size = 5;
    Algebra::Polynomial f(size);
    f[0] = {1, 2};
    f[1] = {1, 3};
    f[2] = {2, 7};

    Algebra::Polynomial w = f.derive();
    
    ASSERT_EQUAL(w[1].value(), (double)4/7);
END_TEST

BEGIN_TEST(multiply_poly_with_int)
    int size = 5;
    Algebra::Polynomial f(size);
    f[0] = {1, 2};
    f[1] = {1, 3};
    f[2] = {2, 7};

    f *= 3;
    
    ASSERT_EQUAL(f[2].value(), (double)6/7);
END_TEST

BEGIN_TEST(multiply_poly_with_rational)
    int size = 5;
    Algebra::Polynomial f(size);
    f[0] = {1, 2};
    f[1] = {1, 3};
    f[2] = {2, 7};

    f *= Algebra::Rational{3, 2};    
    
    ASSERT_EQUAL(f[2].value(), (double)6/14);
END_TEST

BEGIN_TEST(add_polynomials_test)
    size_t size = 3;
    Algebra::Polynomial p(size);
    p[0] = {7,1};
    p[1] = {2,1};
    p[2] = {1,1};
    Algebra::Polynomial f(size);
    f[0] = {7,1};
    f[1] = {2,1};
    f[3] = {1,1};
    Algebra::Polynomial w = p+f;
    Algebra::Rational m = w({1,1});
    ASSERT_EQUAL(m.value(), 20);
END_TEST

BEGIN_TEST(mul_polynomials_test)
    size_t size = 3;
    Algebra::Polynomial p(size);
    p[0] = {7,1};
    p[1] = {2,1};
    p[2] = {1,1};
    Algebra::Polynomial f(size);
    f[0] = {7,1};
    f[1] = {2,1};
    f[2] = {1,1};
    Algebra::Polynomial w = p*f;  
    Algebra::Rational m = w({1,1});
    ASSERT_EQUAL(m.value(), 100);
END_TEST

TEST_SUITE(Rational unit tests)
	TEST(ctor_poly)
	TEST(init_poly)
	TEST(insert_rational_array_to_poly)
	TEST(init_empty_poly)
	TEST(calc_value_in_poly)
	TEST(derive_poly)
	TEST(multiply_poly_with_int)
	TEST(multiply_poly_with_rational)
	TEST(add_polynomials_test)
	TEST(mul_polynomials_test)
END_SUITE