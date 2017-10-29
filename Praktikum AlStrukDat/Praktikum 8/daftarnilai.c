/*
NIM				: 
Nama			: 
Tanggal			: 25 Oktober 2017
Topik praktikum	: ADT List Linier
Deskripsi		: 
*/

#include <stdio.h>
#include "listlinier.h"
#include "boolean.h"

int main(){
	infotype x;
	List L;
	CreateEmpty(&L);
	scanf("%d", &x);
	while(x>=0 && x<=100){
		InsVLast(&L, x);
		scanf("%d", &x);
	}
	if(IsEmpty(L)){
		printf("Daftar nilai kosong\n");
	}
	else{
		printf("%d\n", NbElmt(L));
		printf("%d\n", Max(L));
		printf("%d\n", Min(L));
		printf("%.2f\n", Average(L));
		PrintInfo(L);
		printf("\n");
		InversList(&L);
		PrintInfo(L);
		printf("\n");
	}
	return 0;
}
