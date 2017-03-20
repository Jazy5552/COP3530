#ifndef FRACTION_H
#define FRACTION_H
#include <string>
#include <iostream>

class Fraction {
private:
	int numer;
	int denom;

	void reduce();
public:
	Fraction(): numer(0), denom(1) {};
	Fraction(int numer, int denom = 1): numer(numer), denom(denom) {};

	Fraction(double deci);

	double getDouble() const;
	std::string toString() const;

	int getNumerator() const;
	int getDenominator() const;

	Fraction& operator=(const Fraction& o);
	Fraction& operator+=(const Fraction& o);
	Fraction& operator-=(const Fraction& o);
	Fraction& operator*=(const Fraction& o);
	Fraction& operator/=(const Fraction& o);

};

//Shit ton of operator overloads incoming 
Fraction operator+(Fraction l, const Fraction& o);
Fraction operator-(Fraction l, const Fraction& o);
Fraction operator*(Fraction l, const Fraction& o);
Fraction operator/(Fraction l, const Fraction& o);
std::ostream& operator<<(std::ostream& os, const Fraction& o);
/*
Fraction operator+(const Fraction& l, const Fraction& o);
Fraction operator+(const Fraction& l, const int& o);
Fraction operator+(const Fraction& l, const double& o);
Fraction operator+(const int& l, const Fraction& o);
Fraction operator+(const double& l, const Fraction& o);

Fraction operator-(const Fraction& l, const Fraction& o);
Fraction operator-(const Fraction& l, const int& o);
Fraction operator-(const Fraction& l, const double& o);
Fraction operator-(const int& l, const Fraction& o);
Fraction operator-(const double& l, const Fraction& o);

Fraction operator*(const Fraction& l, const Fraction& o);
Fraction operator*(const Fraction& l, const int& o);
Fraction operator*(const Fraction& l, const double& o);
Fraction operator*(const int& l, const Fraction& o);
Fraction operator*(const double& l, const Fraction& o);

Fraction operator/(const Fraction& l, const Fraction& o);
Fraction operator/(const Fraction& l, const int& o);
Fraction operator/(const Fraction& l, const double& o);
Fraction operator/(const int& l, const Fraction& o);
Fraction operator/(const double& l, const Fraction& o);
*/
#endif
