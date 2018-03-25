/*
NIM				:
Nama			:
Tanggal			: 19 Oktober 2017
Topik praktikum	: Stack
Deskripsi		: bigint.c
*/

#include "stackt.h"
#include <stdio.h>

int main(){
	char x;
	int carry, a, b, c;
	Stack S1,S2,S3;
	CreateEmpty(&S1);
	CreateEmpty(&S2);
	CreateEmpty(&S3);
	scanf("%c",&x);
	while(x!='#'){
		Push(&S1,x-'0');
		scanf("%c",&x);
	}
	scanf("%c",&x);
	scanf("%c",&x);
	while(x!='#'){
		Push(&S2,x-'0');
		scanf("%c",&x);
	}
	carry=0;
	while(!IsEmpty(S1)&&!IsEmpty(S2)){
		Pop(&S1, &a);
		Pop(&S2, &b);
		c = a+b+carry;
		Push(&S3,c%10);
		carry = c/10;
	}
	while(!IsEmpty(S1)){
		Pop(&S1,&a);
		c = a+carry;
		Push(&S3,c%10);
		carry = (c)/10;
	}
	while(!IsEmpty(S2)){
		Pop(&S2,&a);
		c = a+carry;
		Push(&S3,c%10);
		carry = (c)/10;
	}
	if(carry>0){
		Push(&S3, carry);
		carry=0;
	}
	while(!IsEmpty(S3)){
		Pop(&S3,&a);
		printf("%d",a);
	}
	printf("\n");
	return 0;
}
