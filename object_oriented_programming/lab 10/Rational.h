#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
namespace CS1124 {
int greatestCommonDivisor(int x, int y);

class Rational{
public:
	Rational(int n=1, int d=1);
	void setNumerator(int n);
	void setDenominator(int d);
	void simplify();
	int getNumerator() const;
	int getDenominator() const;
	Rational& operator+=(const Rational& rhs);
	Rational& operator++();
	Rational operator++(int i);
private:
	int numerator;
	int denominator;
};

std::ostream& operator<<(std::ostream& os, const Rational& rhs);
std::istream& operator>>(std::istream& is, Rational& rhs);
Rational operator+(Rational lhs, Rational& rhs);
bool operator==(const Rational& lhs ,const Rational& a);
bool operator!=(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& lhs);
Rational operator--(Rational& lhs, int i);

}

#endif