
#ifndef __ALAMAT_HPP__
#define __ALAMAT_HPP__
#include <string>

using namespace std;

class Alamat{
	public :
		Alamat();
		Alamat(const string &a, const string &b, const string &c);
		void setJalan(const string&);
		void setProvinsi(const string&);
		void setKota(const string &);
		string getJalan() const;
		string getProvinsi() const;
		string getKota() const;
		string getAlamatLengkap();
	private :
		string provinsi;
		string kota;
		string jalan;
};
#endif