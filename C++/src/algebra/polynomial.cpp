#include "polynomial.hpp"
#include <new>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

namespace algebra
{

Polynomial::Polynomial(size_t degree)
: m_coefficient{new Rational[degree + 1]}
, m_size{degree + 1}
{
    assert(m_coefficient);
}

Polynomial::~Polynomial()
{
	delete[] m_coefficient;
}

Polynomial::Polynomial(Polynomial const& other)
: m_coefficient{new Rational[other.m_size]}
, m_size{other.m_size}
{
	for (size_t i = 0; i < m_size; ++i) {
		m_coefficient[i] = other.m_coefficient[i];
	}
}

void Polynomial::swap(Polynomial& other)
{
    std::swap(this->m_coefficient, other.m_coefficient);
    std::swap(this->m_size, other.m_size);
}

Polynomial& Polynomial::operator=(Polynomial const& other)
{
	if (this!= &other) {
        Polynomial temp(other);
        swap(temp);
        }

    return *this;

}

bool Polynomial::operator==(Polynomial const& other)
{
	return m_coefficient == other.m_coefficient;
}

Rational& Polynomial::operator[](size_t const& index)
{
    return m_coefficient[index];
}

Rational const& Polynomial::operator[](size_t const& index) const
{
	return m_coefficient[index];
}


Rational Polynomial::operator()(Rational const& value) const
{
    Rational sum;
    int size = static_cast<int>(m_size);

	for(int i = 0; i < size; ++i) {
        if(m_coefficient[i] != 0) {
            Rational temp = mul(calcpow(value, i), m_coefficient[i]);
            sum = add(sum, temp);
        }
    }
    return sum;
}

Polynomial::Polynomial(Rational* begin, Rational* end)
{
    int i = 0;
    m_size = end - begin;
    m_coefficient = new Rational[m_size];
    while(begin + i != end) {
        m_coefficient[i] = begin[i];
        ++i;
    }
}

size_t Polynomial::size() const
{
    return m_size;
}

void Polynomial::print(std::ostream& os) const
{
    for(int i = static_cast<int>(m_size) - 1; i >= 0; --i) {
        if(m_coefficient[i].value() != 0) {
            m_coefficient[i].print();
            if(i != 0) {
                os << "X^" << i << " + ";
            }
        }
    }
}

Polynomial Polynomial::derive() const
{
    Polynomial temp{m_size - 1};
    int size = static_cast<int>(m_size);

    for(int i = size; i > 0; --i) {
        temp.m_coefficient[i - 1] = mul(m_coefficient[i], i);
    }
    return temp;
}

Polynomial& Polynomial::operator*=(Rational const& scaler)
{

    int size = static_cast<int>(m_size);
    for(int i = size; i >= 0; --i) {
        m_coefficient[i].mul(scaler);
    }
    return *this;
}

Polynomial& Polynomial::operator*=(int scaler)
{
    int size = static_cast<int>(m_size);
    for(int i = size; i >= 0; --i) {
        m_coefficient[i].mul(scaler);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, Polynomial const& rhs)
{
    rhs.print(os);
    return os;
}

Polynomial operator+(Polynomial const& lhs, Polynomial const& rhs)
{
    size_t max_size, min_size;
    max_size = lhs.size();
    min_size = rhs.size();

    Polynomial greater;
    Polynomial smaller;

    if(rhs.size() <= lhs.size()){
        greater = lhs;
        smaller = rhs;
    }
    else{
        std::swap(max_size,min_size);
        greater = rhs;
        smaller = lhs;
    } 
    
    for (size_t i=0; i<min_size; ++i)
    {
        greater[i].add(smaller[i]);
    }
    return greater;
}

Polynomial operator*(Polynomial const& lhs, Polynomial const& rhs)
{
    size_t r_size = rhs.size();
    size_t l_size = lhs.size();
    size_t res_size = l_size + r_size;

    Polynomial res{res_size};

    for (size_t i=0; i<r_size; ++i)
    {
        for (size_t j=0; j<l_size; ++j)
        {
            res[j+i] = add(res[j+i], mul(rhs[i],lhs[j]));
        }
    }
    return res;
}

}