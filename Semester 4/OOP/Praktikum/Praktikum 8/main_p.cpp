#include "Physic.hpp"
#include <iostream>

using namespace std;

int main(){
	try{
		Physic P(100,4);
		cout<<P.constant()<<"\n";
	}
	catch(const PhysicException& e){
		cout<<e.getMsg()<<endl;
	}
	try{
		Physic P(64,4);
		cout<<P.constant()<<"\n";
	}
	catch(const PhysicException& e){
		cout<<e.getMsg()<<endl;
	}
	try{
		Physic P(100,0);
		cout<<P.constant()<<"\n";
	}
	catch(const PhysicException& e){
		cout<<e.getMsg()<<endl;
	}
	try{
		Physic P(10,0);
		cout<<P.constant()<<"\n";
	}
	catch(const PhysicException& e){
		cout<<e.getMsg()<<endl;
	}
}
