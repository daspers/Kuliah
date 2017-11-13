#include <stdlib.h>
#include <stdio.h>
#include "bintree.h"

/* *** Konstruktor *** */
BinTree Tree (infotype Akar, BinTree L, BinTree R) 
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
{
	BinTree P;
	P = AlokNode(Akar);
	if(P!=Nil){
		Left(P) = L;
		Right(P) = R;
	}
	return P;
}

void MakeTree (infotype Akar, BinTree L, BinTree R, BinTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R 
		jika alokasi berhasil. P = Nil jika alokasi gagal. */
{
	*P = Tree(Akar, L, R);
}


/* Manajemen Memory */
addrNode AlokNode (infotype X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	addrNode P;
	P = (addrNode) malloc(sizeof(Node));
	if(P!=Nil){
		Akar(P) = X;
		Left(P) = Nil;
		Right(P) = Nil;
	}
	return P;
}

void DealokNode (addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
	free(P);
}


/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty (BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
	return P == Nil;
}

boolean IsTreeOneElmt (BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
	if(IsTreeEmpty(P))
		return false;
	return Left(P) == Nil && Right(P) == Nil;
}

boolean IsUnerLeft (BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
	if(IsTreeEmpty(P))
		return false;
	return Left(P) != Nil && Right(P) == Nil;
}

boolean IsUnerRight (BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
	if(IsTreeEmpty(P))
		return false;
	return Left(P) == Nil && Right(P) != Nil;
}

boolean IsBiner (BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
	if(IsTreeEmpty(P))
		return false;
	return Left(P) != Nil && Right(P) != Nil;
}


/* *** Traversal *** */
void PrintPreorder (BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara preorder: akar, pohon kiri, dan pohon kanan. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (A()()) adalah pohon dengan 1 elemen dengan akar A
   (A(B()())(C()())) adalah pohon dengan akar A dan subpohon kiri (B()()) dan subpohon kanan (C()()) */
{
	if(IsTreeEmpty(P))
		printf("()");
	else{
		printf("(");
		printf("%d",Akar(P));
		PrintPreorder(Left(P));
		PrintPreorder(Right(P));
		printf(")");
	}
}

void PrintInorder (BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara inorder: pohon kiri, akar, dan pohon kanan. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (()A()) adalah pohon dengan 1 elemen dengan akar A
   ((()B())A(()C())) adalah pohon dengan akar A dan subpohon kiri (()B()) dan subpohon kanan (()C()) */
{
	if(IsTreeEmpty(P))
		printf("()");
	else{
		printf("(");
		PrintInorder(Left(P));
		printf("%d",Akar(P));
		PrintInorder(Right(P));
		printf(")");
	}
}

void PrintPostorder (BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara postorder: pohon kiri, pohon kanan, dan akar. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (()()A) adalah pohon dengan 1 elemen dengan akar A
   ((()()B)(()()C)A) adalah pohon dengan akar A dan subpohon kiri (()()B) dan subpohon kanan (()()C) */
{
	if(IsTreeEmpty(P))
		printf("()");
	else{
		printf("(");
		PrintPostorder(Left(P));
		PrintPostorder(Right(P));
		printf("%d",Akar(P));
		printf(")");
	}
}
void PrintTree (BinTree P, int h)
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
{
	if(IsTreeOneElmt(P)){
		printf("%d\n", Akar(P));
	}
	else if(!IsTreeEmpty(P)){
		int i;
		printf("%d\n", Akar(P));
		if(Left(P) != Nil){
			for(i=0;i<h;i++){
				printf(" ");
			}
			PrintTree(Left(P),h+h);
		}
		if(Right(P)!=Nil){
			for(i=0;i<h;i++){
				printf(" ");
			}
			PrintTree(Right(P),h+h);
		}
	}
}

/* *** Searching *** */
boolean SearchTree (BinTree P, infotype X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
	if(IsTreeEmpty(P))
		return false;
	else{
		if(Akar(P)==X)
			return true;
		else
			return SearchTree(Left(P),X) || SearchTree(Right(P), X);
	}
}


/* *** Fungsi-Fungsi Lain *** */
int NbElmt (BinTree P)
/* Mengirimkan banyaknya elemen (node) pohon biner P */
{
	if(IsTreeEmpty(P))
		return 0;
	else
		return 1+NbElmt(Left(P))+NbElmt(Right(P));
}

int NbDaun (BinTree P)
/* Mengirimkan banyaknya daun (node) pohon biner P */
/* Prekondisi: P tidak kosong */
{
	if(IsTreeOneElmt(P))
		return 1;
	else{
		if(IsUnerLeft(P))
			return NbDaun(Left(P));
		else if(IsUnerRight(P))
			return NbDaun(Right(P));
		else
			return NbDaun(Left(P))+NbDaun(Right(P));
	}
}

boolean IsSkewLeft (BinTree P)
/* Mengirimkan true jika P adalah pohon condong kiri */
/* Pohon kosong adalah pohon condong kiri */
{
	if(IsTreeEmpty(P))
		return true;
	else if(Right(P)!=Nil)
		return false;
	return IsSkewLeft(Left(P));
}

boolean IsSkewRight (BinTree P)
/* Mengirimkan true jika P adalah pohon condong kanan */
/* Pohon kosong adalah pohon condong kanan */
{
	if(IsTreeEmpty(P))
		return true;
	else if(Left(P)!=Nil)
		return false;
	return IsSkewRight(Right(P));
}

int Level (BinTree P, infotype X)
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P. 
   Akar(P) level-nya adalah 1. Pohon P tidak kosong. */
{
	if(Akar(P) == X)
		return 1;
	else{
		if(SearchTree(Left(P),X))
			return 1 + Level(Left(P), X);
		else
			return 1 + Level(Right(P), X);
	}
}

int Tinggi (BinTree P)
/* Pohon Biner mungkin kosong. Tinggi pohon kosong = 0.
   Mengirim "height" yaitu tinggi dari pohon */
{
	if(IsTreeEmpty(P))
		return 0;
	else{
		int r = Tinggi(Right(P));
		int l = Tinggi(Left(P));
		if(l>r)
			return 1+l;
		else
			return 1+r;
	}
}


/* *** Operasi lain *** */
void AddDaunTerkiri (BinTree *P, infotype X)
/* I.S. P boleh kosong */
/* F.S. P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
{
	if(IsTreeEmpty(*P)){
		*P = AlokNode(X);
	}
	else{
		AddDaunTerkiri(&Left(*P), X);
	}
}

void AddDaun (BinTree *P, infotype X, infotype Y, boolean Kiri)
/* I.S. P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau 
        sebagai anak Kanan X (jika Kiri = false) */
/*		Jika ada > 1 daun bernilai X, diambil daun yang paling kiri */
{
	if(IsTreeOneElmt(*P)){
		BinTree Q;
		Q = AlokNode(Y);
		if(Kiri)
			Left(*P) = Q;
		else
			Right(*P) = Q;
	}
	else{
		if(SearchTree(Left(*P), X))
			AddDaun(&Left(*P), X, Y, Kiri);
		else
			AddDaun(&Right(*P), X, Y, Kiri);
	}
}

void DelDaunTerkiri (BinTree *P, infotype *X)
/* I.S. P tidak kosong */
/* F.S. P dihapus daun terkirinya, dan didealokasi, dengan X adalah info yang semula 
        disimpan pada daun terkiri yang dihapus */
{
	if(IsTreeOneElmt(*P)){
		*X = Akar(*P);
		DealokNode(*P);
		*P = Nil;
	}
	else{
		if(IsUnerRight(*P))
			DelDaunTerkiri(&Right(*P), X);
		else
			DelDaunTerkiri(&Left(*P), X);
	}
}

void DelDaun (BinTree *P, infotype X)
/* I.S. P tidak kosong, minimum ada 1 daun bernilai X. */
/* F.S. Semua daun bernilai X dihapus dari P. */
{
	if(IsTreeOneElmt(*P)){
		DealokNode(*P);
		*P = Nil;
	}
	else{
		if(SearchTree(Left(*P),X))
			DelDaun(&Left(*P), X);
		if(SearchTree(Right(*P),X))
			DelDaun(&Right(*P), X);
	}
}

List MakeListDaun (BinTree P)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua daun pohon P,
   jika semua alokasi list berhasil.
   Daun terkiri menjadi elemen pertama dari list, diikuti elemen kanannya, dst.
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
	if(IsTreeEmpty(P))
		return Nil;
	else if(IsTreeOneElmt(P))
		return Alokasi(Akar(P));
	else
		return Concat(MakeListDaun(Left(P)), MakeListDaun(Right(P)));
}

List MakeListPreorder (BinTree P)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua elemen pohon P 
   dengan urutan preorder, jika semua alokasi berhasil.   
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
	if(IsTreeEmpty(P))
		return Nil;
	else{
		return Konso(Akar(P), Concat(MakeListPreorder(Left(P)), MakeListPreorder(Right(P))));
	}
}

List MakeListLevel (BinTree P, int N)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua elemen pohon P 
   yang levelnya=N, jika semua alokasi berhasil. 
   Elemen terkiri menjadi elemen pertama dari list, diikuti elemen kanannya, dst.
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
	if(IsTreeEmpty(P))
		return Nil;
	else if(N==1)
		return Alokasi(Akar(P));
	else{
		return Concat(MakeListLevel(Left(P),N-1), MakeListLevel(Right(P),N-1));
	}
}
