/*
NIM				: 13516010
Nama			: Tony
Tanggal			: 28 September 2017
Topik praktikum	: Mesin Kata Versi 1
Deskripsi		: implementasi mesintoken.h
*/

#include "mesintoken.h"
#include "boolean.h"
#include <stdio.h>

int main(){
	STARTTOKEN();
	if(EndToken)
		printf("Ekspresi kosong\n");
	while(!EndToken){
		if(CToken.tkn=='b')
			printf("%d\n",CToken.val);
		else
			printf("%c\n",CToken.tkn);
		ADVTOKEN();
	}
}
