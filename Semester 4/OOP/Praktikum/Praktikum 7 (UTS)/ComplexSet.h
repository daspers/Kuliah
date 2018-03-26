#ifndef COMPLEXSET_H
#define COMPLEXSET_H
#include <iostream>
#include <cmath>
#include "Complex.h"

#define MAX_COMPLEX 100

using namespace std;

// Kelas yang menyimpan himpunan bilangan kompleks
class ComplexSet {
    public:
        // Inisiasi ComplexSet
        // members dialokasikan untuk menyimpan bilangan kompleks sebanyak MAX_COMPLEX
        // count diinisialisasi dengan 0
        ComplexSet();

        // Copy constructor, destructor, dan assignment
        ComplexSet(const ComplexSet &comp);
        ~ComplexSet();
        ComplexSet& operator=(const ComplexSet& other);

        // Mengembalikan true jika ada salah satu bilangan kompleks yang tersimpan
        // yang sama dengan c
        bool hasComplex(const Complex& c) const;
        // Memasukkan bilangan kompleks c ke dalam ComplexSet
        // Jika c sudah ada di dalam ComplexSet, tidak boleh dimasukkan
        // (tidak boleh ada duplikat)
        // Tidak perlu ada penanganan ComplexSet penuh.
        void insert(const Complex& c);

        // Getter bilangan kompleks dengan magnitude terbesar (sesuai getMagnitude)
        Complex getLargest() const;
        // Menghasilkan bilangan kompleks di mana komponen real nya adalah rata-rata
        // komponen real semua kompleks yang tersimpan, dan komponen imaginer nya
        // adalah rata-rata komponen imaginer semua kompleks yang tersimpan.
        Complex getCenter() const;

        // Mengembalikan jumlah bilangan kompleks yang tersimpan
        int getCount() const;

        // Mengembalikan sebuah ComplexSet baru yang semua anggotanya ada di
        // ComplexSet ini dan other
        ComplexSet intersection(const ComplexSet& other) const;
        // Mengembalikan sebuah ComplexSet baru yang semua anggotanya ada di
        // ComplexSet ini atau other (tidak boleh duplikat)
        ComplexSet setUnion(const ComplexSet& other) const;

    private:
        // Pointer untuk array data yang menyimpan bilangan kompleks
        Complex* members;
        // Jumlah bilangan kompleks yang sedang tersimpan
        int count;
};

#endif