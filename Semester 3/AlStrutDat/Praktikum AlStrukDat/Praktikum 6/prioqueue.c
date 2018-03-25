#include "boolean.h"
#include "prioqueue.h"
#include <stdlib.h>
#include <stdio.h>

boolean IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
	return Head(Q) == Nil && Tail(Q) == Nil;
}

boolean IsFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
	return NBElmt(Q) == MaxEl(Q);
}

int NBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
	if(IsEmpty(Q))
		return 0;
	if(Head(Q) <= Tail(Q))
		return Tail(Q)-Head(Q)+1;
	return (Tail(Q)) + (MaxEl(Q) - Head(Q)+1);
}


/* *** Kreator *** */
void CreateEmpty (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
	(*Q).T = (infotype *) malloc((Max+1)*sizeof(infotype));
	MaxEl(*Q) = 0;
	if((*Q).T != NULL){
		MaxEl(*Q) = Max;
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}
}


/* *** Destruktor *** */
void DeAlokasi(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
	free((*Q).T);
	MaxEl(*Q) = 0;
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}


/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X)
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer;
        elemen baru disisipkan pada posisi yang tepat sesuai dengan prioritas */
{
	int i;
	boolean cari = true;
	if(IsEmpty(*Q)){
		Head(*Q) = 1;
		Tail(*Q) = 1;
	}
	else if(Tail(*Q)==MaxEl(*Q))
		Tail(*Q) = 1;
	else
		Tail(*Q) += 1;
	i = Tail(*Q);
	while(cari && i!=Head(*Q)){
		if(Prio(Elmt(*Q,i-1))>=Prio(X)){
			Elmt(*Q,i) = X;
			cari = false;
		}
		else{
			Elmt(*Q,i) = Elmt(*Q,i-1);
			if(i==1)
				i = MaxEl(*Q);
			else
				i--;
		}
	}
	if(cari){
		Elmt(*Q,i) = X;
	}
}

void Del (Queue * Q, infotype * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
	*X = InfoHead(*Q);
	if(NBElmt(*Q)==1){
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}
	else{
		if(Head(*Q)==MaxEl(*Q))
			Head(*Q) = 1;
		else
			Head(*Q) += 1;
	}
}

/* Operasi Tambahan */
void PrintQueue (Queue Q)
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/
{
	infotype x;
	while(!IsEmpty(Q)){
		Del(&Q,&x);
		printf("%d %d\n",Prio(x), Info(x));
	}
	printf("#\n");
}
