#include "Vehicle.h"
#include "Bike.h"
#include "Car.h"

int main(){
	Vehicle a(3,2);
	Vehicle b(a);
	Vehicle c(6,50);
	Car f (8);
	Car f1 (f);
	Car e (6);
	Bike g;
	e.drive();
	g.show();
	g.ride();
	return 0;
}
