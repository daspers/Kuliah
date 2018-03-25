/*
    NIM         : 13516010
    Nama        : Tony
    Tanggal     : 7 September 2017
    Topik praktikum : Array Statik Eksplisit
    Deskripsi       : implementasi dari ADT arraypos.h
 */

#include "arraypos.h"
#include "boolean.h"
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty (TabInt * T)
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */
{
    IdxType i;
    for(i=IdxMin;i<=IdxMax;i++)
        Elmt(*T,i)=ValUndef;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt (TabInt T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
{
    IdxType i;
    int c=0;
    for(i=IdxMin;i<=IdxMax&&Elmt(T,i)!=ValUndef;i++)
        c++;
    return c;
}

int MaxNbEl (TabInt T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
    return IdxMax-IdxMin+1;
}

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
    return IdxMin;
}

IdxType GetLastIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
    return IdxMin+NbElmt(T)-1;
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (i>=IdxMin)&&(i<=MaxNbEl(T)+IdxMin-1);
}

boolean IsIdxEff (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
    return (i>=GetFirstIdx(T))&&(i<=GetLastIdx(T));
}


/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (TabInt T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
    return NbElmt(T)==0;
}

/* *** Test tabel penuh *** */
boolean IsFull (TabInt T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
    return NbElmt(T)==MaxNbEl(T);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakukan N kali: Baca elemen mulai dari indeks 
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
{   //Kamus
    IdxType N, i;
    //Algorima
    MakeEmpty(T);
    do{
        scanf("%d",&N);
    }while((N<0)||(N>MaxNbEl(*T)));
    for(i=IdxMin;i<IdxMin+N;i++){
        scanf("%d", &Elmt(*T,i));
    }
    
}

void TulisIsiTab (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{   //Kamus
    IdxType i,j;
    //Algoritma
    printf("[");
    for(i=IdxMin, j=GetLastIdx(T);i<=j;i++){
        printf("%d",Elmt(T,i));
        if(i<j)
            printf(",");
    }
    printf("]");
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
TabInt PlusMinusTab (TabInt T1, TabInt T2, boolean plus)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */
{   //Kamus
    IdxType i,j;
    //Algoritma
    for(i=GetFirstIdx(T1), j=GetLastIdx(T1);i<=j;i++){
        if(plus)
            Elmt(T1,i)+=Elmt(T2,i);
        else
            Elmt(T1,i)-=Elmt(T2,i);
    }
    return T1;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ (TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika ukuran T1 = T2 dan semua elemennya sama */
{   //Kamus
    IdxType i,j;
    //Algoritma
    if(NbElmt(T1)==NbElmt(T2)){
        for(i=GetFirstIdx(T1), j=GetLastIdx(T1);i<=j;i++){
            if(Elmt(T1,i)!=Elmt(T2,i))
                return false;
        }
        return true;
    }   
    else
        return false;
    
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
{   //Kamus
    IdxType i,j;
    //Algoritma
    for(i=GetFirstIdx(T), j=GetLastIdx(T);i<=j;i++){
        if(Elmt(T,i)==X)
            return i;
    }
    return IdxUndef;
    
}

boolean SearchB (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
{   //Kamus
    IdxType i,j;
    //Algoritma
    for(i=GetFirstIdx(T), j=GetLastIdx(T);i<=j;i++){
        if(Elmt(T,i)==X)
            return true;
    }
    return false;
    
}

/* ********** NILAI EKSTREM ********** */
void MaxMin (TabInt T, ElType * Max, ElType * Min)
/* I.S. Tabel T tidak kosong */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
{
    IdxType i,j;
    //Algoritma
    *Max=Elmt(T,IdxMin);
    *Min=Elmt(T,IdxMin);
    for(i=IdxMin+1, j=GetLastIdx(T);i<=j;i++){
        if(Elmt(T,i)>*Max)
            *Max=Elmt(T,i);
        else if(Elmt(T,i)<*Min)
            *Min=Elmt(T,i);
    }
}

/* ********** OPERASI LAIN ********** */
ElType SumTab (TabInt T)
/* Menghasilkan hasil penjumlahan semua elemen T */
/* Jika T kosong menghasilkan 0 */
{   
    IdxType i,j;
    ElType sum=0;
    //Algoritma
    for(i=IdxMin, j=GetLastIdx(T);i<=j;i++){
        sum+=Elmt(T,i);
    }
    return sum;
}

int CountX (TabInt T, ElType X)
/* Menghasilkan berapa banyak kemunculan X di T */
{
    IdxType i,j;
    int c=0;
    //Algoritma
    for(i=IdxMin, j=GetLastIdx(T);i<=j;i++){
        if(Elmt(T,i)==X)
            c++;
    }
    return c;
}

/* Jika T kosong menghasilkan 0 */
boolean IsAllGenap (TabInt T)
/* Menghailkan true jika semua elemen T genap */
{
    IdxType i,j;
    //Algoritma
    for(i=IdxMin, j=GetLastIdx(T);i<=j;i++){
        if(Elmt(T,i)%2==1)
            return false;
    }
    return NbElmt(T)>0;
}

/* ********** SORTING ********** */
void Sort (TabInt * T, boolean asc)
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
   algoritma bebas */
{
    IdxType i,j,k=GetLastIdx(*T),itemp;
    ElType temp;
    //Algoritma
    for(i=GetFirstIdx(*T);i<k;i++){
        itemp=i;
        for(j=i+1;j<=k;j++){
            if(asc){
                if(Elmt(*T,itemp)>Elmt(*T,j))
                    itemp=j;
            }
            else if(Elmt(*T,itemp)<Elmt(*T,j)){
                itemp=j;
            }
        }
        if(i!=itemp){
            temp=Elmt(*T,itemp);
            Elmt(*T,itemp)=Elmt(*T,i);
            Elmt(*T,i)=temp;
        }
    }
}
/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabInt * T, ElType X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
    Elmt(*T, GetLastIdx(*T)+1)=X;
}

/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl (TabInt * T, ElType * X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
    *X= Elmt(*T, GetLastIdx(*T));
    Elmt(*T, GetLastIdx(*T))=ValUndef;
}
