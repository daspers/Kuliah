#include <cmath>

template <class T>
class Point {

public:

    Point(); // absis dan ordinat = 0

    Point(T, T);

    Point(const Point<T>&);

    Point<T>& operator=(const Point<T>&);

    

    int getAbsis() const;

    int getOrdinat() const;

    void setAbsis(T);

    void setOrdinat(T);

    double countDistance(Point<T>); //menghasilkan akar((x1-x2)^2+(y1-y2)^2)


    Point<T> operator +(const Point<T>&) const; //xnew=x1+x2, ynew=y1+y2

    Point<T> operator -(const Point<T>&) const; //xnew=x1-x2, ynew=y1-y2

    Point<T>& operator +=(const Point<T>&);

    Point<T>& operator -=(const Point<T>&);

    

private:

    T x; //absis

    T y; //ordinat

};
template <class T>
Point<T>::Point() // absis dan ordinat = 0
{
	x = 0;
	y = 0;
}
template <class T>
Point<T>::Point(T a, T b)
{
	x = a;
	y = b;	
}
template <class T>
Point<T>::Point(const Point<T>& t){
	x = t.x;
	y = t.y;
}
template <class T>
Point<T>& Point<T>::operator=(const Point<T>& t)
{
	x = t.x;
	y = t.y;
}


template <class T>
int Point<T>::getAbsis() const
{
	return x;
}
template <class T>
int Point<T>::getOrdinat() const
{
	return y;
}
template <class T>
void Point<T>::setAbsis(T a)
{
	x = a;
}
template <class T>
void Point<T>::setOrdinat(T b)
{
	y = b;
}
template <class T>
double Point<T>::countDistance(Point<T> t) //menghasilkan akar((x1-x2)^2+(y1-y2)^2)
{
	T xx = x - t.x;
	T yy = y - t.y; 
	return sqrt(xx*xx+yy*yy); 
}

template <class T>
Point<T> Point<T>::operator +(const Point<T>& t) const //xnew=x1+x2, ynew=y1+y2
{
	Point tem(x+t.x, y+t.y);
	return tem;
}
template <class T>
Point<T> Point<T>::operator -(const Point<T>& t) const //xnew=x1-x2, ynew=y1-y2
{
	Point<T> tem(x-t.x, y-t.y);
	return tem;
}
template <class T>
Point<T>& Point<T>::operator +=(const Point<T>& t)
{
	x += t.x;
	y += t.y;
	return *this;
}
template <class T>
Point<T>& Point<T>::operator -=(const Point<T>& t)
{
	x -= t.x;
	y -= t.y;
	return *this;
}
