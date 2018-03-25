/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi I : dengan banyaknya elemen didefinisikan secara eksplisit, 
   memori tabel statik */

#include "boolean.h"
#include "array.h"
#include <stdio.h>


/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty (TabInt * T)
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
{
	Neff(*T) =0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt (TabInt T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
{
	return Neff(T);
}

int MaxNbEl (TabInt T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
{
	return IdxMax-IdxMin+1;
}

IdxType GetFirstIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
	return IdxMin;
}

IdxType GetLastIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
	return IdxMin+Neff(T)-1;
}


/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
	return (i>=IdxMin)&&(i<=MaxNbEl(T));
}

boolean IsIdxEff (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
	return (i>=IdxMin)&&(i<=IdxMin+Neff(T)-1);
}


/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (TabInt T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
	return Neff(T)==0;
}

/* *** Test tabel penuh *** */
boolean IsFull (TabInt T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
	return Neff(T)==MaxNbEl(T);
}


/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakukan N kali: Baca elemen mulai dari indeks 
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
{	//Kamus
	IdxType N, i;
	//Algorima
	do{
		scanf("%d",&N);
	}while((N<0)||(N>MaxNbEl(*T)));
	Neff(*T) = N;
	for(i=GetFirstIdx(*T);i<=GetLastIdx(*T);i++){
		scanf("%d", &Elmt(*T,i));
	}
}

