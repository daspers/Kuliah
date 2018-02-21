#include "Rekening.h"
// Konstruktor untuk menginisialisasi saldo
// Set saldo 0.0 apabila saldo bernilai negatif
Rekening::Rekening(double val)
{
	if(val<0)
		saldo = 0;
	else
		saldo = val;
}

// Getter, Setter
// Set saldo 0.0 apabila saldo bernilai negatif
void Rekening::setSaldo(double val)
{
	saldo = val;
}

double Rekening::getSaldo() const
{
	return saldo;
}

// Member Function
// Tambahkan sejumlah nominal uang ke saldo
void Rekening::simpanUang(double val)
{
	saldo+=val;
}

// Kurangkan sejumlah nominal uang dari saldo apabila saldo mencukupi (tidak negatif setelah dikurangkan)
// Kembalikan boolean yang mengindikasikan apakah uang berhasil ditarik atau tidak
bool Rekening::tarikUang(double val)
{
	if(val<=saldo){
		saldo -= val;
		return true;
	}
	return false;
}
