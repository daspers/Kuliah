#include "GrayscalePixel.hpp"
//ctor dengan parameter 3 buah integer (r, g, dan b dengan range nilai 0 <= x <= 255, wajib dicek)
//Apabila masukan > 255, kembalikan nilai mulai dari 0 lagi
//Contoh: 256 -> 0, 257 -> 1, dst
//Apabila masukan < 0, kembalikan nilai absolutnya tetap pertahankan range 0 <= x <= 255.
//Contoh: -12 -> 12, -257 -> 1

#include <iostream>

using namespace std;

GrayscalePixel::GrayscalePixel(int r, int g, int b){
	rgb = new int [3];
	if(r<0)
		r = ~r+1;
	if(g<0)
		g = ~g+1;
	if(b<0)
		b = ~b+1;
	r%=256;
	g%=256;
	b%=256;
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}
//cctor
GrayscalePixel::GrayscalePixel(const GrayscalePixel& a){
	rgb = new int[3];
	rgb[0] = a.rgb[0];
	rgb[1] = a.rgb[1];
	rgb[2] = a.rgb[2];
}
//dtor
GrayscalePixel::~GrayscalePixel()
{
	delete[] rgb;
}


//getter&setter (masukan setter TIDAK selalu valid)
int GrayscalePixel::getRed() const
{
	return rgb[0];
}
int GrayscalePixel::getGreen() const
{
	return rgb[1];
}
int GrayscalePixel::getBlue() const
{
	return rgb[2];
}
void GrayscalePixel::setRed(int r)
{
	if(r<0)
		r = ~r+1;
	r%=256;
	rgb[0]=r;
}
void GrayscalePixel::setGreen(int g)
{
	if(g<0)
		g = ~g+1;
	g%=256;
	rgb[1] = g;
}
void GrayscalePixel::setBlue(int b)
{
	if(b<0)
		b = ~b+1;
	b%=256;
	rgb[2] = b;
}

//Implementasi preProcess (method untuk membuat pixel menjadi grayscale)
//Grayscale pixel adalah pixel yang memiliki nilai R, G, dan B = rata-rata RGB.
//NB: Lakukan pembulatan ke bawah.
void GrayscalePixel::preProcess()
{
	int avg = rgb[0]+rgb[1]+rgb[2];
	avg/=3;
	rgb[0]=rgb[1]=rgb[2]=avg;
}

//Implementasi print (method untuk menampilkan pixel)
//format: GRAYSCALE(r,g,b) diakhiri endline
//contoh: GRAYSCALE(1,12,123)
void GrayscalePixel::print()
{
	cout<<"GRAYSCALE("<<rgb[0]<<","<<rgb[1]<<","<<rgb[2]<<")\n";
}
