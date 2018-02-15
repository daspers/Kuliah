#include <iostream>
#include "Polinom.hpp"

using namespace std;

Polinom::Polinom(){
	koef = new int[1];
	koef[0] = 0;
	derajat = 0;
}

Polinom::Polinom(int tes){
	koef = new int[tes+1];
	derajat = tes;
	for(int i=0;i<=tes;i++){
		koef[i] = 0;
	}
}

Polinom::Polinom(const Polinom& tes){
	koef = new int[tes.derajat+1];
	derajat = tes.derajat;
	for(int i=0;i<=tes.derajat;i++){
		koef[i] = tes.koef[i];
	}
}

Polinom::~Polinom(){
	delete[] koef;
}

Polinom& Polinom::operator=(const Polinom& tes){
	if(derajat!=tes.derajat){
		delete[] koef;
		koef = new int[tes.derajat+1];
	}
	derajat = tes.derajat;
	for(int i=0;i<=tes.derajat;i++){
		koef[i] = tes.koef[i];
	}
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
	derajat = val;
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

