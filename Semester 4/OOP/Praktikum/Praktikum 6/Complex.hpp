	
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

using namespace std;

template<class T>
class Complex {
	public:
		// ctor
		// inisialisasi real dan imaginer dengan 0
		Complex();
		// inisialisasi real dengan paramater pertama dan imaginer dengan parameter kedua
		Complex(T, T);
		
		// Getter, Setter
		T getReal() const;
		T getImaginer() const;
		void setReal(T);
		void setImaginer(T);

		Complex operator +(Complex const &comp) const;
		Complex operator -(Complex const &comp) const;
		Complex operator *(Complex const &comp) const;
		Complex& operator +=(const Complex&);
		Complex& operator -=(const Complex&);
		Complex& operator *=(const Complex&);

	private: 
		T real, imaginer;
};

template<class T>
Complex<T>::Complex(){
	real = 0;
	imaginer = 0;
}

template<class T>
Complex<T>::Complex(T a, T b){
	real =a;
	imaginer = b;
}

template<class T>
T Complex<T>::getReal() const{
	return real;
}

template<class T>
T Complex<T>::getImaginer() const{
	return imaginer;
}

template<class T>
void Complex<T>::setReal(T a){
	real = a;
}

template<class T>
void Complex<T>::setImaginer(T a){
	imaginer =a;
}

template<class T>
Complex<T> Complex<T>::operator +(Complex<T> const &comp) const{
	Complex Temp(real, imaginer);
	return Temp+=comp;
}

template<class T>
Complex<T> Complex<T>::operator -(Complex<T> const &comp) const{
	Complex Temp(real, imaginer);
	return Temp-=comp;
}

template<class T>
Complex<T> Complex<T>::operator *(Complex<T> const &comp) const{
	Complex Temp(real, imaginer);
	return Temp*=comp;
}

template<class T>
Complex<T>& Complex<T>::operator +=(const Complex<T>& a){
	real += a.real;
	imaginer += a.imaginer;
	return *this;
}

template<class T>
Complex<T>& Complex<T>::operator -=(const Complex<T>& a){
	real -= a.real;
	imaginer -= a.imaginer;
	return *this;
}

template<class T>
Complex<T>& Complex<T>::operator *=(const Complex<T>& comp){
	T tem = real;
	real = tem*comp.real - imaginer*comp.imaginer;
	imaginer = imaginer*comp.real + tem*comp.imaginer;
	return *this;
}

#endif
