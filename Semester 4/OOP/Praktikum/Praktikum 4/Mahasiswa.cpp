#include "Mahasiswa.hpp"

using namespace std;

Mahasiswa::Mahasiswa(const string& a, const string& b)
{
	nama = a;
	nim = b;
}

Mahasiswa::Mahasiswa(const string& a, const string& b, const Alamat& c)
{
	nama = a;
	nim = b;
	alamat.setJalan(c.getJalan());
	alamat.setKota(c.getKota());
	alamat.setProvinsi(c.getProvinsi());
}

Mahasiswa::Mahasiswa(const Mahasiswa& c)
{
	nama = c.nama;
	nim = c.nim;
	alamat.setJalan(c.alamat.getJalan());
	alamat.setKota(c.alamat.getKota());
	alamat.setProvinsi(c.alamat.getProvinsi());
}

Mahasiswa::~Mahasiswa()
{
	
}

void Mahasiswa::setNim(const string& a)
{
	nim = a;
}
void Mahasiswa::setNama(const string& a)
{
	nama = a;
}
void Mahasiswa::setAlamat(const Alamat& a)
{
	alamat = a;
}
string Mahasiswa::getNim() const
{
	return nim;
}
string Mahasiswa::getNama() const
{
	return nama;
}

Alamat Mahasiswa::getAlamat() const
{
	return alamat;
}
