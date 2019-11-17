#ifndef RATIONAL
#define RATIONAL
#include <iostream>
#include <string>
namespace CS2124 {
	class Rational {
		friend std::ostream& operator<<(std::ostream& os, const Rational& num);
		friend std::istream& operator>>(std::istream& is, Rational& num);
		friend bool operator==(const Rational& lhs, const Rational& rhs);
		friend bool operator<(const Rational& lhs, const Rational& rhs);

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
	Rational operator+(const Rational& lhs, const Rational rhs);
	bool operator!=(const Rational& lhs, const Rational& rhs);
	Rational& operator--(Rational& rat);
	Rational& operator--(Rational& rat, int junk);
	std::ostream& operator<<(std::ostream& os, const Rational& num);
	std::istream& operator>>(std::istream& is, Rational& num);
	bool operator==(const Rational& lhs, const Rational& rhs);
	bool operator<=(const Rational& lhs, const Rational& rhs);
	bool operator>=(const Rational& lhs, const Rational& rhs);
	bool operator>(const Rational& lhs, const Rational& rhs);
}



#endif