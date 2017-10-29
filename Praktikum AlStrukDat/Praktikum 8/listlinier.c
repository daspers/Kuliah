/*
NIM				:
Nama			: Tony
Tanggal			: 25 Oktober 2017
Topik praktikum	: ADT List Linier
Deskripsi		: 
*/

#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"
#include "boolean.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong */
{
	return First(L) == Nil;
}


/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
	First(*L) = Nil;
}


/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	address P = (address) malloc (sizeof(ElmtList));
	if(P != Nil){
		Info(P) = X;
		Next(P) = Nil;
	}
	return P;
}

void Dealokasi (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	address P;
	P = First(L);
	while(P != Nil){
		if(Info(P) == X)
			return P;
		else
			P = Next(P);
	}
	return Nil;
}

boolean FSearch (List L, address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
	address Q;
	Q = First(L);
	while(Q != Nil){
		if(Q == P)
			return true;
		else
			Q = Next(Q);
	}
	return false;
}

address SearchPrec (List L, infotype X)
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
	address P,Q;
	P = Search(L,X);
	if(P!=Nil){
		Q = First(L);
		if(P==Q)
			return Nil;
		else{
			Q = Next(Q);
			while(Q!=P){
				Q = Next(Q);
			}
			return Q;
		}
	}
	return Nil;
}


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	address P;
	P = Alokasi(X);
	if(P!=Nil)
		InsertFirst(L, P);
}

void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	address P;
	P = Alokasi(X);
	if(P!=Nil)
		InsertLast(L, P);
}


/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
	address P;
	P = First(*L);
	*X = Info(P);
	First(*L) = Next(P);
	Dealokasi(&P);
}

void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	address P;
	P = First(*L);
	if(Next(P) == Nil){
		*X = Info(P);
		First(*L) = Nil;
		Dealokasi(&P);
	}
	else{
		while(Next(Next(P))!=Nil){
			P = Next(P);
		}
		*X = Info(Next(P));
		Next(P) = Nil;
		Dealokasi(&Next(P));
	}
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	Next(P) = First(*L);
	First(*L) = P;
}

void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next(P) = Next(Prec);
	Next(Prec) = P;
}

void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	address Q;
	Q = First(*L);
	if(Q==Nil)
		First(*L) = P;
	else{
		while(Next(Q)!=Nil){
			Q = Next(Q);
		}
		InsertAfter(L, P, Q);
	}
}


/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P = First(*L);
	First(*L) = Next(*P);
}

void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	address P;
	P = First(*L);
	if(X == Info(P)){
		First(*L) = Next(P);
	}
	else{
		if(Next(P)!=Nil){
			while(Info(Next(P))!=X && Next(Next(P))!=Nil)
				P = Next(P);
			if(Info(Next(P))==X){
				Next(P) = Next(Next(P));
			}
		}
	}
}

void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
	address Q;
	Q = First(*L);
	if(Next(Q)==Nil){
		*P = Q;
		First(*L) = Nil;
	}
	else{
		while(Next(Next(Q)) != Nil){
			Q = Next(Q);
		}
		*P = Next(Q);
		Next(Q) = Nil;
	}
}

void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel = Next(Prec);
	Next(Prec) = Next(Next(Prec));
	Next(*Pdel) = Nil;
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
	address P = First(L);
	printf("[");
	while(P!=Nil){
		printf("%d", Info(P));
		if(Next(P)!=Nil)
			printf(",");
		P = Next(P);
	}
	printf("]");
}

