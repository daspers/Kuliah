#include <iostream>
#include "Polinom.hpp"

using namespace std;

Polinom::Polinom(){
	for(int i=0;i<MAX_LENGTH;i++){
		koef[i] = 0;
	}
	derajat = 0;
}

Polinom::Polinom(int tes){
	for(int i=0;i<MAX_LENGTH;i++){
		koef[i] = 0;
	}
	derajat = tes;
}

Polinom::Polinom(const Polinom& tes){
	for(int i=0;i<MAX_LENGTH;i++){
		koef[i] = 0;
	}
	for(int i=0;i<=tes.derajat;i++){
		koef[i] = tes.koef[i];
	}
	derajat = tes.derajat;
}

Polinom::~Polinom(){
	
}

Polinom& Polinom::operator=(const Polinom& tes){
	for(int i=0;i<MAX_LENGTH;i++)
		koef[i] = 0;
	for(int i=0;i<=tes.derajat;i++){
		koef[i] = tes.koef[i];
	}
	derajat = tes.derajat;
	return *this;
}

int Polinom::getKoefAt(int idx) const{
	return koef[idx];
}

int Polinom::getDerajat() const{
	return derajat;
}

void Polinom::setKoefAt(int idx, int val){
	koef[idx] = val;
}

void Polinom::setDerajat(int val){
	if(val<derajat){
		for(int i =val+1;i<=derajat;i++)
			koef[i] = 0;
	}
	derajat = val;
}

Polinom operator+(const Polinom& p1, const Polinom& p2) // Penjumlahan 2 buah Polinom.
{
	int ma = p1.getDerajat();
	if(ma < p2.getDerajat())
		ma = p2.getDerajat();
	Polinom tem(ma);
	for(int i=0;i<=ma;i++){
		tem.koef[i] = p1.getKoefAt(i)+p2.getKoefAt(i);
	}
	return tem;
}

Polinom operator-(const Polinom& p1, const Polinom& p2) // Pengurangan 2 buah Polinom.
{
	int ma = p1.getDerajat();
	if(ma < p2.getDerajat())
		ma = p2.getDerajat();
	Polinom tem(ma);
	for(int i=0;i<=ma;i++){
		tem.koef[i] = p1.getKoefAt(i)-p2.getKoefAt(i);
	}
	return tem;
}

Polinom operator*(const Polinom& p, const int c) // Perkalian Polinom dengan konstanta
{
	Polinom tem(p.getDerajat());
	for(int i=0;i<=tem.derajat;i++){
		tem.koef[i] = p.getKoefAt(i)*c;
	}
	return tem;
}

Polinom operator*(const int c, const Polinom& p) // Perkalian Polinom dengan konstanta (sifat komutatif)
{
	Polinom tem(p.getDerajat());
	for(int i=0;i<=tem.derajat;i++){
		tem.koef[i] = p.getKoefAt(i)*c;
	}
	return tem;
}

Polinom operator/(const Polinom& p, const int c){
	Polinom tem(p.getDerajat());
	for(int i=0;i<=tem.derajat;i++){
		tem.koef[i] = p.getKoefAt(i)/c;
	}
	return tem;
}

void Polinom::input(){
	for(int i=0;i<=derajat;i++)
		cin>>koef[i];
}

void Polinom::printKoef(){
	for(int i=0;i<=derajat;i++)
		cout<<koef[i]<<endl;
}

int Polinom::substitute(int x){
	int res = 0;
	for(int i = derajat;i>=0;i--){
		res = res * x + koef[i];
	}
	return res;
}

Polinom Polinom::derive(){
	if(derajat == 0){
		Polinom tem(0);
		tem.koef[0] = 0;
		return tem;
	}
	else{
		Polinom tem(derajat-1);
		for(int i=0;i<derajat;i++)
			tem.koef[i] = koef[i+1]*(i+1);
		return tem;
	}
}

void Polinom::print(){
	bool wew = false;
	if(koef[0]!=0){
		if(koef[0]<0)
		;
		cout<<koef[0];
		wew = true;
	}
	for(int i=1;i<=derajat;i++){
		if(koef[i]!=0){
			if(koef[i]<0)
			;
			else if(wew){
				cout<<"+";
			}
			cout<<koef[i]<<"x^"<<i;
			wew= true;
		}
	}
	if(!wew)
		cout<<"0";
	cout<<endl;
}
