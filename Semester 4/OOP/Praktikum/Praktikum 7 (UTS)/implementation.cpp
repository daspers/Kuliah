#include <iostream>
using namespace std;


class A {
private:
    int y;
public:
    A(int a) {
        y = a;
        cout << "A cons " << y << endl;
    }

    // implementasikan destruktor kelas A yang akan mencetak  "A decs " + nilai y diikuti dengan newline
    ~A(){
		cout << "A decs " << y << endl;
	}
};

// Isi dengan definisi kelas X yang adalah turunan dari kelas A

class X : public A

{
private:
    int x;
public:
    // Isi dengan definisi konstruktor untuk kelas X. Kontruktor menerima dua buah parameter bertipe integer. Parameter kedua berfungsi untuk menginstansiasi kelas A

    X(int a, int b) :A(b) 

    {
        x = a;
        cout << "X cons " << x << endl;
    }
   
    // implementasikan destruktor kelas X yang akan mencetak  "X decs " + nilai x diikuti dengan newline
    ~X(){
		cout << "X decs " << x << endl;
	}
   
};

class Y
{
private:
    int z;
public:
    Y(int a)
    {
        z = a;       
        cout << "Y cons " << z << endl;
    }
   
    // implementasikan destruktor kelas Y yang akan mencetak  "Y decs " + nilai z diikuti dengan newline
    ~Y(){
		cout << "Y decs " << z << endl;
	}

    void cetak() {
        cout << "Y cetak" << endl;
    }
   
};

// kelas Z adalah kelas turunan X dan turunan Y. Perhatikan urutan penulisan pewarisan kelasnya. Kelas Z tidak dapat mengakses method publik dari kelas Y.

class Z : public X, public Y

{

public:
    // Isi dengan konstruktor kelas Z. Konstruktor kelas Z menerima tiga buah parameter bertipe integer. Parameter pertama dan kedua berfungsi untuk instansiasi kelas X sedangkan parameter ketiga berfungsi untuk menginstansiasi kelas Y
    Z(int a, int b, int c) : X(a,b), Y(c)
    {
        cout << "Z cons " << a << " " << b << " " << c << endl;
    }
   
    // implementasikan destruktor kelas Z yang akan mencetak  "Z decs" diikuti dengan newline
    ~Z(){
		cout << "Z decs"<< endl;
	}
   
};

