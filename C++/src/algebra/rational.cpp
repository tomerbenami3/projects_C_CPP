#include "../../inc/algebra/rational.hpp"
#include <iostream>

namespace algebra {

Rational::Rational(int numerator, int denominator)
: m_numinator{numerator}
, m_denuminator{denominator}
{
}

void Rational::add(int number)
{
    number *= m_denuminator;
    m_numinator += number;
}

bool Rational::operator==(Rational const& other)
{
	return this == &other;
}

bool Rational::operator!=(Rational const& other)
{
	return !(this == &other);
}

void Rational::add(Rational const number)
{
    Rational temp{number};
    temp.m_denuminator *= m_denuminator;
    temp.m_numinator *= m_denuminator;

    m_denuminator *= number.m_denuminator;
    m_numinator *= number.m_denuminator;

    m_numinator += temp.m_numinator;

    return;
}

Rational add(Rational const num1, Rational const num2)
{
    Rational temp{num1};
    temp.add(num2);
    return temp;
}

Rational mul(Rational const num1, Rational const num2)
{
    Rational temp{num1};
    temp.mul(num2);
    return temp;
}

Rational mul(Rational const num1, int const num2)
{
    Rational temp{num1};
    temp.mul(num2);
    return temp;
}

Rational add(Rational const num1, int const num2)
{
    Rational temp{num1};
    temp.add(num2);
    return temp;
}


void Rational::mul(int number)
{
    this->m_numinator *= number;
}

void Rational::mul(Rational const number)
{
    Rational temp{number};
    m_numinator *= temp.m_numinator;
    m_denuminator *= temp.m_denuminator;
}

double Rational::value() const
{
    return (double)m_numinator / m_denuminator;
}

void Rational::reduce() {
    int common;

    if(m_numinator < m_denuminator) {
        common = m_numinator;
    } else {
        common = m_denuminator;
    }

    for(int i = common; i > 0; --i) {
        if((m_numinator % i) == 0 && (m_denuminator % i) == 0) {
            m_numinator = (double)m_numinator / i;
            m_denuminator = (double)m_denuminator / i;
        }
    }
}

// void Rational::print(std::ostream& os) const
// {

// }

void Rational::print() const
{
    std::cout << m_numinator << "/" << m_denuminator ;
}

Rational calcpow(Rational number, int pow)
{
    Rational res = 1;
    while(pow > 0) {
        res = mul(res, number); 
        --pow;
    }
    return res;
}

}