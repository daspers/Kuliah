#include "BlackWhitePixel.hpp"

#include <iostream>

using namespace std;

//cctor
BlackWhitePixel::BlackWhitePixel(const BlackWhitePixel& a):GrayscalePixel(a), THRESHOLD(a.THRESHOLD){
	
}

BlackWhitePixel::BlackWhitePixel(int r, int g,  int b, int t): GrayscalePixel(r,g,b), THRESHOLD(t){}

//dtor
//getter
int BlackWhitePixel::getThreshold() const{
	return THRESHOLD;
}

//Implementasi preProcess (method untuk membuat pixel menjadi warna hitam atau putih)
//Black and White pixel adalah grayscale pixel yang:
//jika intensitasnya >= threshold maka pixel berwarna putih (R=255, G=255, B=255)
//jika intensitasnya < threshold maka pixel berwarna hitam (R=0, G=0, B=0)
//Petunjuk: gunakan preProcess grayscale terlebih dahulu untuk mencari intensitas.
void BlackWhitePixel::preProcess(){
	GrayscalePixel::preProcess();
	if(rgb[0]>=THRESHOLD){
		rgb[0]=rgb[1]=rgb[2] = 255;
	}
	else{
		rgb[0]=rgb[1]=rgb[2] = 0;
	}
}
//Implementasi print (method untuk menampilkan pixel)
//format: BW(r,g,b,THRESHOLD) diahkhiri endline
//contoh: BW(1,12,123,50)
void BlackWhitePixel::print(){
	cout<<"BW("<<rgb[0]<<","<<rgb[1]<<","<<rgb[2]<<","<<THRESHOLD<<")\n";
}
