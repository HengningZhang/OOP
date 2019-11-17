/*
	testRational.cpp
	CS2124
	Implement the class Rational, so that the following program works.
 */


 // If time allows use  separate compilation, otherwise just define the class below
//#include "Rational.h"
#include <iostream>
#include <string>
using namespace std;


//using namespace CS2124;
class Rational {
	friend std::ostream& operator<<(std::ostream& os, const Rational& num);
	friend std::istream& operator>>(std::istream& is, Rational& num);
	friend bool operator==(const Rational& lhs, const Rational& rhs);


public:
	Rational(int nom, int denom);
	Rational& operator+=(const Rational& rhs);
	Rational& operator++();
	Rational operator++(int junk);
	explicit operator bool() const;


private:
	int nom;
	int denom;
};
int greatestCommonDivisor(int x, int y) {
	while (y != 0) {
		int temp = x % y;
		x = y;
		y = temp;
	}
	return x;
}


Rational::Rational(int nom = 0, int denom = 1) :nom(nom), denom(denom) {}

Rational& Rational::operator+=(const Rational& rhs) {
	nom = nom * rhs.denom + rhs.nom * denom;
	denom = denom * rhs.denom;
	int gcd = greatestCommonDivisor(nom, denom);
	nom /= gcd;
	denom /= gcd;
	return *this;
}

Rational& Rational::operator++() {
	nom += denom;
	return *this;
}
Rational Rational::operator++(int junk) {
	Rational original(*this);
	nom += denom;
	return original;
}
Rational::operator bool() const {
	return nom != 0;
}
Rational operator+(const Rational& lhs, const Rational rhs) {
	Rational temp(lhs);
	return temp += rhs;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}
Rational& operator--(Rational& rat) {
	rat += -1 / 1;
	return rat;
}
Rational& operator--(Rational& rat, int junk) {
	Rational original(rat);
	rat += -1 / 1;
	return rat;
}
ostream& operator<<(ostream& os, const Rational& num) {
	os << num.nom << "/" << num.denom;
	return os;
}
istream& operator>>(istream& is, Rational& num) {
	int nomin, denomin;
	char slash;
	is >> nomin >> slash >> denomin;
	int gcd = greatestCommonDivisor(nomin, denomin);
	num.nom = nomin / gcd;
	num.denom = denomin / gcd;
	return is;
}
bool operator==(const Rational& lhs, const Rational& rhs) {
	return lhs.denom == rhs.denom && lhs.nom == rhs.nom;
}
int main() {
	Rational twoThirds(2, 3);
	cout << twoThirds << endl;

	Rational a, b;
	cout << "Input a rational number, e.g. 6/9.\n";
	cout << "a: ";
	cin >> a;
	cout << "Input a rational number, e.g. 6/9.\n";
	cout << "b: ";
	cin >> b;
	const Rational one = 1;
	cout << a;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "one = " << one << endl;
	cout << "a += b: " << (a += b) << endl;	// Implement as member
	cout << "a = " << a << endl;

	// Implement as non-member, but not a friend
	cout << "a + one: " << (a + one) << endl;
	cout << "a == one: " << boolalpha << (a == one) << endl;

	// How does this manage to work?
	// It does NOT require writing another == operator. 
	cout << "1 == one: " << boolalpha << (1 == one) << endl;

	// Do not implement as friend.
	cout << "a != one: " << boolalpha << (a != one) << endl;

	cout << "a = " << a << endl;
	cout << "++a = " << (++a) << endl;
	cout << "a = " << a << endl;
	cout << "a++ = " << (a++) << endl;
	cout << "a = " << a << endl;
	cout << "--a = " << (--a) << endl;
	cout << "a = " << a << endl;
	cout << "a-- = " << (a--) << endl;
	cout << "a = " << a << endl;

	cout << "++ ++a = " << (++ ++a) << endl;
	cout << "a = " << a << endl;
	cout << "-- --a = " << (-- --a) << endl;
	cout << "a = " << a << endl;

	cout << "a++ ++ = " << (a++ ++) << endl;
	cout << "a = " << a << endl;

	// Even though the above example, (a++ ++), compiled, the
	// following shouldn't.
	// But some compiler vendors might let it...  Is your compiler
	// doing the right thing?
	cout << "a-- -- = " << (a-- --) << endl;
	cout << "a = " << a << endl;


	// Should report that 1 is true
	if (Rational(1)) {
		cout << "1 is true" << endl;
	}
	else {
		cout << "1 is false" << endl;
	}

	// Should report that 0 is false
	if (Rational(0)) {
		cout << "0 is true" << endl;
	}
	else {
		cout << "0 is false" << endl;
	}
	
}
