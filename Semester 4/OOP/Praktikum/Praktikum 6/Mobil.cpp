#include <string>
#include <iostream>
#include "Mobil.h"

using namespace std;

Mobil::Mobil(string t, string w, string m, int p, int l, int h){
	tahun = t;
	warna = w;
	merek = m;
	panjang = p;
	lebar = l;
	tinggi = h;
}
string Mobil::getTahun() const{
	return tahun;
}

string Mobil::getWarna()const{
	return warna;
}
string Mobil::getMerek() const{
	return merek;
}
int Mobil::getPanjang() const{
	return panjang;
}
int Mobil::getLebar() const{
	return lebar;
}
int Mobil::getTinggi() const{
	return tinggi;
}
void Mobil::setTahun(string a){
	tahun =a;
}
void Mobil::setWarna(string a){
	warna = a;
}
void Mobil::setMerek(string a){
	merek = a;
}
void Mobil::setPanjang(int a){
	panjang = a;
}
void Mobil::setLebar(int a){
	lebar = a;
}
void Mobil::setTinggi(int a){
	tinggi = a;
}
void Mobil::bunyikanKlakson(){
	cout<<"Telolet\n";
}
void Mobil::cetakJenisBahanBakar(){
	cout<<"Air\n";
}


MobilCepat::MobilCepat(string t, string w, string m, int p, int l, int h, int k):Mobil(t,w,m,p,l,h){
	maxKecepatan = k;
}

int MobilCepat::getMaxKecepatan() const{
	return maxKecepatan;
}
void MobilCepat::setMaxKecepatan(int a){
	maxKecepatan = a;
}
void MobilCepat::bunyikanKlakson(){
	cout<<"Ngeng...din...din\n";
}
void MobilCepat::cetakJenisBahanBakar(){
	cout<<"Avtur\n";
}
