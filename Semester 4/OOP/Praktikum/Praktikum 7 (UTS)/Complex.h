#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
#include <cmath>

#define EPSILON 0.0001

using namespace std;

class Complex {
    public:
        // Constructor bilangan complex 0 + 0i
        Complex();
        // Constructor untuk bilangan re + im*i
        Complex(double re, double im);

        // Getter komponen real
        double getReal() const;
        // Getter komponen imaginer
        double getImaginer() const;
        // Getter untuk magnitude, yaitu sqrt(re*re + im*im) (fungsi sqrt ada di cmath)
        double getMagnitude() const;

        // Operator-operator
        // definisi +: (a + b i) + (c + d i) = (a + c) + (b + d) i
        Complex operator+ (const Complex& other) const;
        // definisi -: (a + b i) - (c + d i) = (a - c) + (b - d) i
        Complex operator- (const Complex& other) const;
        // definisi *: (a + b i) * (c + d i) = (a * c - b * d) + (a * d + b * c) i
        Complex operator* (const Complex& other) const;
        // Dua bilangan kompleks dianggap sama jika komponen real dan imaginer
        // tidak berbeda lebih dari EPSILON. (Karena sifat floating point)
        // (a + b i) == (c + d i) jika abs(a - c) < EPSILON dan abs(b - d) < EPSILON
        // (fungsi abs ada di cmath)
        bool operator== (const Complex& other) const;

    private:
        // Penyimpanan komponen real dan imaginer
        double real, imaginer;
};

#endif