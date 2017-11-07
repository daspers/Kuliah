/*
NIM					: 13516010
Nama				: Tony
Tanggal				: 02 November 2017
Topik praktikum		: ADT List Sirkuler dan Double Pointer, ADT Stack dan Queue dengan Representasi List Linier
Deskripsi			:
*/

#include <stdio.h>
#include "listdp.h"

address SearchPrec (List L, infotype X)
/* Mengirimkan address elemen sebelum elemen yang nilainya>=X */
/* Mencari apakah ada elemen list dengan Info(P)>=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)>=X pertama. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
{
	address P;
	P = First(L);
	if(Info(P) >= X || Next(P) == Nil){
		return Nil;
	}
	else{
		while(Info(Next(P))<X && Next(Next(P))!=Nil){
			P = Next(P);
		}
		if(Info(Next(P))>=X)
			return P;
		else
			return Nil;
	}
}

void InsertUrut (List *L, infotype X)
/* Menambahkan elemen pada list L tanpa mengganggu keterurutan L.
Manfaatkan fungsi SearchPrec. */
/* I.S. X terdefinisi. L terdefinisi, mungkin kosong.
Jika tidak kosong, L terurut membesar. */
/* F.S. X dialokasi. Jika alokasi berhasil, maka X dimasukkan sebagai salah
satu elemen L tanpa mengganggu keterurutan L. Insert elemen baru
dapat dilakukan di awal, di tengah, maupun di akhir.
Jika alokasi gagal, L tetap. */
{
	address P, Q;
	Q = Alokasi(X);
	if(IsEmpty(*L)){
		InsVLast(L, X);
	}
	else{
		P = SearchPrec(*L, X);
		if(P==Nil){
			if(Info(First(*L))>=X){
				InsertFirst(L, Q);
			}
			else{
				InsertLast(L, Q);
			}
		}
		else{
			InsertAfter(L, Q, P);
		}
	}
}

infotype Max (List L)
/* Menghasilkan nilai terbesar dari elemen list L. L tidak kosong. */
{
	return Info(Last(L));
}

infotype Min (List L)
/* Menghasilkan nilai terkecil dari elemen list L. L tidak kosong. */
{
	return Info(First(L));
}

float Average (List L)
/* Menghasilkan nilai rata-rata elemen L. L tidak kosong. */
{
	infotype S = 0;
	int c =0;
	address P;
	P = First(L);
	while(P!=Nil){
		S += Info(P);
		P = Next(P);
		c++;
	}
	return (float) S/c;
}

int main(){
	List L;
	infotype X;
	CreateEmpty(&L);
	scanf("%d", &X); 
	while(X!=-9999){
		InsertUrut(&L, X);
		scanf("%d", &X); 
	}
	if(IsEmpty(L))
		printf("[]\n");
	else{
		printf("%d\n", Max(L));
		printf("%d\n", Min(L));
		printf("%.2f\n", Average(L));
		PrintForward(L);
		printf("\n");
		PrintBackward(L);
		printf("\n");
	}
	return 0;
}
