#ifndef __MOBIL_H__
#define __MOBIL_H__

#include <string>
using namespace std;

class Mobil{
public:
	Mobil(string, string, string, int, int, int);
	string getTahun() const;
	string getWarna() const;
	string getMerek() const;
	int getPanjang() const;
	int getLebar() const;
	int getTinggi() const;
	void setTahun(string);
	void setWarna(string);
	void setMerek(string);
	void setPanjang(int);
	void setLebar(int);
	void setTinggi(int);
	virtual void bunyikanKlakson();
	virtual void cetakJenisBahanBakar();
protected:
	string tahun;
	string warna;
	string merek;
	int panjang;
	int lebar;
	int tinggi;
};

class MobilCepat : public Mobil{
public :
	MobilCepat(string, string, string, int, int, int, int);
	int getMaxKecepatan() const;
	void setMaxKecepatan(int);
	void bunyikanKlakson();
	void cetakJenisBahanBakar();
protected :
	int maxKecepatan;
};

#endif
