#include <cmath>
#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

#define MAX_N 10 // adjust this value as needed
#define eps 2.71828183

struct AugmentedMatrix { 
// Tipe data untuk menyimpan Matriks
	double mat[MAX_N][MAX_N + 1];
};

struct ColumnVector {
// Tipe data untuk menyimpan jawaban atau koefisien 
	double vec[MAX_N]; 
};
int N; // Untuk  menyimpan indeks matriks agar menjadi persegi
int M; // Untuk menyimpan banyak persamaan
int NS; // Untuk menyimpan banyak variabel
AugmentedMatrix Aug;
string Variabel = {"abcdefghijklmnopqrstuvwxyz"}; // Untuk menyimpan huruf dari setiap variabel ke-i ketika menjadi parameter
bool Parameter[100] = {0}; // Untuk menyimpan apakah variabel ke-i ialah parameter atau bukan

double fx(double x) {
//Untuk mengembalikan nilai dari fungsi yang telah diberikan	
	double Hasil;
	
	Hasil = 1/((1 + sqrt(x) + pow(x, 2)) * pow(eps, x));
	
	return Hasil;
}

void BacaMatriks()
{
// Untuk membaca Matriks yang ingin dieksekusi
	cout << "Masukkan banyak variabel : ";
	cin >> N; col
	cout << "Masukkan banyak persamaan : ";
	cin >> M; row
	cout << "Masukkan persamaan : \n";

	if (N > M) {
		for(int i = 0; i < M; i++) {
			for(int j = 0; j <= N; j++) {
				cin >> Aug.mat[i][j];
			}
		}
		for(int i = M; i < N; i++) {
			for(int j = 0; j <= N; j++) {
				Aug.mat[i][j] = 0;
			}
		}
		NS = N;
	} else {
		for(int i = 0; i < M; i++) {
			for(int j = 0; j < N; j++) {
				cin >> Aug.mat[i][j];
			}
			for(int j = N; j < M; j++) {
				Aug.mat[i][j] = 0;
			}
			cin >> Aug.mat[i][M];
		}
		NS = N;
		N = M;
	}
}

void TulisMatriks() {
//Untuk menulis isi dari matriks
	for(int i = 0; i < N; i++) {
		for(int j = 0; j <= N; j++) {
			cout << Aug.mat[i][j] << " ";
		}
		cout << "\n";
	}
}

void IsiMatriksHilbert()
// Untuk mengisi matriks dari persamaan Hilbert
{
	cout << "Masukkan N : ";
	cin >> N;
	
	NS = N;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			Aug.mat[i][j] = (((double) 1)/((double) (j+i+1)) * (double)(10000));
		}
	}
	
	for(int i = 0; i < N; i++) {
		Aug.mat[i][N] = 1;
	}

}

void IsiInterpolasifungsie() {
//Untuk mengisi matriks danri fungsi yang telah diberikan	
	double a, b;
	
	a = 0;
	b = 1;

	cout << "Masukkan N : ";
	cin >> N;
	
	double h = (b-a)/N;
	
	N++;
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			Aug.mat[i][j] = pow(a, j);
		}
		Aug.mat[i][N] = fx(a);
		a = a+h;
	}
}

void IsiInterpolasi(){
// Untuk mengisi matriks sesuai dengan masukan dari user
	double x;
	
	cout << "Masukkan banyak x yang di input : ";
	cin >> N;

	NS = N;
	
	for(int i = 0; i < N; i++) {
		cout << "Masukkan x" << i << " : ";
		cin >> x;
		for(int j = 0; j < N; j++) {
			Aug.mat[i][j] = pow(x, j);
		}
	}

	for(int i = 0; i < N; i++) {
		cout << "f(x" << i << ") = ";
		cin >> Aug.mat[i][N];
	}
}

void Pindahkan() {
//Untuk mengurutkan matriks agar mendapatkan variabel yang tepat untuk dijadikan parameter
	double t;
	
	for(int i = 0; i < N; i++) {
		if (fabs(Aug.mat[i][i]) <= 0.0000000001) {
			for(int j = i-1; j >= 0; j--) {
				if (fabs(Aug.mat[j][i]) >= 0.000000001) {
					if (fabs(Aug.mat[j][j]) <= 0.00000001) {
						for(int k = 0; k <= N; k++) {
							t = Aug.mat[i][k], Aug.mat[i][k] = Aug.mat[j][k], Aug.mat[j][k] = t;
						}
					}
				}
			}
		}
	}
}


