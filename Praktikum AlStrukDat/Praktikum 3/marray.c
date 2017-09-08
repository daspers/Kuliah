/*
    NIM         : 
    Nama        : 
    Tanggal     : 7 September 2017
    Topik praktikum : Array Statik Eksplisit
    Deskripsi       : file main dari ADT array.h
 */

#include <stdio.h>
#include "array.h"
#include "boolean.h"

int main(){
    TabInt T;
    IdxType i;
    ElType X,med;
    int c=0;
    BacaIsi(&T);
    TulisIsiTab(T);
    printf("\n");
    scanf("%d",&X);
    for(i=GetFirstIdx(T);i<=GetLastIdx(T);i++){
        if(Elmt(T,i)==X)
            c++;
    }
    printf("%d\n",c);
    i=Search1(T,X);
    if(i!=IdxUndef)
        printf("%d\n",i);
    else
        printf("%d tidak ada\n", X);
    InsSortAsc(&T);
    if(X==ValMax(T))
        printf("maksimum\n");
    if(X==ValMin(T))
        printf("minimum\n");\
    if(NbElmt(T)%2==1)
        med=Elmt(T,NbElmt(T)/2+1);
    else
        med=Elmt(T,NbElmt(T)/2);
    if(X==med)
        printf("median\n");
    return 0;
}
