#include "A.hpp"

int main(){
	A x('1');
	A b('2');
	A c = x;
	c = b;
	c.show();
	return 0;
}
