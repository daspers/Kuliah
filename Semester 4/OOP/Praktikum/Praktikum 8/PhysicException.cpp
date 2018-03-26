#include "PhysicException.hpp"

PhysicException::PhysicException(const string& t) : msg(t){
	
}

string PhysicException::getMsg() const{
	return msg;
}
