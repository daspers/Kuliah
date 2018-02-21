
#ifndef __MAHASISWA_HPP__
#define __MAHASISWA_HPP__
#include "Alamat.hpp"

using namespace std;

class Mahasiswa{
	public :
		Mahasiswa(const string& a, const string& b);
		Mahasiswa(const string& a, const string& b, const Alamat& c);
		Mahasiswa(const Mahasiswa&);
		~Mahasiswa();
		void setNim(const string& );
		void setNama(const string& );
		void setAlamat(const Alamat& );
		string getNim() const;
		string getNama() const;
		Alamat getAlamat() const;
	private:
		string nim;
		string nama;
		Alamat alamat;
};
#endif