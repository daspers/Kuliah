#ifndef __HEWAN_H__
#define __HEWAN_H__
#include <iostream>

using namespace std;

class Hewan{
	public :
		Hewan(string a){nama = a;}
		~Hewan(){cout<<"Hewan mati "<<nama<<endl;}
		virtual void print(){
			cout<<"Hewan ini namanya "<<nama<<endl;
		}
	protected :
		string nama;
};

class Anjing : public Hewan{
	public:
		Anjing(string a):Hewan(a){}
		~Anjing(){cout<<"Anjing mati "<<nama<<endl;}
		virtual void print(){
			cout<<"Anjing ini namanya "<<nama<<endl;
		}
};

class Kucing : public Hewan{
	public:
		Kucing(string a):Hewan(a){}
		virtual ~Kucing(){cout<<"Kucing mati "<<nama<<endl;}
};

class KucingAnggora : public Kucing{
	public :
		KucingAnggora(string a, string b) : Kucing(a){
			pemilik = b;
		}
		~KucingAnggora(){cout<<"Kucing anggora mati "<<nama<<endl;}
		void print(){
			cout<<"Kucing anggora ini namanya "<<nama<<". Pemiliknya adalah "<<pemilik<<endl;
		}
	protected :
		string pemilik;
};

class AnjingBulldog : public Anjing{
	public :
		AnjingBulldog(string a, string b):Anjing(a){
			pemilik = b;
		}
		~AnjingBulldog(){cout<<"Anjing bulldog mati "<<nama<<endl;}
		void print(){
			cout<<"Anjing bulldog ini namanya "<<nama<<". Pemiliknya adalah "<<pemilik<<endl;
		}
	protected :
		string pemilik;
};

#endif
