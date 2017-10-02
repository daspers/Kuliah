/*
NIM				: 13516010
Nama			: Tony
Tanggal			: 28 September 2017
Topik praktikum	: Mesin Kata Versi 1
Deskripsi		: 
*/

#include <stdio.h>
#include "mesinkata.h"
#include "boolean.h"

boolean IsKataSama(Kata K1, Kata K2){
	if(K1.Length!=K2.Length)
		return false;
	int i=1;
	while(i<=K1.Length){
		if(K1.TabKata[i]!=K2.TabKata[i])
			return false;
		i++;
	}
	return true;
}

int main(){
	Kata Titik, Koma;
	long c=0, k=0, harga,a=0, b=0,i;
	STARTKATA();
	Titik.TabKata[1]='T';
	Titik.TabKata[2]='I';
	Titik.TabKata[3]='T';
	Titik.TabKata[4]='I';
	Titik.TabKata[5]='K';
	Titik.Length = 5;
	Koma.TabKata[1]='K';
	Koma.TabKata[2]='O';
	Koma.TabKata[3]='M';
	Koma.TabKata[4]='A';
	Koma.Length = 4;
	while(!EndKata){
		if(IsKataSama(CKata, Titik)){
			b++;
			printf(".");
		}
		else if(IsKataSama(CKata, Koma)){
			b++;
			printf(",");
		}
		else{
			if(a>0)
				printf(" ");
			if(CKata.Length<10)
				c++;
			else
				k++;
			for(i=1;i<=CKata.Length;i++){
				printf("%c", CKata.TabKata[i]);
			}
		}
		if(a==0)
			a=1;
		ADVKATA();
	}
	printf("\n");
	printf("%ld\n%ld\n",c,k);
	if(c+k+b>10)
		harga = c*900+k*1350;
	else
		harga = c*1000+k*1500;
	printf("%ld\n",harga);
	return 0;
}
