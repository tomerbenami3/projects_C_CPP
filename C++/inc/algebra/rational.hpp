#ifndef ALGEBRA_RATIONAL_H
#define ALGEBRA_RATIONAL_H


namespace algebra {

class Rational 
{
public:
    Rational(int numerator = 0, int denominator = 1);
    bool operator==(Rational const& other);
    bool operator!=(Rational const& other);
    void add(int number);
    void add(Rational const number);

    // void print(std::ostream& os) const;

    void mul(int number);
    void mul(Rational const number);
    void reduce();
    double value() const;
    void print() const;

private:
    int m_numinator;
    int m_denuminator;
};

Rational add(Rational num1, Rational num2);
Rational add(Rational const num1, int const num2);
Rational calcpow(Rational number, int pow);
Rational mul(Rational const num1, Rational const num2);
Rational mul(Rational const num1, int const num2);
}

#endif // ALGEBRA_RATIONAL_H