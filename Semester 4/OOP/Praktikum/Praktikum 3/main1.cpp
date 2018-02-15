#include "Box.h"

int main(){
	Box a(2);
	a.set(0,99);
	a.show();
	Box b = a;
	Box c(2);
	c = a;
	a.set(0,299);
	a.show();
	b.show();
	c.show();
	return 0;
}