void BacaIsiTab (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca elemen T sampai dimasukkan nilai -9999 */
/* Dibaca elemen satu per satu dan disimpan mulai dari IdxMin */
/* Pembacaan dihentikan jika pengguna memasukkan nilai -9999 */
/* Jika dari pertama dimasukkan nilai -9999 maka terbentuk T kosong */
{	//Kamus
	ElType temp;
	//Algoritma
	MakeEmpty(T);
	scanf("%d", &temp);
	while(temp!=-9999&&Neff(*T)<IdxMax){
		Neff(*T)+=1;
		Elmt(*T,GetLastIdx(*T))=temp;
		scanf("%d", &temp);
	}
}

void TulisIsi (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika T kosong : Hanya menulis "Tabel kosong" */
/* Contoh: Jika isi Tabel: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]1
   [2]20
   [3]30
   [4]50
*/
{	//Kamus
	IdxType i;
	//Algoritma
	if(IsEmpty(T))
		printf("Tabel kosong\n");
	else{
		for(i=IdxMin;i<=GetLastIdx(T);i++){
			printf("[%d]%d\n",i,Elmt(T,i));
		}
	}
}

void TulisIsiTab (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{	//Kamus
	IdxType i;
	//Algoritma
	printf("[");
	for(i=IdxMin;i<=GetLastIdx(T);i++){
		printf("%d",Elmt(T,i));
		if(i<GetLastIdx(T))
			printf(",");
	}
	printf("]");
}


/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
TabInt PlusTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
{	//Kamus
	TabInt T3;
	IdxType i;
	//Algoritma
	Neff(T3)=Neff(T1);
	for(i=GetFirstIdx(T1);i<=GetLastIdx(T1);i++){
		Elmt(T3,i)=Elmt(T1,i)+Elmt(T2,i);
	}
	return T3;
}

TabInt MinusTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */
{	//Kamus
	TabInt T3;
	IdxType i;
	//Algoritma
	Neff(T3)=Neff(T1);
	for(i=IdxMin;i<=IdxMin+Neff(T1)-1;i++){
		Elmt(T3,i)=Elmt(T1,i)-Elmt(T2,i);
	}
	return T3;
}

TabInt KaliTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1 * T2 dengan definisi setiap elemen dengan indeks yang sama dikalikan */
{	//Kamus
	TabInt T3;
	IdxType i;
	//Algoritma
	Neff(T3)=Neff(T1);
	for(i=IdxMin;i<=IdxMin+Neff(T1)-1;i++){
		Elmt(T3,i)=Elmt(T1,i)*Elmt(T2,i);
	}
	return T3;
	
}

TabInt KaliKons (TabInt Tin, ElType c)
/* Prekondisi : Tin tidak kosong */
/* Mengirimkan tabel dengan setiap elemen Tin dikalikan c */
{	//Kamus
	IdxType i;
	//Algoritma
	for(i=IdxMin;i<=IdxMin+Neff(Tin)-1;i++){
		Elmt(Tin,i)*=c;
	}
	return Tin;
}


/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ (TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika ukuran T1 = T2 dan semua elemennya sama */
{	//Kamus
	IdxType i;
	//Algoritma
	if(NbElmt(T1)==NbElmt(T2)){
		for(i=IdxMin;i<=IdxMin+Neff(T1)-1;i++){
			if(Elmt(T1,i)!=Elmt(T2,i))
				return false;
		}
		return true;
	}	
	else
		return false;
}

boolean IsLess (TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 < T2, */
/* yaitu : sesuai dg analogi 'Ali' < Badu'; maka [0, 1] < [2, 3] */
{	//Kamus
	IdxType i;
	//Algoritma
	for(i=GetFirstIdx(T1);i<=GetLastIdx(T1)&&i<=GetLastIdx(T2);i++){
		if(Elmt(T1,i)!=Elmt(T2,i))
			return Elmt(T1,i)<Elmt(T2,i);
	}
	return NbElmt(T1)<NbElmt(T2);
}


/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search TANPA boolean */
{	//Kamus
	IdxType i;
	//Algoritma
	for(i=IdxMin;i<=IdxMin+Neff(T)-1;i++){
		if(Elmt(T,i)==X)
			return i;
	}
	return IdxUndef;
}

IdxType Search2 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search DENGAN boolean Found */
{	//Kamus
	IdxType i;
	boolean found=false;
	//Algoritma
	for(i=IdxMin;i<=IdxMin+Neff(T)-1&&!found;i++){
		found=Elmt(T,i)==X;
	}
	return (found?i-1:IdxUndef);
}

boolean SearchB (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Memakai Skema search DENGAN boolean */
{	//Kamus
	IdxType i;
	boolean found=false;
	//Algoritma
	for(i=IdxMin;i<=IdxMin+Neff(T)-1&&!found;i++){
		found=Elmt(T,i)==X;
	}
	return found;
}

boolean SearchSentinel (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* dengan metoda sequential search dengan sentinel */
/* Untuk sentinel, manfaatkan indeks ke-0 dalam definisi array dalam Bahasa C 
   yang tidak dipakai dalam definisi tabel */
{	//Kamus
	IdxType i;
	Elmt(T,IdxMin+Neff(T)) = X;
	for(i=IdxMin;Elmt(T,i)!=X;i++);
	return i<IdxMin+Neff(T);
}

/* ********** NILAI EKSTREM ********** */
ElType ValMax (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai maksimum tabel */
{	//Kamus
	IdxType i;
	ElType maks;
	//Algoritma
	maks=Elmt(T,IdxMin);
	for(i=IdxMin+1;i<=IdxMin+Neff(T)-1;i++){
		if(Elmt(T,i)>maks)
			maks=Elmt(T,i);
	}
	return maks;
}

ElType ValMin (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai minimum tabel */
/* *** Mengirimkan indeks elemen bernilai ekstrem *** */
{	//Kamus
	IdxType i;
	ElType minimum;
	//Algoritma
	minimum=Elmt(T,IdxMin);
	for(i=IdxMin+1;i<=IdxMin+Neff(T)-1;i++){
		if(Elmt(T,i)<minimum)
			minimum=Elmt(T,i);
	}
	return minimum;
}

IdxType IdxMaxTab (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai maksimum pada tabel */
{	//Algoritma
	return Search1(T,ValMax(T));
}

IdxType IdxMinTab (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai minimum pada tabel */
{	//Algoritma
	return Search1(T,ValMin(T));
}


/* ********** OPERASI LAIN ********** */
void CopyTab (TabInt Tin, TabInt * Tout)
/* I.S. Tin terdefinisi, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (elemen dan ukuran identik) */
/* Proses : Menyalin isi Tin ke Tout */
{	//Kamus
	IdxType i;
	//Algoritma
	Neff(*Tout)=Neff(Tin);
	for(i=IdxMin;i<=IdxMin+Neff(Tin)-1;i++){
		Elmt(*Tout, i)=Elmt(Tin,i);
	}
}

TabInt InverseTab (TabInt T)
/* Menghasilkan tabel dengan urutan tempat yang terbalik, yaitu : */
/* elemen pertama menjadi terakhir, */
/* elemen kedua menjadi elemen sebelum terakhir, dst.. */
/* Tabel kosong menghasilkan tabel kosong */
{	//Kamus
	IdxType i;
	TabInt T2;
	//Algoritma
	Neff(T2)=Neff(T);
	for(i=IdxMin;i<=IdxMin+Neff(T)-1;i++){
		Elmt(T2, i)=Elmt(T,IdxMin+Neff(T)-i);
	}
	return T2;
}

boolean IsSimetris (TabInt T)
/* Menghasilkan true jika tabel simetrik */
/* Tabel disebut simetrik jika: */
/*      elemen pertama = elemen terakhir, */
/*      elemen kedua = elemen sebelum terakhir, dan seterusnya */
/* Tabel kosong adalah tabel simetris */
{	//Kamus
	IdxType i,j;
	//Algoritma
	for(i=GetFirstIdx(T), j=GetLastIdx(T);i<j;i++,j--){
		if(Elmt(T, i)!=Elmt(T,j))
			return false;
	}
	return true;
}


/* ********** SORTING ********** */
void MaxSortDesc (TabInt * T)
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menurun dengan Maximum Sort */
/* Proses : mengurutkan T sehingga elemennya menurun/mengecil */
/*          tanpa menggunakan tabel kerja */
{	//Kamus
	IdxType i,j, itemp;
	ElType temp;
	//Algoritma
	for(i=IdxMin;i<GetLastIdx(*T);i++){
		itemp=i;
		for(j=i+1;j<=GetLastIdx(*T);j++){
			if(Elmt(*T,itemp)<Elmt(*T,j))
				itemp=j;
		}
		if(i!=itemp){
			temp=Elmt(*T,itemp);
			Elmt(*T,itemp)=Elmt(*T,i);
			Elmt(*T,i)=temp;
		}
	}
}

void InsSortAsc (TabInt * T)
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menaik dengan Insertion Sort */
/* Proses : mengurutkan T sehingga elemennya menaik/membesar */
/*          tanpa menggunakan tabel kerja */
{	//Kamus
	IdxType i,j;
	ElType temp;
	//Algoritma
	for(i=IdxMin+1;i<IdxMin+Neff(*T)-1;i++){
		for(j=i;j>IdxMin&&Elmt(*T,j-1)>Elmt(*T,j);j--){
			temp=Elmt(*T,j-1);
			Elmt(*T,j-1)=Elmt(*T,j);
			Elmt(*T,j)=temp;
		}
	}
}


/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabInt * T, ElType X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{	//Algoritma
	Elmt(*T, IdxMin+Neff(*T))=X;
	Neff(*T)+=1;
}

void AddEli (TabInt * T, ElType X, IdxType i)
/* Menambahkan X sebagai elemen ke-i tabel tanpa mengganggu kontiguitas 
   terhadap elemen yang sudah ada */
/* I.S. Tabel tidak kosong dan tidak penuh */
/*      i adalah indeks yang valid. */
/* F.S. X adalah elemen ke-i T yang baru */
/* Proses : Geser elemen ke-i+1 s.d. terakhir */
/*          Isi elemen ke-i dengan X */
{	//Kamus
	IdxType j;
	//Algoritma
	for(j=IdxMin+Neff(*T); j>i;j--){
		Elmt(*T,j)=Elmt(*T,j-1);
	}
	Neff(*T)+=1;
	Elmt(*T,i)=X;
}


/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl (TabInt * T, ElType * X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
	*X=Elmt(*T,IdxMin+Neff(*T)-1);
	Neff(*T)-=1;
}

void DelEli (TabInt * T, IdxType i, ElType * X)
/* Menghapus elemen ke-i tabel tanpa mengganggu kontiguitas */
/* I.S. Tabel tidak kosong, i adalah indeks efektif yang valid */
/* F.S. X adalah nilai elemen ke-i T sebelum penghapusan */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
/* Proses : Geser elemen ke-i+1 s.d. elemen terakhir */
/*          Kurangi elemen efektif tabel */
{	//Kamus
	IdxType j;
	//Algoritma
	*X=Elmt(*T, i);
	Neff(*T)-=1;
	for(j=i;j<IdxMin+Neff(*T);j++){
		Elmt(*T,j)=Elmt(*T,j+1);
	}
}


/* ********** TABEL DGN ELEMEN UNIK (SETIAP ELEMEN HANYA MUNCUL 1 KALI) ********** */
void AddElUnik (TabInt * T, ElType X)
/* Menambahkan X sebagai elemen terakhir tabel, pada tabel dengan elemen unik */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/*      dan semua elemennya bernilai unik, tidak terurut */
/* F.S. Jika tabel belum penuh, menambahkan X sbg elemen terakhir T, 
        jika belum ada elemen yang bernilai X. 
		Jika sudah ada elemen tabel yang bernilai X maka I.S. = F.S. 
		dan dituliskan pesan "nilai sudah ada" */
/* Proses : Cek keunikan dengan sequential search dengan sentinel */
/*          Kemudian tambahkan elemen jika belum ada */
{	//Algoritma
	if(!SearchSentinel(*T,X)){
		Elmt(*T,IdxMin+Neff(*T))=X;
		Neff(*T)+=1;
	}
	else
		printf("nilai sudah ada\n");
}


/* ********** TABEL DGN ELEMEN TERURUT MEMBESAR ********** */
IdxType SearchUrut (TabInt T, ElType X)
/* Prekondisi: Tabel T boleh kosong. Jika tidak kosong, elemen terurut membesar. */
/* Mengirimkan indeks di mana harga X dengan indeks terkecil diketemukan */
/* Mengirimkan IdxUndef jika tidak ada elemen tabel bernilai X */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel kosong */
{	//Kamus
	IdxType i;
	//Algoritma
	for(i=IdxMin;Elmt(T,i)<X && i<IdxMin+Neff(T);i++);
	return (Elmt(T,i)==X?i:IdxUndef);
}

ElType MaxUrut (TabInt T)
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai maksimum pada tabel */
{	//Algoritma
	return Elmt(T,GetLastIdx(T));
}

ElType MinUrut (TabInt T)
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai minimum pada tabel*/
{	//Algoritma
	return Elmt(T,GetFirstIdx(T));
}

void MaxMinUrut (TabInt T, ElType * Max, ElType * Min)
/* I.S. Tabel T tidak kosong, elemen terurut membesar */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
{	//Algoritma
	*Max=MaxUrut(T);
	*Min=MinUrut(T);
}

void Add1Urut (TabInt * T, ElType X)
/* Menambahkan X tanpa mengganggu keterurutan nilai dalam tabel */
/* Nilai dalam tabel tidak harus unik. */
/* I.S. Tabel T boleh kosong, boleh penuh. */
/*      Jika tabel isi, elemennya terurut membesar. */
/* F.S. Jika tabel belum penuh, menambahkan X. */
/*      Jika tabel penuh, maka tabel tetap. */
/* Proses : Search tempat yang tepat sambil geser */
/*          Insert X pada tempat yang tepat tersebut tanpa mengganggu keterurutan */
{	//Kamus
	IdxType i=GetLastIdx(*T)+1;
	//Algoritma
	if(Neff(*T)>0){
		for(;i>IdxMin&&Elmt(*T,i-1)>X;i--)
			Elmt(*T,i)=Elmt(*T,i-1);
	}
	Elmt(*T,i)=X;
	Neff(*T)+=1;
}

void Del1Urut (TabInt * T, ElType X)
/* Menghapus X yang pertama kali (pada indeks terkecil) yang ditemukan */
/* I.S. Tabel tidak kosong */
/* F.S. Jika ada elemen tabel bernilai X , */
/*      maka banyaknya elemen tabel berkurang satu. */
/*      Jika tidak ada yang bernilai X, tabel tetap. */
/*      Setelah penghapusan, elemen tabel tetap kontigu! */
/* Proses : Search indeks ke-i dengan elemen ke-i = X. */
/*          Delete jika ada. */
{	//Kamus
	IdxType i;
	i=Search1(*T,X);
	if(i!=IdxUndef){
		DelEli(T,i,&X);
	}
}
