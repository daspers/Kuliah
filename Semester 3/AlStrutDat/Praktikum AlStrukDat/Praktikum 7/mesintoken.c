/*
NIM				: 13516
Nama			: 
Tanggal			: 28 September 2017
Topik praktikum	: Mesin Kata Versi 1
Deskripsi		: implementasi mesintoken.h
*/

#include "mesintoken.h"
#include "mesinkar.h"
#include "boolean.h"

boolean EndToken;
Token CToken;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{
	while(CC==BLANK)
		ADV();
}

void STARTTOKEN()
/* I.S. : CC sembarang 
   F.S. : EndToken = true, dan CC = MARK; 
          atau EndToken = false, CToken adalah Token yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir Token */
{
	START();
	IgnoreBlank();
	EndToken = CC==MARK;
	if(!EndToken){
		SalinToken();
	}
}

void ADVTOKEN()
{
	IgnoreBlank();
	EndToken = CC==MARK;
	if(!EndToken){
		SalinToken();
	}
}

void SalinToken()
/* Mengakuisisi Token dan menyimpan hasilnya dalam CToken
   I.S. : CC adalah karakter pertama dari Token
   F.S. : CToken berisi Token yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
	int i;
	CToken.val = 0;
	for(i=1;i<=NMax && (CC!=MARK&&CC!=BLANK);i++){
		if((CC>='0' &&  CC<='9')){
			if(CToken.val==-1)
				CToken.val=0;
			CToken.tkn='b';
			CToken.val=CToken.val*10+CC-'0';
		}
		else{
			CToken.tkn=CC;
			CToken.val=-1;
		}
		ADV();
	}
	IgnoreBlank();
}
