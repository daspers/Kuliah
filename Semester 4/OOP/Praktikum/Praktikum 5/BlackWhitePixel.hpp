#ifndef	__BlackWhitePixel__
#define __BlackWhitePixel__
#include "GrayscalePixel.hpp"

class BlackWhitePixel : public GrayscalePixel { 
    private:
        const int THRESHOLD;
	public :
    //ctor dengan parameter 4 buah integer (r, g, b, dan threshold)
    //rgb memiliki range nilai 0 <= x <= 255,  wajib dicek
    //nilai threshold bebas, TIDAK perlu dicek
    //Apabila masukan > 255, kembalian nilai mulai dari 0 lagi (contoh: 256 -> 0, 257 -> 1, dst)
    //Apabila masukan < 0, kembalikan nilai absolutnya tetap pertahankan range 0 <= x <= 255.
    //Contoh: -12 -> 12, -257 -> 1
	BlackWhitePixel(int r, int g,  int b, int t);
    //cctor
	BlackWhitePixel(const BlackWhitePixel&);
    //dtor
    //getter
    int getThreshold() const;

    //Implementasi preProcess (method untuk membuat pixel menjadi warna hitam atau putih)
    //Black and White pixel adalah grayscale pixel yang:
    //jika intensitasnya >= threshold maka pixel berwarna putih (R=255, G=255, B=255)
    //jika intensitasnya < threshold maka pixel berwarna hitam (R=0, G=0, B=0)
    //Petunjuk: gunakan preProcess grayscale terlebih dahulu untuk mencari intensitas.
	void preProcess();
    //Implementasi print (method untuk menampilkan pixel)
    //format: BW(r,g,b,THRESHOLD) diahkhiri endline
    //contoh: BW(1,12,123,50)
    void print();
};

#endif
