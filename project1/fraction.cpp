#include "fraction.h"
#include <string>
#include <iostream>

//Function to get greatest common devisor for reduce function
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

void Fraction::reduce() {
	int g = gcd(numer, denom);
	numer /= g;
	denom /= g;
}

Fraction::Fraction(double deci) {
	int denom = 1;
	while (deci - (int)deci > 0) {
		deci *= 10;
		denom *= 10;
	}
	//No more decimal
	numer = deci;
	reduce();
}

std::string Fraction::toString() const {
	std::string num = std::to_string(numer);
	std::string den = std::to_string(denom);
	return num + "/" + den;
}

int Fraction::getNumerator() const {
	return numer;
}
int Fraction::getDenominator() const {
	return denom;
}

double Fraction::getDouble() const {
	return (double)numer/denom;
}

Fraction& Fraction::operator=(const Fraction& o) {
	this->numer = o.getNumerator();
	this->denom = o.getDenominator();
	return *this;
}

Fraction& Fraction::operator+=(const Fraction& o) {
	int oldDenom = this->denom;
	this->numer *= o.getDenominator();
	this->denom *= o.getDenominator();
	this->numer += (o.getNumerator() * oldDenom);
	
	this->reduce();
	return *this;
}
Fraction& Fraction::operator-=(const Fraction& o) {
	int oldDenom = this->denom;
	this->numer *= o.getDenominator();
	this->denom *= o.getDenominator();
	this->numer -= (o.getNumerator() * oldDenom);
	
	this->reduce();
	return *this;
}
Fraction& Fraction::operator*=(const Fraction& o) {
	this->numer *= o.getNumerator();
	this->denom *= o.getDenominator();
	this->reduce();
	return *this;
}
Fraction& Fraction::operator/=(const Fraction& o) {
	this->numer /= o.getNumerator();
	this->denom /= o.getDenominator();
	this->reduce();
	return *this;
}

Fraction operator+(Fraction l, const Fraction& o) {
	return l+=o;
}

Fraction operator-(Fraction l, const Fraction& o) {
	return l-=o;
}

Fraction operator*(Fraction l, const Fraction& o) {
	return l*=o;
}

Fraction operator/(Fraction l, const Fraction& o) {
	return l/=o;
}

std::ostream& operator<<(std::ostream& os, const Fraction& o) {
	os << o.toString();
	return os;
}
