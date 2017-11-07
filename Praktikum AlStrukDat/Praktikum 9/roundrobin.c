/*
NIM					: 13516010
Nama				: Tony
Tanggal				: 02 November 2017
Topik praktikum		: ADT List Sirkuler dan Double Pointer, ADT Stack dan Queue dengan Representasi List Linier
Deskripsi			:
*/

#include <stdio.h>
#include "listsirkuler.h"

void DeleteRR (List *L, infotype TQ)
/* Jika L tidak kosong, "menghapus" elemen terakhir list L, misal last, sesuai aturan round robin, yaitu:
- jika Info(last)>TQ, maka last "diantrikan" kembali sebagai first elemen dengan Info(last)=Info(last)-TQ
- jika Info(last)<=TQ, maka DeleteLast(L,X) dan menampilkan X ke layar */
/* Jika L kosong, cetak "List kosong" */
/* I.S. TQ terdefinisi sebagai nilai time slice pemrosesan.
L terdefinisi, mungkin kosong. */
/* F.S. Elemen terakhir L diproses sesuai aturan round-robin.
L mungkin menjadi kosong. */
{
	address P;
	if(IsEmpty(*L)){
		printf("List kosong\n");
	}
	else{
		P = First(*L);
		while(Next(P)!=First(*L)){
			P = Next(P);
		}
		if(Info(P) > TQ){
			Info(P) -=TQ;
			DelLast(L, &P);
			InsertFirst(L, P);
			printf("%d\n", TQ);
			
		}
		else{
			DelLast(L, &P);
			printf("%d\n", Info(P));
		}
	}
}

float Average (List L)
/* Menghasilkan nilai rata-rata elemen L. L tidak kosong. */
{
	infotype S=0;
	int c=0;
	address P;
	P = First(L);
	S = Info(P);
	c=1;
	while(Next(P)!=First(L)){
		P = Next(P);
		S += Info(P);
		c++;
	}
	return (float) S/c;
}

int main(){
	List L;
	infotype X;
	int TQ;
	char c;
	CreateEmpty(&L);
	scanf("%d\n", &TQ);
	while(TQ <=0)
		scanf("%d\n", &TQ);
	scanf("%c", &c);
	while(c!='F'){
		if(c=='A'){
			scanf("%d", &X);
			if(X>0)
				InsVFirst(&L, X);
		}
		else if(c=='D'){
			DeleteRR(&L, TQ);
		}
		else if(c!='F')
			printf("Kode salah\n");
		scanf("%c", &c);
		scanf("%c", &c);
	}
	if(IsEmpty(L))
		printf("Proses selesai\n");
	else
		printf("%.2f\n", Average(L));
	return 0;
}
