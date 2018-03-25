/*
NIM     : 13516010
Nama    : Tony
Tanggal : 31 Agustus 2017
Topik praktikum : Pengantar ADT 
Deskripsi      : 
*/

#include "jam.h"
#include <stdio.h>

int main(){
    int i,n;
    scanf("%d", &n);
    JAM J1, J2 ,t,mi=MakeJAM(23,59,59),ma=MakeJAM(0,0,0);
    for(i=1;i<=n;i++){
        printf("[%d]\n",i);
        BacaJAM(&J1);
        BacaJAM(&J2);
        if(JGT(J1, J2)){
            t=J1;
            J1=J2;
            J2=t;
        }
        if(JLT(J1,mi))
            mi=J1;
        if(JGT(J2,ma))
            ma=J2;
        printf("%ld\n",(Durasi(J1,J2)));
    }
    TulisJAM(mi);
    printf("\n");
    TulisJAM(ma);
    printf("\n");
    return 0;
}