int NbElmt (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
	int coun = 0;
	address P = First(L);
	while(P!=Nil){
		coun++;
		P = Next(P);
	}
	return coun;
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max (List L)
/* Mengirimkan nilai info(P) yang maksimum */
{
	address P = First(L);
	infotype ma = Info(P);
	P = Next(P);
	while(P!=Nil){
		if(Info(P)>ma)
			ma = Info(P);
		P = Next(P);
	}
	return ma;
}

address AdrMax (List L)
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
{
	infotype X;
	address P = First(L);
	X = Max(L);
	while(Info(P)!=X)
		P = Next(P);
	return P;
}

infotype Min (List L)
/* Mengirimkan nilai info(P) yang minimum */
{
	address P = First(L);
	infotype mi = Info(P);
	P = Next(P);
	while(P!=Nil){
		if(Info(P)<mi)
			mi = Info(P);
		P = Next(P);
	}
	return mi;
}

address AdrMin (List L)
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
{
	infotype X;
	address P = First(L);
	X = Min(L);
	while(Info(P)!=X)
		P = Next(P);
	return P;
}

float Average (List L)
/* Mengirimkan nilai rata-rata info(P) */
{
	infotype sum=0;
	address P;
	P = First(L);
	while(P!=Nil){
		sum+=Info(P);
		P = Next(P);
	}
	return (float) sum/NbElmt(L);
}

/****************** PROSES TERHADAP LIST ******************/
void DelAll (List *L)
/* Delete semua elemen list dan alamat elemen di-dealokasi */
{
	address P = First(*L),Q;
	if(P!=Nil){
		while(P!=Nil){
			Q = Next(P);
			Dealokasi(&P);
			P = Q;
		}
		First(*L) = Nil;
	}
}

void InversList (List *L)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
	address P, Q;
	if(!IsEmpty(*L)){
		P = First(*L);
		Q = Next(P);
		Next(P) = Nil;
		while(Q!=Nil){
			P=Q;
			Q=Next(Q);
			InsertFirst(L, P);
		}
	}
}

List FInversList (List L)
/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */
{
	List L2;
	address P;
	CreateEmpty(&L2);
	if(!IsEmpty(L)){
		P = First(L);
		while(P!=Nil){
			InsVFirst(&L2, Info(P));
			P = Next(P);
		}
		if(NbElmt(L)!=NbElmt(L2)){
			DelAll(&L2);
		}
	}
	return L2;
}

void CopyList (List *L1, List *L2)
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */
{
	First(*L2) = First(*L1);
}

List FCopyList (List L)
/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */
{
	List L2;
	address P;
	CreateEmpty(&L2);
	if(!IsEmpty(L)){
		P = First(L);
		while(P!=Nil){
			InsVLast(&L2, Info(P));
			P = Next(P);
		}
		if(NbElmt(L)!=NbElmt(L2)){
			DelAll(&L2);
		}
	}
	return L2;
}

void CpAlokList (List Lin, List *Lout)
/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */
{
	*Lout = FCopyList(Lin);
}

void Konkat (List L1, List L2, List * L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=Nil*/
/* Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Nil*/
/* dan semua elemen yang pernah dialokasi didealokasi */
{
	address P;
	CreateEmpty(L3);
	P = First(L1);
	while(P!=Nil){
		InsVLast(L3, Info(P));
		P = Next(P);
	}
	P = First(L2);
	while(P!=Nil){
		InsVLast(L3, Info(P));
		P = Next(P);
	}
	if(NbElmt(*L3)!=NbElmt(L1)+NbElmt(L2)){
		DelAll(L3);
	}
}

void Konkat1 (List *L1, List *L2, List *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
	address P;
	CreateEmpty(L3);
	if(IsEmpty(*L1)){
		First(*L3) = First(*L2);
	}
	else{
		First(*L3) = First(*L1);
		P = First(*L3);
		while(Next(P)!=Nil){
			P = Next(P);
		}
		Next(P) = First(*L2);
		First(*L1) = Nil;
	}
	First(*L2) = Nil;
}

void PecahList (List *L1, List *L2, List L)
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 */
{
	int i, n;
	address P = First(L);
	CreateEmpty(L1);
	CreateEmpty(L2);
	n = NbElmt(L)/2;
	for(i=0; i<n;i++){
		InsVLast(L1, Info(P));
		P = Next(P);
	}
	while(P!=Nil){
		InsVLast(L2, Info(P));
		P = Next(P);
	}
}
