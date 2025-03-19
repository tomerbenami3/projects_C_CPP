#ifndef ALGEBRA_POLYNOMIAL_H
#define ALGEBRA_POLYNOMIAL_H

#include <cstddef>
#include <iostream>
#include "rational.hpp"

namespace algebra {

class Polynomial
{
public:
    explicit Polynomial(size_t degree = 0);
	explicit Polynomial(Rational* begin, Rational* end);
    ~Polynomial();

    Polynomial(Polynomial const& other);
	Polynomial& operator=(Polynomial const& other);

    bool operator==(Polynomial const& other);

    Rational& operator[](size_t const& index);
	Rational const& operator[](size_t const& index) const;

	Rational operator()(Rational const& x) const;

	Polynomial& operator*=(Rational const& value);
	Polynomial& operator*=(int scaler);

    void swap(Polynomial& temp);

    void print(std::ostream& os) const;
    size_t size() const;
    Polynomial derive() const;

private:
    Rational *m_coefficient;
    size_t m_size;
};

std::ostream& operator<<(std::ostream& os, Polynomial const& rhs);
Polynomial operator+(Polynomial const& lhs, Polynomial const& rhs);
Polynomial operator*(Polynomial const& lhs, Polynomial const& rhs);

}

#endif // ALGEBRA_POLYNOMIAL_H
