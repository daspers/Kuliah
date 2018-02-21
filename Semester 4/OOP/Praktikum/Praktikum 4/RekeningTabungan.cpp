#include "Rekening.h"
#include "RekeningTabungan.h"

// Konstruktor menginisialisi saldo (parameter 1) dan biaya transaksi (parameter 2)
// Set biaya transaksi 0.0 apabila biaya transaksi bernilai negatif
RekeningTabungan::RekeningTabungan(double a, double b) : Rekening(a)
{
	if(b<0)
		biayaTransaksi = 0;
	else
		biayaTransaksi = b;
}

// Getter, Setter
void RekeningTabungan::setBiayaTransaksi(double val)
{
	if(val<0)
		biayaTransaksi = 0;
	else
		biayaTransaksi = val;
}

double RekeningTabungan::getBiayaTransaksi() const
{
	return biayaTransaksi;
}

// Member Function
// Panggil fungsi simpanUang dari parent class
// Kurangkan saldo dengan biaya transaksi
void RekeningTabungan::simpanUang(double val)
{
	Rekening::simpanUang(val-biayaTransaksi);
}

// Panggil fungsi tarikUang dari parent class
// Kurangkan saldo dengan biaya transaksi hanya jika penarikan uang berhasil
// Saldo mungkin saja menjadi negatif apabila setelah penarikan, saldo < biaya transaksi
// Kembalikan boolean yang mengindikasikan apakah uang berhasil ditarik atau tidak
bool RekeningTabungan::tarikUang(double val)
{
	if(Rekening::tarikUang(val)){
		Rekening::setSaldo(Rekening::getSaldo() - biayaTransaksi);
		return true;
	}
	return false;
}