void Sederhanakan() {
// Untuk menyederhanakan Matriks oleh metode Gauss
	double t;
	bool tidak;
	
	for(int i = 0; i < N - 1; i++) {
		if (fabs(Aug.mat[i][i]) < 0.0000000001) {
			for(int j = i+1; j <N; j++) {
				if (fabs(Aug.mat[i][j]) > 0.0000000001) {
					for(int k = i + 1; k < N; k++) {
						if (fabs(Aug.mat[k][j]) > 0.0000000001) {
							tidak = true;
							for(int m = 0; m < j; m++) {
								if (fabs(Aug.mat[k][m]) > 0.0000000001) {
									tidak = false;
								}
							}
							if (tidak) {
								t = Aug.mat[i][j]/Aug.mat[k][j];
								for(int l = N; l >= j; l--) {
									Aug.mat[i][l] -= Aug.mat[k][l] * t;
								}
								break;								
							}							
								 
						}
					}
				}
			}
		} else {
			t = 1/Aug.mat[i][i];
			for(int j = i; j <= N; j++) {
				Aug.mat[i][j] *= t;
			}
		}
	}
}

void GaussianElimination() {
// input: N, Augmented Matrix Aug, output: Column vector X, the answer
 	int i, j, k, l; double t;

 	for (i = 0; i < N - 1; i++) { // the forward elimination phase
 		l = i;
		for (j = i + 1; j < N; j++) {// which row has largest column value
			if (fabs(Aug.mat[j][i]) > fabs(Aug.mat[l][i])) {
				l = j; // remember this row l
			}
		}
		// swap this pivot row, reason: minimize floating point error
		for (k = i; k <= N; k++) { // t is a temporary double variable
			t = Aug.mat[i][k], Aug.mat[i][k] = Aug.mat[l][k], Aug.mat[l][k] = t;
		}		
		
		if (fabs(Aug.mat[i][i]) < 0.00000001) {
			continue;
		} else {
			for (j = i + 1; j < N; j++) {// the actual forward elimination phase
				for (k = N; k >= i; k--) {
					Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];	
				}
			}
		}
		Pindahkan();
	}
	Sederhanakan();
}


void SederhanakanJordan() {
// Untuk menyederhanakan Matriks agar menjadi Matriks Gauss-Jordan
	double t;
	
	for(int i = 1; i < N; i++) {
		if (fabs(Aug.mat[i][i]) <= 1.00000001 && fabs(Aug.mat[i][i]) >= 0.000000001) {
			for(int k = i-1; k >= 0; k--) {
				if (fabs(Aug.mat[k][i]) > 0.0000000001) {
					t = Aug.mat[k][i];
					for(int j = i; j <= N; j++) {
						Aug.mat[k][j] -= Aug.mat[i][j] * t;
					}
				}	
			}
		}	
	}	
}

void GausJordanElimination() {
// input: N, Augmented Matrix Aug, output: Column vector X, the answer
 	int i, j, k, l; double t;

 	for (i = 0; i < N; i++) { // the forward elimination phase
 		l = i;
		for (j = i + 1; j < N; j++) {// which row has largest column value
			if (fabs(Aug.mat[j][i]) > fabs(Aug.mat[l][i])) {
				l = j; // remember this row l
			}
		}
		// swap this pivot row, reason: minimize floating point error
		for (k = i; k <= N; k++) { // t is a temporary double variable
			t = Aug.mat[i][k], Aug.mat[i][k] = Aug.mat[l][k], Aug.mat[l][k] = t;
		}		
		
		if (fabs(Aug.mat[i][i]) < 0.00000001) {
			continue;
		} else {
			for (j = i + 1; j < N; j++) {// the actual forward elimination phase
				for (k = N; k >= i; k--) {
					Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];	
				}
			}
			t = 1/Aug.mat[i][i];
			for(j = i; j <= N; j++) {
				Aug.mat[i][j] *= t;
			}
		}
		Pindahkan();	
	}	
			
	SederhanakanJordan();
	
	int pilihan;
	
	cout << "Apakah Anda ingin Menuliskan Hasil Gauss-Jordan Elimination : \n";
	cout << "1. Yes\n2. No\n";
	cin >> pilihan;
	if (pilihan == 1) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j <= N; j++) {
				cout << Aug.mat[i][j] << " ";
			}
			cout << "\n";
		}
	}
}

