#include "Rational.h"
# include <string>
#include <iostream>
using namespace std;
namespace CS1124 {
int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

Rational::Rational(int n, int d) : numerator(n), denominator(d){
		this->simplify();
	}

	void Rational::setNumerator(int n){
		numerator = n;
		this->simplify();
	}

	void Rational::setDenominator(int d) {
		denominator = d;
		this->simplify();
	}

	void Rational::simplify(){
		int gcd = greatestCommonDivisor(numerator,denominator);
		numerator = numerator/gcd;
		denominator = denominator/gcd;
		if(numerator < 0 && denominator < 0){
			numerator += -2*numerator;
			denominator += -2*denominator;
		}
		else if(denominator < 0){
			numerator -= 2 * numerator;
			denominator += -2*denominator;	}
	}0

	int Rational::getNumerator() const {return numerator;}

	int Rational::getDenominator() const {return denominator;}

	

	Rational& Rational::operator+=(const Rational& rhs){
		Rational temp(rhs.numerator, rhs.denominator);
		numerator *= temp.denominator;
		int tempD = denominator;
		denominator *= temp.denominator;
		temp.numerator *= tempD;
		numerator += temp.numerator;
		this->simplify();
		return *this;
	}


	Rational& Rational::operator++(){
		numerator += denominator;
		return *this;


	}

	Rational Rational::operator++(int i){
		Rational temp = *this;
		*this = operator++();
		return temp;
	}


ostream& operator<<(ostream& os, const Rational& rhs){
	os << rhs.getNumerator() << "/" << rhs.getDenominator();
	return os;
}

istream& operator>>(istream& is, Rational& rhs){
	int tempNum, tempDem;
	is >> tempNum >> tempDem;
	rhs.setNumerator(tempNum);
	rhs.setDenominator(tempDem);
	rhs.simplify();
	return is;
}



Rational operator+(Rational lhs, Rational& rhs){
	lhs += rhs;
	return lhs;

}

bool operator==(const Rational& lhs ,const Rational& a)  {
		return(lhs.getNumerator() == a.getNumerator() && lhs.getDenominator() == a.getDenominator());

	}

bool operator!=(const Rational& lhs, const Rational& rhs){
	return !(lhs==rhs);
}

Rational& operator--(Rational& lhs){
	lhs += -1;
	return lhs;
}

Rational operator--(Rational& lhs, int i){
	Rational temp = lhs;
	lhs += -1;
	return temp;
}

}