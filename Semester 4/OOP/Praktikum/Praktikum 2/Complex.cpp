#include "Complex.h"

using namespace std;

Complex::Complex(){
	real=0;
	imaginer=0;
}

Complex::Complex(int re, int im){
	real = re;
	imaginer = im;
}

Complex::Complex(const Complex &comp){
	this->real = comp.real;
	this->imaginer = comp.imaginer;
}

Complex::~Complex(){
	
}

int Complex::getReal(){
	return real;
}
	
int Complex::getImaginer(){
	return imaginer;
}

void Complex::setReal(int re){
	real = re;
}

void Complex::setImaginer(int im){
	imaginer = im;
}

Complex Complex::operator +(Complex const &comp){
	Complex t(real+comp.real, imaginer+comp.imaginer);
	return t;
}

Complex Complex::operator -(Complex const &comp){
	Complex t(real-comp.real, imaginer-comp.imaginer);
	return t;
}

Complex Complex::operator *(Complex const &comp){
	Complex t(real*comp.real - imaginer*comp.imaginer, imaginer*comp.real + real*comp.imaginer);
	return t;
}
