/*
    NIM				:
    Nama			: 
    Tanggal			: 5 Oktober 2017
    Topik praktikum	: Queue
    Deskripsi		: 
*/

#include <stdio.h>
#include "queue.h"
#include "boolean.h"

float AvgElmt (Queue Q){
	infotype x;
	int s = NBElmt(Q);
	float sum=0;
	while(!IsEmpty(Q)){
		Del(&Q, &x);
		sum += x;
	}
	return sum/s;
}

int main(){
	Queue Q;
	int s, op, x;
	scanf("%d", &s);
	CreateEmpty(&Q, s);
	scanf("%d", &op);
	while(op!=0){
		if(op == 1){
			scanf("%d", &x);
			if(!IsFull(Q)){
				Add(&Q,x);
			}
			else
				printf("Queue penuh\n");
		}
		else{
			if(IsEmpty(Q)){
				printf("Queue kosong\n");
			}
			else
				Del(&Q,&x);
		}
		scanf("%d", &op);
	}
	if(IsEmpty(Q)){
		printf("0\nTidak bisa dihitung\n");
	}
	else{
		printf("%d\n%.2f\n", NBElmt(Q), AvgElmt(Q));
	}
	return 0;
}
