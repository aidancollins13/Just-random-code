# include <string>
#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

class Rational{
public:
	Rational(int n=1, int d=1) : numerator(n), denominator(d){
		this->simplify();
	}

	void setNumerator(int n){
		numerator = n;
		this->simplify();
	}

	void setDenominator(int d) {
		denominator = d;
		this->simplify();
	}

	void simplify(){
		int gcd = greatestCommonDivisor(numerator,denominator);
		numerator = numerator/gcd;
		denominator = denominator/gcd;
		if(numerator < 0 && denominator < 0){
			numerator += -2*numerator;
			denominator += -2*denominator;
		}
		else if(denominator < 0){
			numerator -= 2 * numerator;
			denominator += -2*denominator;
		}
	}

	int getNumerator() const {return numerator;}

	int getDenominator() const {return denominator;}

	

	Rational& operator+=(const Rational& rhs){
		Rational temp(rhs.numerator, rhs.denominator);
		numerator *= temp.denominator;
		int tempD = denominator;
		denominator *= temp.denominator;
		temp.numerator *= tempD;
		numerator += temp.numerator;
		this->simplify();
		return *this;
	}


	Rational& operator++(){
		numerator += denominator;
		return *this;


	}

	Rational operator++(int i){
		Rational temp = *this;
		*this = operator++();
		return temp;
	}
private:
	int numerator;
	int denominator;
};

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

int main(){
	Rational a, b;
    cout << "Input two rational numbers.\n";
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    Rational one = 1;
    Rational c(4,2);

	cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	             // Implement as member
    cout << "a = " << a << endl;		
    cout << "a + one: " << (a + one) << endl;                // Implement as non-member, but not a friend
    cout << "a == one: " << boolalpha << (a == one) << endl;  
    cout << "1 == one: " << boolalpha << (1 == one) << endl; // How does this work?
    cout << "a != one: " << boolalpha << (a != one) << endl; // Implement as non-member, but not a friend
   cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;   // Implement as member
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;   // Implement as member
    cout << "a = " << a << endl;	
     cout << "--a = " << (--a) << endl;   // Implement as non-member, but not a friend
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;   // Implement as non-member, but not a friend
    cout << "a = " << a << endl;
}