bool NoSolution() {
// Untuk mengecek apakah matriks tersebut mempunyai solusi atau tidak
	bool NoSolution = false;
	for(int i = 0; i < N; i++) {
		if (fabs(Aug.mat[i][i]) <= 0.0000000001) {
			NoSolution = true;
			for(int j = i+1; j < N; j++) {
				if (fabs(Aug.mat[i][j]) >= 0.0000000001) {
					NoSolution = false;
				}
			}
			if (NoSolution) {
				if (fabs(Aug.mat[i][N]) <= 0.0000000001) {
					NoSolution = false;
				}
			}			
		}
	}
	
	return NoSolution;
}

void Solution() {
// Untuk mengeluarkan Solusi dari matriks tersebut dengan metode Gauss-Jordan
	GausJordanElimination();
	
	for(int i = 0; i < NS; i++) {
		if (fabs(Aug.mat[i][i]) <= 0.0000000001) {
			Parameter[i] = true;
		}
	}
	
	if (NoSolution()) {
		cout << "TIDAK ADA SOLUSI\n";
	} else if (!NoSolution()) {
		for(int i = 0; i < NS; i++) {
			if (Parameter[i]) {
				cout << "x" << i << " = " << Variabel[i] << "\n";
			} else {
				cout << "x" << i << " = " << Aug.mat[i][N];
				for(int j = i + 1; j < NS; j++) {
					if (Parameter[j] && fabs(Aug.mat[i][j]) >= 0.0000000001) {
						if (Aug.mat[i][j] < 0) {
							cout << " + " << fabs(Aug.mat[i][j]) << Variabel[j];
						} else {
							cout << " - " << Aug.mat[i][j] << Variabel[j];
						}
					}
				}
				printf("\n");
			}
		}
	} 
}

void TulisPolinom() {
	for(int i = 0; i < N; i++) {
		if (i == 0) {
			cout << Aug.mat[i][N];
		} else {
			cout << " + " << Aug.mat[i][N] << "x^" << i;
		}
	}
	printf("\n");
}

void SolusiInterpolasifungsie() {
//Untuk mengeluarkan Solusi dari Persoalan Interpolasi dengan fungsi yang diberikan
	GausJordanElimination();
	double a, b;
	int pilihan;

	cout << "Apakah anda ingin menuliskan polinom : \n1. Yes\n2.No\n";
	cin >> pilihan;
	if (pilihan == 1) {
		TulisPolinom();
	}

	cout << "Masukkan selang atas : ";
	cin >> a;
	cout << "Masukkan selang bawah : ";
	cin >> b;
	
	double h = (b-a)/(N-1);
	
	cout << "Hampiran dari fungsinya ialah : \n";
	for(int i = 0; i < N; i++) {
		cout << "f(" << a << ") = ";
		double Hasil = 0;
		for(int j = 0; j < N; j++) {
			Hasil += Aug.mat[j][N]*pow(a, j);
		}
		cout << Hasil << "\n";
		a = a+h;
	}
}


void SolusiInterpolasi(){
//Untuk mengeluarkan Solusi dari Persoalan Interpolasi dengan nilai f(x) yang diberika
	GausJordanElimination();
	int banyak;
	int pilihan;
	double x;
	
	cout << "Apakah anda ingin menuliskan polinom : \n1. Yes\n2.No\n";
	cin >> pilihan;
	if (pilihan == 1) {
		TulisPolinom();
	}
	cout << "Masukkan banyak x yang mau dihampiri : ";
	cin >> banyak;
	for(int i = 0; i < banyak; i++) {
		cout << "Masukkan x : ";
		cin >> x;
		double Hasil = 0;
		for(int j = 0; j < N; j++) {
			Hasil += Aug.mat[j][N] * pow(x, j);
		}
		cout << "f(" << x << ") = " << Hasil << "\n";
	}
}

int main() {

	int pilihan;
	cout << "1. SPL biasa\n";
	cout << "2. interpolasi fungsi e\n";
	cout << "3. Hilbert\n";
	cout << "4. Interpolasi\n";
	
	cout << "Masukkan pilihan : ";
	cin >> pilihan;
	while (pilihan != 0) {
		if (pilihan == 1) {
			BacaMatriks();
			Solution();
		} else if (pilihan == 2) {
			IsiInterpolasifungsie();
			SolusiInterpolasifungsie();
		} else if (pilihan == 3) {
			IsiMatriksHilbert();
			Solution();
		} else if (pilihan == 4) {
			IsiInterpolasi();
			SolusiInterpolasi();
		}
		cout << "1. SPL biasa\n";
		cout << "2. interpolasi fungsi e\n";
		cout << "3. Hilbert\n";
		cout << "4. Interpolasi\n";	
		cin >> pilihan;	
	}


 	return 0;
}
