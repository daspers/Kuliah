/*
NIM				: 13516
Nama			: 
Tanggal			: 19 Oktober 2017
Topik praktikum	: Stack
Deskripsi		: 
*/

#include "stackt.h"
#include "boolean.h"
#include "mesintoken.h"
#include <math.h>
#include <stdio.h>

int main(){
	Stack S;
	int a,b,c;
	CreateEmpty(&S);
	STARTTOKEN();
	if(EndToken){
		printf("Ekspresi kosong\n");
	}
	else{
		while(!EndToken){
			if(CToken.tkn == 'b'){
				Push(&S,CToken.val);
				printf("%d\n",CToken.val);
			}
			else{
				Pop(&S,&b);
				Pop(&S,&a);
				printf("%d %c %d\n",a,CToken.tkn,b);
				if(CToken.tkn=='+')
					c = a+b;
				else if(CToken.tkn=='-')
					c = a-b;
				else if(CToken.tkn=='/')
					c = a/b;
				else if(CToken.tkn=='*')
					c = a*b;
				else if(CToken.tkn=='^')
					c = pow(a,b);
				Push(&S, c);
				printf("%d\n",c);
			}
			ADVTOKEN();
		}
		Pop(&S,&c);
		printf("Hasil=%d\n", c);
	}
	return 0;
}
