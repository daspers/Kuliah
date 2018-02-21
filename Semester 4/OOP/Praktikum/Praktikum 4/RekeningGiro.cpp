#include "Rekening.h"
#include "RekeningGiro.h"

// Konstruktor menginisialisi saldo (parameter 1) dan suku bunga (parameter 2)
// Set suku bunga 0.0 apabila suku bunga bernilai negatif
RekeningGiro::RekeningGiro(double a, double b):Rekening(a)
{
	if(b<0)
		sukuBunga = 0;
	else
		sukuBunga = b;
}

// Getter, Setter
void RekeningGiro::setSukuBunga(double val)
{
	if(val<0)
		sukuBunga = 0;
	else
		sukuBunga = val;
}

double RekeningGiro::getSukuBunga() const
{
	return sukuBunga;
}

// Member Function
// Bunga dihitung dari saldo dikali suku bunga
double RekeningGiro::hitungBunga()
{
	return Rekening::getSaldo()*sukuBunga;
}
