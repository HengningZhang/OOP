#include "Rational.h"
using namespace std;
#include <iostream>
#include <string>

namespace CS2124 {
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
	bool operator<(const Rational& lhs, const Rational& rhs) {
		return (lhs.nom / lhs.denom) < (rhs.nom / rhs.denom);
	}
	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return lhs < rhs && lhs == rhs;
	}
	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return !(lhs < rhs);
	}
	bool operator>(const Rational& lhs, const Rational& rhs) {
		return !(lhs <= rhs);
	}
}

