#include <iostream>

using namespace std;

template <class T>
void print(T param1){
	cout<<"Masukan anda : "<<param1<<"\n";
}

template <>
void print<char>(char param1){
	cout<<"Masukan SPECIAL anda : "<<param1<<"\n";
}

template <class T, int S>
void print(T param1){
	for(int i=0;i<S;i++)
		cout<<"Masukan anda : "<<param1<<"\n";
}

template <class T, class U>
void print(T param1, U param2){
	cout<<"Masukan anda : "<<param1<<" dan "<<param2<<"\n";
}
