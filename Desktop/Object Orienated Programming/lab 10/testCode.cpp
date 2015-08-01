#include <iostream>
#include "Rational.h"
using namespace std;
using namespace CS1124;

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