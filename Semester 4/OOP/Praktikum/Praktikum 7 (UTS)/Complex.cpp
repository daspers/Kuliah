#include "Complex.h"

Complex::Complex()
{
	real = 0;
	imaginer = 0;
}
// Constructor untuk bilangan re + im*i
Complex::Complex(double re, double im)
{
	real = re;
	imaginer = im;
}

// Getter komponen real
double Complex::getReal() const
{
	return real;	
}
// Getter komponen imaginer
double Complex::getImaginer() const
{
	return imaginer;
}
// Getter untuk magnitude, yaitu sqrt(re*re + im*im) (fungsi sqrt ada di cmath)
double Complex::getMagnitude() const
{
	return sqrt(real*real + imaginer*imaginer);
}

// Operator-operator
// definisi +: (a + b i) + (c + d i) = (a + c) + (b + d) i
Complex Complex::operator+ (const Complex& other) const
{
	Complex tem(real + other.real, imaginer+other.imaginer);
	return tem;
}
// definisi -: (a + b i) - (c + d i) = (a - c) + (b - d) i
Complex Complex::operator- (const Complex& other) const
{
	Complex tem(real - other.real, imaginer-other.imaginer);
	return tem;
}
// definisi *: (a + b i) * (c + d i) = (a * c - b * d) + (a * d + b * c) i
Complex Complex::operator* (const Complex& other) const
{
	Complex tem(real*other.real - imaginer*other.imaginer, imaginer*other.real+real*other.imaginer);
	return tem;
}
// Dua bilangan kompleks dianggap sama jika komponen real dan imaginer
// tidak berbeda lebih dari EPSILON. (Karena sifat floating point)
// (a + b i) == (c + d i) jika abs(a - c) < EPSILON dan abs(b - d) < EPSILON
// (fungsi abs ada di cmath)
bool Complex::operator== (const Complex& other) const
{
	return abs(real-other.real)<EPSILON && abs(imaginer-other.imaginer)<EPSILON;
}
