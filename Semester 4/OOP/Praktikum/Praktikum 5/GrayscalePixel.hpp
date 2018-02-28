#ifndef __GrayscalePixel__
#define __GrayscalePixel__
#include "Pixel.hpp"

class GrayscalePixel : public Pixel {
    protected:
        int* rgb; //rgb[0] = r, rgb[1] = g, rgb[2] = b
	public :
    //ctor dengan parameter 3 buah integer (r, g, dan b dengan range nilai 0 <= x <= 255, wajib dicek)
    //Apabila masukan > 255, kembalikan nilai mulai dari 0 lagi
    //Contoh: 256 -> 0, 257 -> 1, dst
    //Apabila masukan < 0, kembalikan nilai absolutnya tetap pertahankan range 0 <= x <= 255.
    //Contoh: -12 -> 12, -257 -> 1
	GrayscalePixel(int , int , int );
    //cctor
	GrayscalePixel(const GrayscalePixel&);
    //dtor
	~GrayscalePixel();
    //getter&setter (masukan setter TIDAK selalu valid)
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);

    //Implementasi preProcess (method untuk membuat pixel menjadi grayscale)
    //Grayscale pixel adalah pixel yang memiliki nilai R, G, dan B = rata-rata RGB.
    //NB: Lakukan pembulatan ke bawah.
    void preProcess();

    //Implementasi print (method untuk menampilkan pixel)
    //format: GRAYSCALE(r,g,b) diakhiri endline
    //contoh: GRAYSCALE(1,12,123)
    void print();
};

#endif
