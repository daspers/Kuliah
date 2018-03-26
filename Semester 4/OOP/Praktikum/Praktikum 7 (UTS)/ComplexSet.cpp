#include "ComplexSet.h"

// Inisiasi ComplexSet
// members dialokasikan untuk menyimpan bilangan kompleks sebanyak MAX_COMPLEX
// count diinisialisasi dengan 0
ComplexSet::ComplexSet()
{
	members = new Complex[MAX_COMPLEX];
	count = 0;
}

// Copy constructor, destructor, dan assignment
ComplexSet::ComplexSet(const ComplexSet &comp)
{
	members = new Complex[MAX_COMPLEX];
	count = comp.count;
	for(int i=0;i<count;i++)
		members[i] = comp.members[i];
}
ComplexSet::~ComplexSet()
{
	delete[] members;
}
ComplexSet& ComplexSet::operator=(const ComplexSet& other)
{
	count = other.count;
	for(int i=0;i<count;i++)
		members[i] = other.members[i];
	return *this;
}

// Mengembalikan true jika ada salah satu bilangan kompleks yang tersimpan
// yang sama dengan c
bool ComplexSet::hasComplex(const Complex& c) const
{
	for(int i=0;i<count;i++)
		if(members[i]==c)
			return true;
	return false;
}
// Memasukkan bilangan kompleks c ke dalam ComplexSet
// Jika c sudah ada di dalam ComplexSet, tidak boleh dimasukkan
// (tidak boleh ada duplikat)
// Tidak perlu ada penanganan ComplexSet penuh.
void ComplexSet::insert(const Complex& c)
{
	if(!hasComplex(c)){
		members[count] = c;
		count++;
	}
}

// Getter bilangan kompleks dengan magnitude terbesar (sesuai getMagnitude)
Complex ComplexSet::getLargest() const
{
	double ma = members[0].getMagnitude();
	int idx=0;
	for(int i=1;i<count;i++){
		double temp = members[i].getMagnitude();
		if(temp>ma){
			ma = temp;
			idx = i;
		}
	}
	return members[idx];
}
// Menghasilkan bilangan kompleks di mana komponen real nya adalah rata-rata
// komponen real semua kompleks yang tersimpan, dan komponen imaginer nya
// adalah rata-rata komponen imaginer semua kompleks yang tersimpan.
Complex ComplexSet::getCenter() const
{
	double avgr = 0;
	double avgi = 0;
	for(int i=0;i<count;i++){
		avgr += members[i].getReal();
		avgi += members[i].getImaginer();
	}
	Complex temp(avgr/count, avgi/count);
	return temp; 
}

// Mengembalikan jumlah bilangan kompleks yang tersimpan
int ComplexSet::getCount() const
{
	return count;
}

// Mengembalikan sebuah ComplexSet baru yang semua anggotanya ada di
// ComplexSet ini dan other
ComplexSet ComplexSet::intersection(const ComplexSet& other) const
{
	ComplexSet res;
	for(int i=0;i<count;i++){
		if(other.hasComplex(members[i]))
			res.insert(members[i]);
	}
	return res;
}
// Mengembalikan sebuah ComplexSet baru yang semua anggotanya ada di
// ComplexSet ini atau other (tidak boleh duplikat)
ComplexSet ComplexSet::setUnion(const ComplexSet& other) const
{
	ComplexSet res(other);
	for(int i=0;i<count;i++){
		res.insert(members[i]);
	}
	return res;
}
