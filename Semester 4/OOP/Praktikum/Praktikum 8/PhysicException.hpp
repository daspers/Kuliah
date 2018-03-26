#include <string>
//#include "Physic.hpp"
using namespace std;

class PhysicException{
	private :
		const string msg;
	public :
		PhysicException(const string&);
		string getMsg() const;
};
