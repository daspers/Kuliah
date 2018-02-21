#include "Alamat.hpp"
#include <string>
#include <iostream>

using namespace std;

Alamat::Alamat()
{
	provinsi = "";
	kota="";
	jalan="";
}

Alamat::Alamat(const string &a, const string &b, const string &c)
{
	provinsi = a;
	kota = b;
	jalan = c;
}

void Alamat::setJalan(const string &s)
{
	jalan = s;
}

void Alamat::setProvinsi(const string &s)
{
	provinsi = s;
}

void Alamat::setKota(const string &s)
{
	kota = s;
}

string Alamat::getJalan() const
{
	return jalan;
}

string Alamat::getProvinsi() const
{
	return provinsi;
}

string Alamat::getKota() const
{
	return kota;
}

string Alamat::getAlamatLengkap()
{
	return "Jalan "+jalan+", "+kota+", "+provinsi+".";
}
